from __future__ import annotations

import tempfile
import unittest
from pathlib import Path

import pandas as pd

from src.movie_recommender.visualization import generate_figures_from_csv


class VisualizationTests(unittest.TestCase):
    def test_generates_figures_from_csv(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            pd.DataFrame(
                [
                    {
                        "model": "gmf",
                        "epoch": 1,
                        "train_loss": 0.6,
                        "validation_hr@10": 0.5,
                        "validation_ndcg@10": 0.3,
                    },
                    {
                        "model": "mlp",
                        "epoch": 1,
                        "train_loss": 0.5,
                        "validation_hr@10": 0.6,
                        "validation_ndcg@10": 0.4,
                    },
                ]
            ).to_csv(directory / "training_history.csv", index=False)
            pd.DataFrame(
                [
                    {
                        "model": "gmf",
                        "hr@5": 0.3,
                        "ndcg@5": 0.2,
                        "hr@10": 0.5,
                        "ndcg@10": 0.3,
                        "sampled_auc": 0.7,
                    },
                    {
                        "model": "mlp",
                        "hr@5": 0.4,
                        "ndcg@5": 0.3,
                        "hr@10": 0.6,
                        "ndcg@10": 0.4,
                        "sampled_auc": 0.8,
                    },
                ]
            ).to_csv(directory / "test_metrics.csv", index=False)
            figures = generate_figures_from_csv(directory)
            self.assertEqual(len(figures), 2)
            self.assertTrue(all(path.is_file() for path in figures))
            self.assertTrue(all(path.stat().st_size > 0 for path in figures))


if __name__ == "__main__":
    unittest.main()

