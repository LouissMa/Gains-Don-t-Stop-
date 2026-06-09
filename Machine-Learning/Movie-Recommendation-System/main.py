"""Command entry point with explicit formal-training safeguards."""

from __future__ import annotations

import argparse
import os
import sys
from pathlib import Path


os.environ.setdefault("CUBLAS_WORKSPACE_CONFIG", ":4096:8")

PROJECT_ROOT = Path(__file__).resolve().parent
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from movie_recommender.config import load_config
from movie_recommender.experiment import (
    run_formal_experiment,
    run_recommendation_demo,
)
from movie_recommender.visualization import generate_figures_from_csv


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Movie recommendation experiment.")
    parser.add_argument(
        "--config",
        default="configs/experiment.toml",
        help="Path to the experiment TOML configuration.",
    )
    subparsers = parser.add_subparsers(dest="command")
    subparsers.add_parser("inspect", help="Display configuration without training.")
    train_parser = subparsers.add_parser(
        "train-formal", help="Run the approved formal experiment."
    )
    train_parser.add_argument(
        "--confirm-formal-training",
        action="store_true",
        help="Required acknowledgement before formal training can start.",
    )
    figures_parser = subparsers.add_parser(
        "visualize", help="Regenerate figures from existing raw CSV files."
    )
    figures_parser.add_argument("--output-dir", required=True)
    recommend_parser = subparsers.add_parser(
        "recommend", help="Recommend unrated movies with a trained model."
    )
    recommend_parser.add_argument(
        "--experiment-dir", default="outputs/formal"
    )
    recommend_parser.add_argument(
        "--model", choices=["gmf", "mlp", "neumf"], default="neumf"
    )
    recommend_parser.add_argument("--user-id", type=int, required=True)
    recommend_parser.add_argument("--top-k", type=int, default=10)
    recommend_parser.add_argument("--save-csv")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    config_path = PROJECT_ROOT / args.config
    config = load_config(config_path)

    if args.command in (None, "inspect"):
        print(f"Project: {config.project['name']}")
        print(f"Dataset: {config.project['dataset']}")
        print(f"Task: {config.project['task']}")
        print(f"Models: {', '.join(config.models['names'])}")
        print(f"Split: {config.data['split_strategy']}")
        print(f"Primary metric: {config.evaluation['primary_metric']}")
        print(f"Formal training approved: {config.formal_training_approved}")
        print("No data processing or training was executed.")
        return
    if args.command == "train-formal":
        try:
            output_dir = run_formal_experiment(
                config,
                PROJECT_ROOT,
                config_path,
                confirmation=args.confirm_formal_training,
            )
        except (PermissionError, FileExistsError) as error:
            raise SystemExit(f"Training refused: {error}") from None
        print(f"Formal experiment completed: {output_dir}")
        return
    if args.command == "visualize":
        paths = generate_figures_from_csv(PROJECT_ROOT / args.output_dir)
        for path in paths:
            print(path)
        return
    if args.command == "recommend":
        try:
            recommendations = run_recommendation_demo(
                config,
                PROJECT_ROOT,
                args.experiment_dir,
                args.model,
                args.user_id,
                args.top_k,
            )
        except (FileNotFoundError, ValueError) as error:
            raise SystemExit(f"Recommendation refused: {error}") from None
        print(recommendations.to_string(index=False))
        if args.save_csv:
            destination = PROJECT_ROOT / args.save_csv
            destination.parent.mkdir(parents=True, exist_ok=True)
            recommendations.to_csv(destination, index=False)
            print(f"Saved recommendations: {destination}")


if __name__ == "__main__":
    main()
