
没有使用传统的 Critic 网络（Value Function），那么模型是如何判断哪一手牌打得好呢？这就是 **Reinforce++** 的精髓。

## 1. 核心公式：从 Reinforce 到 Reinforce++

传统的 Reinforce 算法方差极大，像是在黑暗中乱撞。Reinforce++ 通过两个关键改进压制了方差：

### A. 优势估计 (Advantage Estimation)

优势 $A_t$ 不是由模型预测的，而是通过 **Batch 均值基准 (Mean Baseline)** 计算的：


$$A_t = \text{Return} - \text{Baseline}$$


其中，$\text{Baseline} = \text{mean}(\text{Batch Returns})$。

* **Ques**：为什么要减均值？
*
* **Ans**：因为斗地主每局的初始牌力差距巨大。如果这把牌天生大王小王四个 2，赢了不代表模型打得好。减去当前 Batch 的平均得分，能抵消掉“牌力天注定”带来的干扰，让模型只学习**超过平均水平**的操作。

### B. 这种“++”在哪？

**重要性采样 (Importance Sampling)**：引入了 $min(r_t(\theta), \text{clip})$，虽然名字叫 Reinforce++，但它借鉴了 PPO 的截断机制，防止参数更新步子迈得太大。

$min(r_t(\theta), \text{clip})$ 的含义：给梯度装上“刹车”

其实是 PPO 截断机制（Clipped Surrogate Objective） 的核心。

$r_t(\theta)$ (Ratio)：它是当前新策略输出某个动作的概率 $P_{\theta}$ 除以采样时旧策略的概率 $P_{old}$。$$r_t(\theta) = \frac{P_{\theta}(a|s)}{P_{old}(a|s)}$$

含义：它衡量了“这次参数更新后，模型对这个动作的偏好改变了多少”。

为什么要 Clip（截断）？强化学习非常容易“练歪”。如果某一局斗地主赢了大分，梯度更新可能会让模型疯狂向那个动作靠拢。

如果 $r_t(\theta)$ 变成 10（意味着新策略比旧策略激进了 10 倍），这会导致模型崩溃。

Clip 就像一个安全阀：即使这一局赢了 100 分，我也只允许策略在 1+$\epsilon$（比如 1.2 倍）的范围内微调。

eps_clip: 0.2：意味着单次更新，模型对某个动作的概率变化幅度被限制在 [0.8, 1.2] 之间。

 **多轮采样稳定性**：配置中的 `global_batch_size: 256` 保证了计算均值基准时的统计学意义。

算法与硬件的“甜点位”

这个参数定义了 Learner（训练器）每次“吃”多少数据来更新一次参数。

它由 micro_batch_size × data_parallel_size × gradient_accumulation_steps 得到。

为什么选 256？

在 4 张 A800 上，256 是经过压榨后的结果，原因有三：

A. 算法稳定性：Reinforce++ 的 Baseline 精度由于你没有 Critic 网络，你的 Advantage 是通过 $R - \bar{R}$ 计算的。

如果 Batch Size 太小（比如 32），这 32 局里的平均得分 $\bar{R}$ 随机性太大（可能正好这 32 局牌都极好或极坏）。256 个样本能提供一个相对稳定的“全局平均分”基准，让 Advantage 估计更准确，减少方差。

B. 硬件效率：A800 的算力对齐显存占用：Qwen3-8B 在 TP2 下，每张卡承载约 4B 参数。开启 offload_train 和 FlashAttention 后，单卡显存能容纳的样本数有限。

计算强度：如果 Batch Size 太小，GPU 的 Tensor Cores 吃不饱，大部分时间花在节点间通信上。256 能让 A800 的计算利用率（MFU）达到一个较高的水平，不至于让 Learner 等待数据。

C. 通信开销（TP2 架构）由于你使用了 tensor_model_parallel_size: 每一步更新都需要在 GPU 0-1 之间进行 All-Reduce 通信。

大 Batch 意味着更少的通信频率。更新一次 256 样本的梯度，比更新八次 32 样本的梯度，总耗时要短得多。“如果我想把 Batch Size 调到 1024 怎么办？”
你的满分回答：

“如果为了进一步稳定梯度想扩到 1024，在单机 4 卡 A800 上会面临 OOM（显存溢出） 的风险。

方案一：增加 gradient_accumulation_steps（梯度累加）。比如设置 micro_batch 为 1，累加 256 步，实现逻辑上的大 Batch，但这会牺牲训练速度。

方案二：进一步压榨显存，比如开启 recompute_num_layers（重计算）或者更激进的 activation_checkpointing。

方案三：在采样侧（Rollout），利用 SGLang 的异步能力，确保存储 Buffer 里的样本足够多，从而支持 Learner 进行更大规模的并行训练。”

## 2. Token-level Reward 分解逻辑

这是你最开始问的 KL 散度与胜负奖励的结合。在 `ppo_utils.py` 的实现中，每个 Token 拿到的奖励 $r_t$ 是复合的：

$$r_t = \underbrace{-\beta \cdot D_{KL}(P_t \parallel Q_t)}_{\text{局部约束 (KL)}} + \underbrace{\delta(t = T) \cdot R_{\text{win/loss}}}_{\text{全局信号 (Sparse Reward)}}$$

* **KL 部分**：每个 Token 都在被参考模型（SFT）盯着，说错话立刻扣分。
* 
* **Sparse Reward 部分**：只有在序列最后一个 Token（`last_idx`），才会加上那局棋/牌的最终胜负分（+1 或 -1）。
*
* **Advantage 传播**：通过 Backwards Discounted Loop，最后的胜负分会随着 $\gamma=1$（你的配置值）传回给前面的每一个动作。

## 3. 为什么不用 Critic 网络？

1. **资源利用率**：在 4 张 A800 上，如果要跑 TP2 的 Policy + TP2 的 Reference + TP2 的 Critic，显存会极其紧张。去掉 Critic 换成 Reinforce++，能腾出显存给更大的 Batch Size。

2. **信噪比问题**：斗地主这种博弈游戏的 Value 极其难估准（状态空间太大）。一个训练不好的 Critic 反而会提供错误的梯度信号。

使用 **Batch Baseline** 虽然简单，但它提供的是“无偏估计”，在数据量足够（5000 条 rollout）时更加稳健。

---

## 4. 你的配置参数对算法的支撑

* **`kl_loss_type: low_var_kl`**：
这是实现中的细节。它不是直接算 $\log(P/Q)$，而是使用类似 $(P/Q - 1) - \log(P/Q)$ 的展开式。这种方式在 $P$ 和 $Q$ 接近时方差更小，能让训练曲线更平滑。
* **`normalize_advantages: true`**：
在算出 $A_t$ 后，再除以标准差进行归一化。这保证了无论这局分打得多大，梯度更新的量级始终在一个可控范围内。
