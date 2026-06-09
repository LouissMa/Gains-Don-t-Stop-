"""Formal experiment orchestration with audit and overwrite safeguards."""

from __future__ import annotations

import shutil
from pathlib import Path

import pandas as pd
import torch

from .config import ExperimentConfig
from .data import (
    build_evaluation_candidates,
    load_movielens_100k,
    prepare_implicit_splits,
)
from .evaluator import evaluate_candidate_sets, recommend_unrated_items
from .models import build_model, count_trainable_parameters
from .reproducibility import (
    collect_environment_metadata,
    set_global_seed,
    sha256_file,
    write_json,
)
from .trainer import TrainingSettings, load_checkpoint, train_one_model
from .visualization import generate_figures_from_csv


def run_formal_experiment(
    config: ExperimentConfig,
    project_root: str | Path,
    config_path: str | Path,
    confirmation: bool,
) -> Path:
    """Run the approved full experiment and persist an auditable record."""

    if not config.formal_training_approved:
        raise PermissionError(
            "Formal training is disabled in the configuration. "
            "Do not change it until the experiment parameters are approved."
        )
    if not confirmation:
        raise PermissionError("Explicit formal-training confirmation is required")

    root = Path(project_root)
    output_dir = root / config.paths["formal_output_dir"]
    _prepare_formal_output_directory(
        output_dir,
        allow_overwrite=bool(
            config.governance["allow_overwrite_formal_outputs"]
        ),
    )

    seed = int(config.training["seed"])
    set_global_seed(seed)
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    raw_data_dir = root / config.paths["raw_data_dir"]
    tables = load_movielens_100k(raw_data_dir)
    splits = prepare_implicit_splits(
        tables.ratings,
        positive_threshold=float(config.data["positive_threshold"]),
        minimum_user_positives=int(config.data["minimum_user_positives"]),
    )

    validation_candidates = build_evaluation_candidates(
        splits.validation,
        splits,
        negatives_per_user=int(config.data["evaluation_negatives"]),
        seed=seed + 10_000,
    )
    test_candidates = build_evaluation_candidates(
        splits.test,
        splits,
        negatives_per_user=int(config.data["evaluation_negatives"]),
        seed=seed + 20_000,
    )

    _write_audit_inputs(
        root, output_dir, Path(config_path), raw_data_dir, splits.summary()
    )
    settings = TrainingSettings(
        epochs=int(config.training["epochs"]),
        batch_size=int(config.training["batch_size"]),
        learning_rate=float(config.training["learning_rate"]),
        negatives_per_positive=int(config.data["training_negatives"]),
        early_stopping_patience=int(
            config.training["early_stopping_patience"]
        ),
        seed=seed,
        num_workers=int(config.training["num_workers"]),
    )

    history_frames: list[pd.DataFrame] = []
    metric_rows: list[dict[str, int | float | str]] = []
    recommendation_frames: list[pd.DataFrame] = []
    hidden_layers = [int(value) for value in config.models["mlp_layers"]]
    cutoffs = (5, 10)

    for model_name in config.models["names"]:
        set_global_seed(seed)
        model = build_model(
            model_name,
            splits.num_users,
            splits.num_items,
            int(config.models["embedding_dim"]),
            hidden_layers,
        )
        model_dir = output_dir / "models" / model_name
        result = train_one_model(
            model=model,
            model_name=model_name,
            splits=splits,
            validation_candidates=validation_candidates,
            settings=settings,
            device=device,
            output_dir=model_dir,
            primary_metric=config.evaluation["primary_metric"],
            cutoffs=cutoffs,
        )
        history_frames.append(result.history)
        test_metrics = evaluate_candidate_sets(
            model, test_candidates, device, cutoffs=cutoffs
        )
        metric_rows.append(
            {
                "model": model_name,
                "best_epoch": result.best_epoch,
                "trainable_parameters": count_trainable_parameters(model),
                **test_metrics,
            }
        )
        for user_idx in range(min(3, splits.num_users)):
            recommendations = recommend_unrated_items(
                model,
                user_idx,
                splits,
                tables.movies,
                device,
                top_k=10,
            )
            recommendations.insert(0, "model", model_name)
            recommendation_frames.append(recommendations)

    pd.concat(history_frames, ignore_index=True).to_csv(
        output_dir / "training_history.csv", index=False
    )
    pd.DataFrame(metric_rows).to_csv(output_dir / "test_metrics.csv", index=False)
    pd.concat(recommendation_frames, ignore_index=True).to_csv(
        output_dir / "recommendation_examples.csv", index=False
    )
    generate_figures_from_csv(output_dir)
    return output_dir


def run_recommendation_demo(
    config: ExperimentConfig,
    project_root: str | Path,
    experiment_dir: str | Path,
    model_name: str,
    user_id: int,
    top_k: int,
) -> pd.DataFrame:
    """Load a trained model and recommend unrated movies for one user."""

    if model_name not in config.models["names"]:
        raise ValueError(f"Unsupported model: {model_name}")
    if top_k <= 0:
        raise ValueError("top_k must be positive")

    root = Path(project_root)
    checkpoint_path = (
        root
        / experiment_dir
        / "models"
        / model_name
        / f"{model_name}_best.pt"
    )
    if not checkpoint_path.is_file():
        raise FileNotFoundError(f"Checkpoint not found: {checkpoint_path}")

    tables = load_movielens_100k(root / config.paths["raw_data_dir"])
    splits = prepare_implicit_splits(
        tables.ratings,
        positive_threshold=float(config.data["positive_threshold"]),
        minimum_user_positives=int(config.data["minimum_user_positives"]),
    )
    if user_id not in splits.user_to_index:
        raise ValueError(f"User ID {user_id} is not available in the experiment")

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = build_model(
        model_name,
        splits.num_users,
        splits.num_items,
        int(config.models["embedding_dim"]),
        [int(value) for value in config.models["mlp_layers"]],
    ).to(device)
    load_checkpoint(checkpoint_path, model, device)
    return recommend_unrated_items(
        model,
        splits.user_to_index[user_id],
        splits,
        tables.movies,
        device,
        top_k=top_k,
    )


def _prepare_formal_output_directory(
    output_dir: Path, allow_overwrite: bool
) -> None:
    if output_dir.exists() and any(output_dir.iterdir()) and not allow_overwrite:
        raise FileExistsError(
            f"Formal output directory is not empty: {output_dir}"
        )
    output_dir.mkdir(parents=True, exist_ok=True)


def _write_audit_inputs(
    project_root: Path,
    output_dir: Path,
    config_path: Path,
    raw_data_dir: Path,
    data_summary: dict,
) -> None:
    shutil.copy2(config_path, output_dir / "experiment_config.toml")
    hashes = {
        "u.data": sha256_file(raw_data_dir / "u.data"),
        "u.item": sha256_file(raw_data_dir / "u.item"),
        "u.user": sha256_file(raw_data_dir / "u.user"),
    }
    source_files = sorted((project_root / "src").rglob("*.py"))
    hashes["source_files"] = {
        str(path.relative_to(project_root)): sha256_file(path)
        for path in source_files
    }
    write_json(output_dir / "environment.json", collect_environment_metadata())
    write_json(output_dir / "file_hashes.json", hashes)
    write_json(output_dir / "data_summary.json", data_summary)
