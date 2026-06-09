"""Training loop, validation, early stopping, and checkpoint management."""

from __future__ import annotations

import time
from dataclasses import dataclass
from pathlib import Path
from typing import Sequence

import pandas as pd
import torch
from torch import nn
from torch.utils.data import DataLoader

from .data import CandidateSet, DataSplits, PointwiseTrainingDataset
from .evaluator import evaluate_candidate_sets


@dataclass(frozen=True)
class TrainingSettings:
    epochs: int
    batch_size: int
    learning_rate: float
    negatives_per_positive: int
    early_stopping_patience: int
    seed: int
    num_workers: int = 0

    def validate(self) -> None:
        positive_values = {
            "epochs": self.epochs,
            "batch_size": self.batch_size,
            "learning_rate": self.learning_rate,
            "negatives_per_positive": self.negatives_per_positive,
            "early_stopping_patience": self.early_stopping_patience,
        }
        for name, value in positive_values.items():
            if value <= 0:
                raise ValueError(f"{name} must be positive")
        if self.num_workers < 0:
            raise ValueError("num_workers must be non-negative")


@dataclass(frozen=True)
class TrainingResult:
    history: pd.DataFrame
    best_epoch: int
    best_metric: float
    checkpoint_path: Path


def train_one_model(
    model: nn.Module,
    model_name: str,
    splits: DataSplits,
    validation_candidates: Sequence[CandidateSet],
    settings: TrainingSettings,
    device: torch.device,
    output_dir: str | Path,
    primary_metric: str = "ndcg@10",
    cutoffs: Sequence[int] = (5, 10),
    verbose: bool = True,
) -> TrainingResult:
    """Train one model and retain the epoch with best validation performance."""

    settings.validate()
    if not validation_candidates:
        raise ValueError("validation_candidates must not be empty")
    destination = Path(output_dir)
    destination.mkdir(parents=True, exist_ok=True)
    checkpoint_path = destination / f"{model_name}_best.pt"
    history_path = destination / f"{model_name}_history.csv"

    model = model.to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=settings.learning_rate)
    criterion = nn.BCEWithLogitsLoss()
    best_metric = float("-inf")
    best_epoch = 0
    epochs_without_improvement = 0
    history_rows: list[dict[str, float | int | str]] = []

    for epoch in range(1, settings.epochs + 1):
        started_at = time.perf_counter()
        dataset = PointwiseTrainingDataset(
            positive_interactions=splits.train,
            num_items=splits.num_items,
            known_items_by_user=splits.known_items_by_user,
            negatives_per_positive=settings.negatives_per_positive,
            seed=settings.seed + epoch,
        )
        generator = torch.Generator().manual_seed(settings.seed + epoch)
        loader = DataLoader(
            dataset,
            batch_size=settings.batch_size,
            shuffle=True,
            num_workers=settings.num_workers,
            pin_memory=device.type == "cuda",
            generator=generator,
        )

        model.train()
        loss_sum = 0.0
        example_count = 0
        for users, items, labels in loader:
            users = users.to(device, non_blocking=True)
            items = items.to(device, non_blocking=True)
            labels = labels.to(device, non_blocking=True)
            optimizer.zero_grad(set_to_none=True)
            logits = model(users, items)
            loss = criterion(logits, labels)
            loss.backward()
            optimizer.step()
            batch_count = len(labels)
            loss_sum += float(loss.item()) * batch_count
            example_count += batch_count

        validation_metrics = evaluate_candidate_sets(
            model,
            validation_candidates,
            device,
            cutoffs=cutoffs,
        )
        if primary_metric not in validation_metrics:
            raise ValueError(f"Unknown primary metric: {primary_metric}")
        current_metric = validation_metrics[primary_metric]
        row: dict[str, float | int | str] = {
            "model": model_name,
            "epoch": epoch,
            "train_loss": loss_sum / example_count,
            "epoch_seconds": time.perf_counter() - started_at,
        }
        row.update({f"validation_{key}": value for key, value in validation_metrics.items()})
        history_rows.append(row)
        pd.DataFrame(history_rows).to_csv(history_path, index=False)
        if verbose:
            print(
                f"[{model_name}] epoch={epoch:02d} "
                f"loss={row['train_loss']:.6f} "
                f"{primary_metric}={current_metric:.6f} "
                f"seconds={row['epoch_seconds']:.2f}"
            )

        if current_metric > best_metric:
            best_metric = current_metric
            best_epoch = epoch
            epochs_without_improvement = 0
            _save_checkpoint(
                checkpoint_path,
                model,
                optimizer,
                model_name,
                epoch,
                primary_metric,
                current_metric,
            )
        else:
            epochs_without_improvement += 1
            if epochs_without_improvement >= settings.early_stopping_patience:
                break

    if best_epoch == 0 or not checkpoint_path.is_file():
        raise RuntimeError("Training completed without a valid checkpoint")
    load_checkpoint(checkpoint_path, model, device)
    return TrainingResult(
        history=pd.DataFrame(history_rows),
        best_epoch=best_epoch,
        best_metric=best_metric,
        checkpoint_path=checkpoint_path,
    )


def _save_checkpoint(
    path: Path,
    model: nn.Module,
    optimizer: torch.optim.Optimizer,
    model_name: str,
    epoch: int,
    metric_name: str,
    metric_value: float,
) -> None:
    temporary_path = path.with_suffix(path.suffix + ".tmp")
    torch.save(
        {
            "model_name": model_name,
            "epoch": epoch,
            "metric_name": metric_name,
            "metric_value": metric_value,
            "model_state_dict": model.state_dict(),
            "optimizer_state_dict": optimizer.state_dict(),
        },
        temporary_path,
    )
    temporary_path.replace(path)


def load_checkpoint(
    path: str | Path, model: nn.Module, device: torch.device
) -> dict:
    """Load a trusted checkpoint created by this project."""

    checkpoint = torch.load(Path(path), map_location=device, weights_only=True)
    model.load_state_dict(checkpoint["model_state_dict"])
    return checkpoint
