from __future__ import annotations

import unittest
from pathlib import Path

from src.movie_recommender.config import load_config
from src.movie_recommender.experiment import run_formal_experiment


class GovernanceTests(unittest.TestCase):
    def test_formal_training_is_disabled(self) -> None:
        root = Path(__file__).resolve().parents[1]
        config_path = root / "configs" / "experiment.toml"
        config = load_config(config_path)
        self.assertFalse(config.formal_training_approved)
        with self.assertRaises(PermissionError):
            run_formal_experiment(
                config,
                root,
                config_path,
                confirmation=True,
            )


if __name__ == "__main__":
    unittest.main()
