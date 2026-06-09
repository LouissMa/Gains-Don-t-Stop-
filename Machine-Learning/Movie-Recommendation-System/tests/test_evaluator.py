from __future__ import annotations

import unittest

import numpy as np
import torch
from torch import nn

from src.movie_recommender.data import CandidateSet
from src.movie_recommender.evaluator import (
    evaluate_candidate_sets,
    recommend_unrated_items,
    score_user_items,
)
from tests.helpers import make_small_movies, make_small_splits


class ItemScoreModel(nn.Module):
    def forward(self, users: torch.Tensor, items: torch.Tensor) -> torch.Tensor:
        return items.float()


class EvaluatorTests(unittest.TestCase):
    def setUp(self) -> None:
        self.model = ItemScoreModel()
        self.device = torch.device("cpu")

    def test_scores_in_original_order(self) -> None:
        scores = score_user_items(
            self.model, 0, [3, 1, 4], self.device, batch_size=2
        )
        np.testing.assert_array_equal(scores, [3.0, 1.0, 4.0])

    def test_evaluates_fixed_candidates(self) -> None:
        candidates = [
            CandidateSet(
                user_idx=0,
                target_item_idx=4,
                item_indices=np.asarray([4, 1, 2]),
                labels=np.asarray([1.0, 0.0, 0.0]),
            )
        ]
        metrics = evaluate_candidate_sets(
            self.model, candidates, self.device, cutoffs=(1, 2)
        )
        self.assertEqual(metrics["hr@1"], 1.0)
        self.assertEqual(metrics["sampled_auc"], 1.0)

    def test_recommendations_exclude_known_items(self) -> None:
        splits = make_small_splits()
        result = recommend_unrated_items(
            self.model,
            user_idx=0,
            splits=splits,
            movies=make_small_movies(),
            device=self.device,
            top_k=3,
        )
        self.assertEqual(len(result), 3)
        self.assertTrue(
            set(result["item_idx"]).isdisjoint(splits.known_items_by_user[0])
        )
        self.assertTrue(result["score"].is_monotonic_decreasing)


if __name__ == "__main__":
    unittest.main()

