from __future__ import annotations

import tempfile
import unittest
from pathlib import Path

import torch

from src.movie_recommender.data import build_evaluation_candidates
from src.movie_recommender.models import build_model
from src.movie_recommender.reproducibility import set_global_seed
from src.movie_recommender.trainer import TrainingSettings, train_one_model
from tests.helpers import make_small_splits


class TrainerTests(unittest.TestCase):
    def test_small_training_updates_and_saves_checkpoint(self) -> None:
        splits = make_small_splits()
        candidates = build_evaluation_candidates(
            splits.validation, splits, negatives_per_user=2, seed=40
        )
        set_global_seed(123)
        model = build_model("mlp", splits.num_users, splits.num_items, 4, [8, 4])
        initial = {
            name: parameter.detach().clone()
            for name, parameter in model.named_parameters()
        }
        settings = TrainingSettings(
            epochs=2,
            batch_size=4,
            learning_rate=0.01,
            negatives_per_positive=1,
            early_stopping_patience=2,
            seed=123,
        )
        with tempfile.TemporaryDirectory() as temporary:
            result = train_one_model(
                model,
                "mlp",
                splits,
                candidates,
                settings,
                torch.device("cpu"),
                temporary,
                primary_metric="ndcg@10",
                verbose=False,
            )
            self.assertTrue(result.checkpoint_path.is_file())
            self.assertTrue((Path(temporary) / "mlp_history.csv").is_file())
            self.assertGreaterEqual(result.best_epoch, 1)
            self.assertLessEqual(result.best_epoch, 2)
            self.assertEqual(len(result.history), 2)
        changed = any(
            not torch.equal(initial[name], parameter.detach())
            for name, parameter in model.named_parameters()
        )
        self.assertTrue(changed)


if __name__ == "__main__":
    unittest.main()
