

## 1. 序列并行 (Sequence Parallelism) 与 张量并行 (Tensor Parallelism) 的区别

面试官可能会问：“既然有了张量并行，为什么还要序列并行？”

* **考点**：
* 
* **张量并行 (TP)**：通常在 $H$（隐藏层维度）上切分。能并行化 `Linear` 层，但 `LayerNorm` 和 `Dropout` 通常会在每个 Rank 上重复计算，产生冗余显存。
* 
* **序列并行 (SP)**：在 $S$（序列长度维度）上切分。它能把 `LayerNorm` 和 `Dropout` 的激活值平摊到各个 GPU 上，极大地降低显存峰值。


* **代码对应**：`_ScatterToSequenceParallelRegion` (进入 SP) 和 `_GatherFromSequenceParallelRegion` (退出 SP)。

---

## 2. 前向传播与反向传播的“对称性”

这是一个经典的面试题：“如果前向传播是 All-Gather，反向传播应该是什么？”

* **核心规律**：
* 
* **Forward: All-Gather $\rightarrow$ Backward: Reduce-Scatter**
* 
* **Forward: Split $\rightarrow$ Backward: All-Gather**
* 
* **Forward: All-Reduce $\rightarrow$ Backward: Copy/Identity**


* **代码逻辑**：
* 
* 看 `_GatherFromSequenceParallelRegion` 的 `backward`：它根据 `tensor_parallel_output_grad` 的布尔值，决定是做简单的 `split` 还是做复杂的 `reduce_scatter`。



---

## 3. All-to-All 的维度变换逻辑

面试官会让你手写或口述 `all_to_all_sp2hp` 的变换过程。

* **关键步骤**：
1. **切分 (Split)**：在 GPU 本地将 $H$ 维切开。
2. **堆叠 (Reshape/Cat)**：为了满足 `all-to-all` 的输入要求，把切开的块堆叠到第 0 维。
3. **交换 (All-to-All)**：跨 GPU 交换数据块。


* **面试陷阱**：为什么要 `contiguous()`？
* **回答**：分布式通信算子通常要求输入张量在内存中是连续的，而 `split` 或 `transpose` 后的张量通常不连续，直接传入会报错或导致性能极差。



---

## 4. 显存优化：Global Memory Buffer

代码中出现了 `get_global_memory_buffer()`。

* **提问**：为什么要用全局内存池，而不是直接 `torch.empty`？
* **回答**：
* **减少碎片**：频繁申请和释放大块通信缓冲区（如 All-Gather 的输出）会导致严重的 CUDA 显存碎片。
* **复用**：Megatron 预先申请一块大显存，通过偏移量（Offset）来复用，能提高显存利用率并加速。



---

## 5. 通信算子的版本兼容性与封装

注意代码开头的 `dist_all_gather_func` 逻辑。

* **考点**：`all_gather` vs `all_gather_into_tensor`。
* 传统的 `all_gather` 输入是 `List[Tensor]`，这会产生大量的 Python 对象开销。
* `all_gather_into_tensor`（新版 PyTorch）直接将结果写入一个大的连续 Tensor，性能更高，更符合 HPC 的思维。



---

## 💡 面试模拟题

**面试官**：“在 `all_to_all_hp2sp` 中，如果你不进行通信，直接在本地 reshape，结果对吗？”
**你**：“不对。因为在 HP 模式下，当前 GPU 只持有部分 $H$ 维度的特征；如果不通过 All-to-All 交换，你无法获得其他 GPU 上属于当前进程负责的那些序列片段（Tokens）的信息。这本质上是一个**分布式转置**过程。”

---

**下一步建议：**
你想让我模拟面试官，针对 `all_to_all_sp2hp` 的具体 **Tensor Shape 变化** 考考你吗？