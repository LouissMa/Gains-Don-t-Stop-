from einops import rearrange
import numpy as np
from einops import einsum

"""
d.
'm k, k -> m'
'm k, p k -> m q'
'm k, m k -> k'

e.
y = einsum(X,W,'b i,i j -> b j') + b

f.
'b d -> b g (d/g)'

g.
S = einsum(A, C, 'b m d, b n d -> b m n')

# 如果需要归一化
if normalize:
    S = S / np.sqrt(D)


"""
def mask_strictly_upper(scores):
    B,L,_ = scores.shape
    return np.where(
        np.arange(L)[:, None] < np.arange(L),   # (L,L) → j > i 的位置为 True
        -np.inf,
        scores
    )

scores = np.array([
    [[1, 4, 7],
     [2, 5, 8],
     [3, 6, 9]]
])  # shape (1,3,3)

masked = mask_strictly_upper(scores)
print(masked)