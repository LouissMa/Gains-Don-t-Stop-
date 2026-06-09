from __future__ import annotations

import unittest

import torch
from torch import nn

from src.movie_recommender.models import (
    GMF,
    MLP,
    NeuMF,
    build_model,
    count_trainable_parameters,
)


class ModelTests(unittest.TestCase):
    def setUp(self) -> None:
        self.users = torch.tensor([0, 1, 2, 3], dtype=torch.long)
        self.items = torch.tensor([1, 2, 3, 4], dtype=torch.long)

    def test_all_models_return_one_logit_per_pair(self) -> None:
        models = [
            GMF(5, 8, 4),
            MLP(5, 8, 4, [8, 4]),
            NeuMF(5, 8, 4, [8, 4]),
        ]
        for model in models:
            logits = model(self.users, self.items)
            self.assertEqual(tuple(logits.shape), (4,))
            self.assertTrue(torch.isfinite(logits).all())

    def test_models_support_backward_pass(self) -> None:
        labels = torch.tensor([1.0, 0.0, 1.0, 0.0])
        for name in ("gmf", "mlp", "neumf"):
            model = build_model(name, 5, 8, 4, [8, 4])
            loss = nn.BCEWithLogitsLoss()(model(self.users, self.items), labels)
            loss.backward()
            gradients = [
                parameter.grad
                for parameter in model.parameters()
                if parameter.requires_grad
            ]
            self.assertTrue(all(gradient is not None for gradient in gradients))
            self.assertGreater(count_trainable_parameters(model), 0)

    def test_factory_rejects_unknown_model(self) -> None:
        with self.assertRaises(ValueError):
            build_model("unknown", 5, 8, 4, [8, 4])

    def test_invalid_dimensions_are_rejected(self) -> None:
        with self.assertRaises(ValueError):
            GMF(0, 8, 4)
        with self.assertRaises(ValueError):
            MLP(5, 8, 4, [])


if __name__ == "__main__":
    unittest.main()
