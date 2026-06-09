"""Figures generated exclusively from saved raw experiment records."""

from __future__ import annotations

from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import pandas as pd


def plot_training_history(
    history: pd.DataFrame, output_path: str | Path
) -> Path:
    """Plot training loss and validation HR/NDCG from a history CSV."""

    required = {
        "model",
        "epoch",
        "train_loss",
        "validation_hr@10",
        "validation_ndcg@10",
    }
    _require_columns(history, required)
    destination = Path(output_path)
    destination.parent.mkdir(parents=True, exist_ok=True)

    figure, axes = plt.subplots(1, 3, figsize=(15, 4.5))
    for model_name, rows in history.groupby("model", sort=False):
        rows = rows.sort_values("epoch")
        axes[0].plot(rows["epoch"], rows["train_loss"], marker="o", label=model_name)
        axes[1].plot(
            rows["epoch"], rows["validation_hr@10"], marker="o", label=model_name
        )
        axes[2].plot(
            rows["epoch"], rows["validation_ndcg@10"], marker="o", label=model_name
        )
    titles = ("Training Loss", "Validation HR@10", "Validation NDCG@10")
    for axis, title in zip(axes, titles):
        axis.set_title(title)
        axis.set_xlabel("Epoch")
        axis.grid(alpha=0.3)
        axis.legend()
    figure.tight_layout()
    figure.savefig(destination, dpi=200, bbox_inches="tight")
    plt.close(figure)
    return destination


def plot_model_comparison(
    metrics: pd.DataFrame, output_path: str | Path
) -> Path:
    """Create a grouped bar chart from the untouched metrics CSV."""

    metric_columns = ["hr@5", "ndcg@5", "hr@10", "ndcg@10", "sampled_auc"]
    _require_columns(metrics, {"model", *metric_columns})
    destination = Path(output_path)
    destination.parent.mkdir(parents=True, exist_ok=True)

    chart_data = metrics.set_index("model")[metric_columns]
    axis = chart_data.plot(kind="bar", figsize=(10, 5.5), width=0.8)
    axis.set_title("Test Metric Comparison")
    axis.set_xlabel("Model")
    axis.set_ylabel("Metric Value")
    axis.set_ylim(0, 1)
    axis.grid(axis="y", alpha=0.3)
    axis.legend(loc="lower right")
    plt.xticks(rotation=0)
    figure = axis.get_figure()
    figure.tight_layout()
    figure.savefig(destination, dpi=200, bbox_inches="tight")
    plt.close(figure)
    return destination


def generate_figures_from_csv(output_dir: str | Path) -> list[Path]:
    """Regenerate all figures without changing any experiment values."""

    directory = Path(output_dir)
    history_path = directory / "training_history.csv"
    metrics_path = directory / "test_metrics.csv"
    if not history_path.is_file() or not metrics_path.is_file():
        raise FileNotFoundError(
            "training_history.csv and test_metrics.csv are required"
        )
    figures_dir = directory / "figures"
    return [
        plot_training_history(
            pd.read_csv(history_path), figures_dir / "training_history.png"
        ),
        plot_model_comparison(
            pd.read_csv(metrics_path), figures_dir / "model_comparison.png"
        ),
    ]


def _require_columns(frame: pd.DataFrame, required: set[str]) -> None:
    missing = sorted(required.difference(frame.columns))
    if missing:
        raise ValueError(f"Missing columns: {missing}")
