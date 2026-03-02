# 显存分析

“一个 10B 参数的模型，用 Adam 优化器进行 FP16 混合精度训练，最少需要多少显存？”

## 1. 基础知识：数据类型与大小

在分布式训练中，我们主要关注以下两种精度：

* **FP32 (Float32):** 每个参数占用 **4 Bytes**。
* **FP16 / BF16 (Float16/Bfloat16):** 每个参数占用 **2 Bytes**。

## 2. FP16 混合精度训练的显存占用

混合精度训练（Mixed Precision Training）为了保证数值稳定性，会在后台维护一套 FP32 的权重。假设模型参数量为 $\Psi$（单位：Billion）：

### A. 模型参数 (Parameters)

* 训练时使用 FP16 进行前向和后向计算：$2\Psi$ Bytes。

### B. 梯度 (Gradients)

* 梯度通常也存储为 FP16：$2\Psi$ Bytes。

### C. 优化器状态 (Optimizer States) - 以 Adam 为例

这是显存占用的“大户”。Adam 优化器需要为每个参数维护：

1. **FP32 权重副本：** $4\Psi$ Bytes（用于更新时保证精度）。
2. **Momentum（动量）：** $4\Psi$ Bytes (FP32)。
3. **Variance（方差）：** $4\Psi$ Bytes (FP32)。

* **合计：** $12\Psi$ Bytes。

---

## 3. 静态显存汇总公式

在**纯数据并行**（无 ZeRO）的情况下，每个 GPU 存储模型状态所需的总显存为：


$$Total_{ModelStates} = 2\Psi (Param) + 2\Psi (Grad) + 12\Psi (Optimizer) = 16\Psi \text{ Bytes}$$

> **面试真题：** 10B 模型需要多少显存？
> **回答：** $16 \times 10 \text{B Bytes} = 160 \text{ GB}$。
> 这显然超过了单张 A100 (80GB) 的容量，所以必须引入 ZeRO。

---

## 4. ZeRO 的显存节省推导

ZeRO (Zero Redundancy Optimizer) 的核心思想是将上述 $16\Psi$ 的内容切分到 $N$ 个 GPU 上。

| 策略 | 显存公式 (Per GPU) | 10B 模型在 64 卡上的占用 |
| --- | --- | --- |
| **ZeRO-1** (切分 Optimizer) | $2\Psi + 2\Psi + \frac{12\Psi}{N}$ | $40\text{GB} + 1.875\text{GB} \approx 41.9\text{GB}$ |
| **ZeRO-2** (加切分 Gradient) | $2\Psi + \frac{14\Psi}{N}$ | $20\text{GB} + 2.18\text{GB} \approx 22.2\text{GB}$ |
| **ZeRO-3** (再切分 Parameter) | $\frac{16\Psi}{N}$ | $160 / 64 = 2.5\text{GB}$ |

---

## 5. 面试加分项：剩余的显存去哪了？

除了上述“模型状态”，实际训练中还有：

1. **Activation（激活值）：** 与 Batch Size 和序列长度强相关。可以用 **Activation Checkpointing** 用计算换显存。
2. **Temporary Buffers：** 用于通信（如 `all_reduce`）的临时缓冲区。
3. **Fragmented Memory：** 内存碎片。

---

**下一步建议：**
显存推导是静态的，面试官接下来很可能会问：**“ZeRO-3 虽然省钱，但在 Forward 和 Backward 过程中是如何通过通信拿回参数的？”**

你想深入分析 **ZeRO-3 的通信状态机**，还是先看一段 **ZeRO-2 梯度切分的源码实现**？