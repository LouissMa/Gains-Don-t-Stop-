from __future__ import annotations

import math
import unittest

from src.movie_recommender.metrics import (
    average_metric_rows,
    metrics_for_candidate_set,
    rank_of_positive,
    sampled_auc,
)


class MetricTests(unittest.TestCase):
    def test_perfect_ranking(self) -> None:
        scores = [0.9, 0.3, 0.1]
        labels = [1, 0, 0]
        result = metrics_for_candidate_set(scores, labels, cutoffs=(1, 2))
        self.assertEqual(rank_of_positive(scores, labels), 1)
        self.assertEqual(result["hr@1"], 1.0)
        self.assertEqual(result["ndcg@1"], 1.0)
        self.assertEqual(result["sampled_auc"], 1.0)

    def test_known_rank_and_auc(self) -> None:
        scores = [0.5, 0.8, 0.2]
        labels = [1, 0, 0]
        result = metrics_for_candidate_set(scores, labels, cutoffs=(1, 2))
        self.assertEqual(rank_of_positive(scores, labels), 2)
        self.assertEqual(result["hr@1"], 0.0)
        self.assertEqual(result["hr@2"], 1.0)
        self.assertAlmostEqual(result["ndcg@2"], 1 / math.log2(3))
        self.assertEqual(sampled_auc(scores, labels), 0.5)

    def test_tie_auc_and_average(self) -> None:
        self.assertEqual(sampled_auc([0.5, 0.5, 0.1], [1, 0, 0]), 0.75)
        averaged = average_metric_rows(
            [{"hr@10": 1.0, "ndcg@10": 0.5}, {"hr@10": 0.0, "ndcg@10": 1.0}]
        )
        self.assertEqual(averaged, {"hr@10": 0.5, "ndcg@10": 0.75})

    def test_rejects_invalid_positive_count(self) -> None:
        with self.assertRaises(ValueError):
            rank_of_positive([0.5, 0.4], [0, 0])
        with self.assertRaises(ValueError):
            rank_of_positive([0.5, 0.4], [1, 1])


if __name__ == "__main__":
    unittest.main()

