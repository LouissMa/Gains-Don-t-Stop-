"""Configuration loading and validation."""

from __future__ import annotations

import tomllib
from dataclasses import dataclass
from pathlib import Path
from typing import Any


@dataclass(frozen=True)
class ExperimentConfig:
    """Validated experiment configuration sections."""

    project: dict[str, Any]
    paths: dict[str, Any]
    data: dict[str, Any]
    models: dict[str, Any]
    training: dict[str, Any]
    evaluation: dict[str, Any]
    governance: dict[str, Any]

    @property
    def formal_training_approved(self) -> bool:
        return bool(self.governance["formal_training_approved"])


REQUIRED_SECTIONS = (
    "project",
    "paths",
    "data",
    "models",
    "training",
    "evaluation",
    "governance",
)


def load_config(path: str | Path) -> ExperimentConfig:
    """Load a TOML file and perform stage-one structural validation."""

    config_path = Path(path)
    if not config_path.is_file():
        raise FileNotFoundError(f"Configuration file not found: {config_path}")

    with config_path.open("rb") as file:
        raw = tomllib.load(file)

    missing = [section for section in REQUIRED_SECTIONS if section not in raw]
    if missing:
        raise ValueError(f"Missing configuration sections: {', '.join(missing)}")

    model_names = raw["models"].get("names", [])
    if model_names != ["gmf", "mlp", "neumf"]:
        raise ValueError("Model order must be: gmf, mlp, neumf")

    if raw["data"].get("split_strategy") != "leave-one-out-by-time":
        raise ValueError("Only the approved time-based leave-one-out split is allowed")

    training = raw["training"]
    positive_training_values = (
        "epochs",
        "batch_size",
        "learning_rate",
        "early_stopping_patience",
    )
    for key in positive_training_values:
        if training.get(key, 0) <= 0:
            raise ValueError(f"training.{key} must be positive")
    if training.get("num_workers", -1) < 0:
        raise ValueError("training.num_workers must be non-negative")
    if training.get("optimizer") != "adam":
        raise ValueError("Only the approved Adam optimizer is supported")
    if training.get("loss") != "binary-cross-entropy":
        raise ValueError("Only binary cross-entropy loss is supported")
    if raw["evaluation"].get("primary_metric") not in raw["evaluation"].get(
        "metrics", []
    ):
        raise ValueError("Primary metric must appear in the metric list")

    return ExperimentConfig(**{name: raw[name] for name in REQUIRED_SECTIONS})
