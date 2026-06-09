"""Ranking metrics for one-positive sampled recommendation evaluation."""

from __future__ import annotations

import math
from collections.abc import Sequence

import numpy as np


def rank_of_positive(scores: Sequence[float], labels: Sequence[float]) -> int:
    """Return the one-based rank of the single positive candidate."""

    score_array = np.asarray(scores, dtype=np.float64)
    label_array = np.asarray(labels, dtype=np.float64)
    if score_array.ndim != 1 or label_array.ndim != 1:
        raise ValueError("scores and labels must be one-dimensional")
    if len(score_array) == 0 or len(score_array) != len(label_array):
        raise ValueError("scores and labels must have the same non-zero length")
    positive_indices = np.flatnonzero(label_array == 1)
    if len(positive_indices) != 1:
        raise ValueError("Exactly one positive label is required")
    if not np.isfinite(score_array).all():
        raise ValueError("scores must be finite")

    # Stable sorting makes ties deterministic and preserves candidate order.
    ranking = np.argsort(-score_array, kind="mergesort")
    return int(np.flatnonzero(ranking == positive_indices[0])[0]) + 1


def hit_rate_at_k(rank: int, k: int) -> float:
    _validate_rank_and_k(rank, k)
    return float(rank <= k)


def ndcg_at_k(rank: int, k: int) -> float:
    _validate_rank_and_k(rank, k)
    return 1.0 / math.log2(rank + 1) if rank <= k else 0.0


def sampled_auc(scores: Sequence[float], labels: Sequence[float]) -> float:
    """Compute AUC for one positive against sampled negative candidates."""

    score_array = np.asarray(scores, dtype=np.float64)
    label_array = np.asarray(labels, dtype=np.float64)
    positive_indices = np.flatnonzero(label_array == 1)
    negative_indices = np.flatnonzero(label_array == 0)
    if len(positive_indices) != 1 or len(negative_indices) == 0:
        raise ValueError("AUC requires one positive and at least one negative")
    positive_score = score_array[positive_indices[0]]
    negative_scores = score_array[negative_indices]
    wins = np.sum(positive_score > negative_scores)
    ties = np.sum(positive_score == negative_scores)
    return float((wins + 0.5 * ties) / len(negative_scores))


def metrics_for_candidate_set(
    scores: Sequence[float],
    labels: Sequence[float],
    cutoffs: Sequence[int] = (5, 10),
) -> dict[str, float]:
    """Calculate all approved metrics for one user's candidate set."""

    rank = rank_of_positive(scores, labels)
    result: dict[str, float] = {"sampled_auc": sampled_auc(scores, labels)}
    for k in cutoffs:
        if k <= 0:
            raise ValueError("Metric cutoffs must be positive")
        result[f"hr@{k}"] = hit_rate_at_k(rank, k)
        result[f"ndcg@{k}"] = ndcg_at_k(rank, k)
    return result


def average_metric_rows(rows: Sequence[dict[str, float]]) -> dict[str, float]:
    """Average per-user metric dictionaries with identical keys."""

    if not rows:
        raise ValueError("At least one metric row is required")
    keys = set(rows[0])
    if any(set(row) != keys for row in rows):
        raise ValueError("All metric rows must contain the same keys")
    return {key: float(np.mean([row[key] for row in rows])) for key in sorted(keys)}


def _validate_rank_and_k(rank: int, k: int) -> None:
    if rank <= 0:
        raise ValueError("rank must be positive")
    if k <= 0:
        raise ValueError("k must be positive")
