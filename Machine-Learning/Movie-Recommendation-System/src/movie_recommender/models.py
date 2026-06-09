"""GMF, MLP, and NeuMF model definitions for implicit recommendation."""

from __future__ import annotations

from collections.abc import Sequence

import torch
from torch import nn


def _validate_dimensions(
    num_users: int, num_items: int, embedding_dim: int
) -> None:
    if num_users <= 0:
        raise ValueError("num_users must be positive")
    if num_items <= 0:
        raise ValueError("num_items must be positive")
    if embedding_dim <= 0:
        raise ValueError("embedding_dim must be positive")


class GMF(nn.Module):
    """Generalized Matrix Factorization with a learnable output layer."""

    def __init__(self, num_users: int, num_items: int, embedding_dim: int) -> None:
        super().__init__()
        _validate_dimensions(num_users, num_items, embedding_dim)
        self.user_embedding = nn.Embedding(num_users, embedding_dim)
        self.item_embedding = nn.Embedding(num_items, embedding_dim)
        self.output = nn.Linear(embedding_dim, 1)
        self.reset_parameters()

    def reset_parameters(self) -> None:
        nn.init.normal_(self.user_embedding.weight, mean=0.0, std=0.01)
        nn.init.normal_(self.item_embedding.weight, mean=0.0, std=0.01)
        nn.init.xavier_uniform_(self.output.weight)
        nn.init.zeros_(self.output.bias)

    def forward(self, users: torch.Tensor, items: torch.Tensor) -> torch.Tensor:
        interaction = self.user_embedding(users) * self.item_embedding(items)
        return self.output(interaction).squeeze(-1)


class MLP(nn.Module):
    """Nonlinear user-item interaction model based on an MLP."""

    def __init__(
        self,
        num_users: int,
        num_items: int,
        embedding_dim: int,
        hidden_layers: Sequence[int],
    ) -> None:
        super().__init__()
        _validate_dimensions(num_users, num_items, embedding_dim)
        if not hidden_layers or any(width <= 0 for width in hidden_layers):
            raise ValueError("hidden_layers must contain positive dimensions")

        self.user_embedding = nn.Embedding(num_users, embedding_dim)
        self.item_embedding = nn.Embedding(num_items, embedding_dim)
        self.hidden = _build_mlp(embedding_dim * 2, hidden_layers)
        self.output = nn.Linear(hidden_layers[-1], 1)
        self.reset_parameters()

    def reset_parameters(self) -> None:
        nn.init.normal_(self.user_embedding.weight, mean=0.0, std=0.01)
        nn.init.normal_(self.item_embedding.weight, mean=0.0, std=0.01)
        _reset_linear_layers(self.hidden)
        nn.init.xavier_uniform_(self.output.weight)
        nn.init.zeros_(self.output.bias)

    def forward(self, users: torch.Tensor, items: torch.Tensor) -> torch.Tensor:
        features = torch.cat(
            [self.user_embedding(users), self.item_embedding(items)], dim=-1
        )
        return self.output(self.hidden(features)).squeeze(-1)


class NeuMF(nn.Module):
    """Neural Matrix Factorization combining GMF and MLP representations."""

    def __init__(
        self,
        num_users: int,
        num_items: int,
        embedding_dim: int,
        hidden_layers: Sequence[int],
    ) -> None:
        super().__init__()
        _validate_dimensions(num_users, num_items, embedding_dim)
        if not hidden_layers or any(width <= 0 for width in hidden_layers):
            raise ValueError("hidden_layers must contain positive dimensions")

        self.gmf_user_embedding = nn.Embedding(num_users, embedding_dim)
        self.gmf_item_embedding = nn.Embedding(num_items, embedding_dim)
        self.mlp_user_embedding = nn.Embedding(num_users, embedding_dim)
        self.mlp_item_embedding = nn.Embedding(num_items, embedding_dim)
        self.hidden = _build_mlp(embedding_dim * 2, hidden_layers)
        self.output = nn.Linear(embedding_dim + hidden_layers[-1], 1)
        self.reset_parameters()

    def reset_parameters(self) -> None:
        for embedding in (
            self.gmf_user_embedding,
            self.gmf_item_embedding,
            self.mlp_user_embedding,
            self.mlp_item_embedding,
        ):
            nn.init.normal_(embedding.weight, mean=0.0, std=0.01)
        _reset_linear_layers(self.hidden)
        nn.init.xavier_uniform_(self.output.weight)
        nn.init.zeros_(self.output.bias)

    def forward(self, users: torch.Tensor, items: torch.Tensor) -> torch.Tensor:
        gmf_features = (
            self.gmf_user_embedding(users) * self.gmf_item_embedding(items)
        )
        mlp_input = torch.cat(
            [self.mlp_user_embedding(users), self.mlp_item_embedding(items)],
            dim=-1,
        )
        combined = torch.cat([gmf_features, self.hidden(mlp_input)], dim=-1)
        return self.output(combined).squeeze(-1)


def _build_mlp(input_dim: int, hidden_layers: Sequence[int]) -> nn.Sequential:
    modules: list[nn.Module] = []
    current_dim = input_dim
    for output_dim in hidden_layers:
        modules.extend([nn.Linear(current_dim, output_dim), nn.ReLU()])
        current_dim = output_dim
    return nn.Sequential(*modules)


def _reset_linear_layers(module: nn.Module) -> None:
    for layer in module.modules():
        if isinstance(layer, nn.Linear):
            nn.init.xavier_uniform_(layer.weight)
            nn.init.zeros_(layer.bias)


def build_model(
    name: str,
    num_users: int,
    num_items: int,
    embedding_dim: int,
    hidden_layers: Sequence[int],
) -> nn.Module:
    """Create one of the three approved recommendation models."""

    normalized_name = name.strip().lower()
    if normalized_name == "gmf":
        return GMF(num_users, num_items, embedding_dim)
    if normalized_name == "mlp":
        return MLP(
            num_users, num_items, embedding_dim, hidden_layers=hidden_layers
        )
    if normalized_name == "neumf":
        return NeuMF(
            num_users, num_items, embedding_dim, hidden_layers=hidden_layers
        )
    raise ValueError(f"Unsupported model: {name}")


def count_trainable_parameters(model: nn.Module) -> int:
    """Return the number of parameters updated during training."""

    return sum(parameter.numel() for parameter in model.parameters() if parameter.requires_grad)
