import torch
import torch.nn.functional as F
from torch import nn
from tacotron2.model import Attention, get_mask_from_lengths
torch.manual_seed(20020910)
# 生成随机输入数据
batch_size = 1
max_time = 5
n_mel_channels = 8
n_frames_per_step = 1
attention_rnn_dim = 8
embedding_dim = 4
attention_dim = 6
attention_location_n_filters = 3
attention_location_kernel_size = 5


query = torch.randn(batch_size, n_mel_channels * n_frames_per_step)
processed_memory = torch.randn(batch_size, max_time, attention_dim)
attention_weights_cat = torch.randn(batch_size, 2, max_time)
attention_hidden_state = torch.randn(batch_size, attention_rnn_dim)
memory = torch.randn(batch_size, max_time, embedding_dim)


mask = get_mask_from_lengths(torch.ones(batch_size, )*max_time)

# 创建Attention模块实例
attention = Attention(attention_rnn_dim, embedding_dim, attention_dim, attention_location_n_filters,
                      attention_location_kernel_size)
# 使用生成的输入数据进行测试
attention_context, attention_weights = attention(attention_hidden_state, memory, processed_memory,
                                                 attention_weights_cat, mask)

# 打印结果
print("Attention Context:", attention_context)
print("Attention Weights:", attention_weights)

# 标准答案（可根据实际情况进行修改）
expected_attention_context = torch.Tensor([[-0.7686,  0.4479, -0.3848, -0.3220]])
expected_attention_weights = torch.Tensor([[0.1249, 0.1688, 0.2372, 0.2462, 0.2229]])

# 使用torch.allclose函数与标准答案进行比较
context_match = torch.allclose(attention_context, expected_attention_context, rtol=1e-03, atol=1e-03, equal_nan=False)
weights_match = torch.allclose(attention_weights, expected_attention_weights, rtol=1e-03, atol=1e-03, equal_nan=False)
print("Context Matches Expected:", context_match)
print("Weights Matches Expected:", weights_match)

print("*"*20)
if context_match and weights_match:
    print("Pass!")
else:
    print("Fail!")
print("*"*20)
