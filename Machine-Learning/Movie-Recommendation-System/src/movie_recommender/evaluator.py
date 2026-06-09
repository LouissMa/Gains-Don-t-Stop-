"""Shared candidate-set evaluation and recommendation generation."""

from __future__ import annotations

from collections.abc import Mapping, Sequence

import numpy as np
import pandas as pd
import torch
from torch import nn

from .data import CandidateSet, DataSplits
from .metrics import average_metric_rows, metrics_for_candidate_set


@torch.inference_mode()
def score_user_items(
    model: nn.Module,
    user_idx: int,
    item_indices: Sequence[int] | np.ndarray,
    device: torch.device,
    batch_size: int = 4096,
) -> np.ndarray:
    """Score item candidates in batches and return raw model logits."""

    if batch_size <= 0:
        raise ValueError("batch_size must be positive")
    items = np.asarray(item_indices, dtype=np.int64)
    if items.ndim != 1 or len(items) == 0:
        raise ValueError("item_indices must be a non-empty one-dimensional sequence")

    model.eval()
    score_parts: list[np.ndarray] = []
    for start in range(0, len(items), batch_size):
        item_batch = torch.as_tensor(
            items[start : start + batch_size], dtype=torch.long, device=device
        )
        user_batch = torch.full_like(item_batch, fill_value=user_idx)
        score_parts.append(model(user_batch, item_batch).detach().cpu().numpy())
    return np.concatenate(score_parts)


@torch.inference_mode()
def evaluate_candidate_sets(
    model: nn.Module,
    candidate_sets: Sequence[CandidateSet],
    device: torch.device,
    cutoffs: Sequence[int] = (5, 10),
    batch_size: int = 4096,
) -> dict[str, float]:
    """Evaluate one model on candidate sets shared across all models."""

    if not candidate_sets:
        raise ValueError("candidate_sets must not be empty")
    rows: list[dict[str, float]] = []
    for candidate_set in candidate_sets:
        scores = score_user_items(
            model,
            candidate_set.user_idx,
            candidate_set.item_indices,
            device,
            batch_size,
        )
        rows.append(
            metrics_for_candidate_set(scores, candidate_set.labels, cutoffs)
        )
    return average_metric_rows(rows)


@torch.inference_mode()
def recommend_unrated_items(
    model: nn.Module,
    user_idx: int,
    splits: DataSplits,
    movies: pd.DataFrame,
    device: torch.device,
    top_k: int = 10,
    batch_size: int = 4096,
) -> pd.DataFrame:
    """Rank every unrated item and attach original movie metadata."""

    if top_k <= 0:
        raise ValueError("top_k must be positive")
    if user_idx not in splits.known_items_by_user:
        raise ValueError(f"Unknown user index: {user_idx}")

    known = splits.known_items_by_user[user_idx]
    candidates = np.fromiter(
        (item for item in range(splits.num_items) if item not in known),
        dtype=np.int64,
    )
    if len(candidates) == 0:
        raise ValueError("The user has no unrated items")
    scores = score_user_items(model, user_idx, candidates, device, batch_size)
    limit = min(top_k, len(candidates))
    top_positions = np.argsort(-scores, kind="mergesort")[:limit]

    title_by_id: Mapping[int, str] = movies.set_index("item_id")["title"].to_dict()
    genres_by_id: Mapping[int, str] = movies.set_index("item_id")["genres"].to_dict()
    rows = []
    for rank, position in enumerate(top_positions, start=1):
        item_idx = int(candidates[position])
        item_id = splits.index_to_item[item_idx]
        rows.append(
            {
                "rank": rank,
                "user_idx": user_idx,
                "user_id": splits.index_to_user[user_idx],
                "item_idx": item_idx,
                "item_id": item_id,
                "title": title_by_id[item_id],
                "genres": genres_by_id[item_id],
                "score": float(scores[position]),
            }
        )
    return pd.DataFrame(rows)
