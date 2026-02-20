from typing import Tuple
import numpy as np
from einops import einsum, rearrange

############################################################
# Problem 1


def linear_project(x: np.ndarray, W: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
    Compute a batched linear projection using einsum from einops.

    Shapes:
    - x: (batch, d_in)
    - W: (d_in, d_out)
    - b: (d_out,)
    Returns:
    - y: (batch, d_out) where y = x * W + b

    Implementation notes:
    - Use einsum from einops for the matrix multiplication (no @ operator).
    - Use NumPy broadcasting for the bias addition.
    - No Python loops.
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    # END_YOUR_CODE


def split_last_dim_pattern() -> str:
    """
    Return an einops.rearrange pattern string that reshapes
    (B, D) -> (B, G, D/G), where G is provided as a keyword
    (e.g., g=num_groups) when applying rearrange.

    I.e., your returned string `pattern`would be used as follows:
    >>> y = rearrange(x, pattern, g=num_groups)
    where x is a tensor with shape (B, D).
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    # END_YOUR_CODE


def normalized_inner_products(A: np.ndarray, C: np.ndarray, normalize: bool = True) -> np.ndarray:
    """
    Batched all-pairs dot products, optionally scaled by 1/sqrt(d).

    Board-style intro:
    - Let A in R^{B x M x D} and C in R^{B x N x D}.
    - For each batch b, form S[b,i,j] = <A[b,i,:], C[b,j,:]> giving S in R^{B x M x N}.
    - If normalize is True, scale S by 1/sqrt(D) to keep magnitudes comparable across D.

    Shapes:
    - A: (batch, m, d)
    - C: (batch, n, d)
    Returns:
    - S: (batch, m, n) with S[b,i,j] = <A[b,i], C[b,j]>.

    Implementation notes:
    - Use einsum from einops for the contraction (no @ operator or loops).
    - Think about the Einstein notation pattern for batched dot products.
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    # END_YOUR_CODE


def mask_strictly_upper(scores: np.ndarray) -> np.ndarray:
    """
    Mask strictly upper-triangular entries (j > i) to -np.inf via broadcasting.

    Board-style intro:
    - Let scores in R^{B x L x L} be a batch of square matrices.
    - For each matrix, we want to set entries with column index j greater than row index i to -inf.
    - Construct the boolean mask using broadcasted index grids; avoid loops.

    Shapes:
    - scores: (batch, L, L)
    Returns:
    - masked_scores: (batch, L, L) where entries with column > row are -inf.

    Use NumPy broadcasting to construct and apply the mask without loops.
    Note that the data type should be floats.
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    # END_YOUR_CODE


def prob_weighted_sum_einsum() -> str:
    """
    Batch probability-weighted sums over value vectors using einsum.

    Board-style intro:
    - Let P in R^{B x N} be per-batch probability weights (each row sums to 1).
    - Let V in R^{B x N x D} be per-batch value vectors aligned with P along N.
    - Compute out[b,:] = sum_{j=1..N} P[b,j] * V[b,j,:] in R^{D} for each batch b.

    Return a einops.einsum string that computes out = sum_j P[b,j] * V[b,j,:]
    for shapes P:(B,N), V:(B,N,D) -> out:(B,D).

    I.e., your returned string `pattern` would be used as follows:
    >>> out = einops.einsum(P, V, pattern)
    where P is a tensor with shape (B, N) and V is a tensor with shape (B, N, D).
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    # END_YOUR_CODE


############################################################
# Problem 2


def gradient_warmup(w: np.ndarray, c: np.ndarray) -> np.ndarray:
    """
    Compute the gradient of f(w) = sum_i (w_i - c_i)^2 with respect to w.

    Inputs:
    - w: (d,)
    - c: (d,)
    Returns:
    - grad: (d,)
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    # END_YOUR_CODE


def matrix_grad(A: np.ndarray, B: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
    """
    For s = sum_{i,j} (A B)_{i,j}, compute gradients wrt A and B.

    If A is (m, p) and B is (p, n):
    - grad_A[i, k] = sum_j B[k, j]  (independent of i)
    - grad_B[k, j] = sum_i A[i, k]  (independent of j)

    Returns (grad_A, grad_B) with the same shapes as A and B, respectively.

    Implementation notes:
    - Consider using einsum from einops for computing sums over dimensions.
    - Alternatively, NumPy sum operations are acceptable for this problem.
    - Use broadcasting to replicate values to the correct shapes.
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    ones_m_p = np.ones((A.shape[0], B.shape[1]))     # shape (m, p)
    
    grad_A = ones_m_p @ B.T                           # (m,p) @ (p,n) → (m,n)
    grad_B = A.T @ ones_m_p                           # (n,m) @ (m,p) → (n,p)
    
    return grad_A, grad_B
    # END_YOUR_CODE


def lsq_grad(w: np.ndarray, A: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
    Analytic gradient for f(w) = 1/2 * ||A w - b||_2^2 with respect to w.

    Inputs:
    - w: (d,)
    - A: (n, d)
    - b: (n,)
    Returns:
    - grad: (d,) = A^T (A w - b)

    Implementation notes:
    - Consider using einsum from einops for matrix-vector operations.
    - Alternatively, NumPy @ operator is acceptable here for simplicity.
    - No Python loops.
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    re = A @ w - b
    grad = A.T @ re
    return grad
    # END_YOUR_CODE

def lsq_objective(w, A, b):
    """辅助函数：计算 1/2 ||Aw - b||^2"""
    residual = A @ w - b
    return 0.5 * np.sum(residual**2)

def lsq_finite_diff_grad(w: np.ndarray,
                         A: np.ndarray,
                         b: np.ndarray,
                         epsilon: float = 1e-5) -> np.ndarray:
    """
    Central-difference numerical gradient for f(w) = 1/2 * ||A w - b||_2^2.

    Inputs:
    - w: (d,)
    - A: (n, d)
    - b: (n,)
    - epsilon: small step size for finite differences
    Returns:
    - grad_fd: (d,)

    Implementation notes:
    - Compute each component using central differences.
    - Vectorize the computation using NumPy broadcasting.
    - Consider using einsum from einops for matrix-vector operations.
    - No Python loops over gradient components.
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    n = len(w)
    grad_approx = np.zeros(n)
    identity = np.eye(n)
    for i in range(n):
        ui = identity[i]
        f_plus = lsq_objective(w + epsilon * ui, A, b)
        f_minus = lsq_objective(w - epsilon * ui, A, b)
        grad_approx[i] = (f_plus - f_minus) / (2 * epsilon)
    return grad_approx
    # END_YOUR_CODE


############################################################
# Problem 3c


def gradient_descent_quadratic(x: np.ndarray, w: np.ndarray, theta0: float, lr: float,
                               num_steps: int) -> float:
    """
    Minimize f(θ) = sum_i w_i * (θ - x_i)^2 with gradient descent in 1D.

    Inputs:
    - x: (n,) data values
    - w: (n,) positive weights
    - theta0: initial scalar θ
    - lr: learning rate (stepsize)
    - num_steps: number of gradient steps (non-negative integer)

    Returns:
    - theta: final scalar after num_steps updates

    Gradient: df/dθ = 2 * sum_i w_i * (θ - x_i).
    """
    # BEGIN_YOUR_CODE
    # TODO: Implement
    for i in range(num_steps):
        grad = 2 * np.sum(w * (theta0 - x))
        theta0 = theta0 - lr * df
    # END_YOUR_CODE
