"""MovieLens 100K loading, preprocessing, splitting, and negative sampling."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Mapping

import numpy as np
import pandas as pd
import torch
from torch.utils.data import Dataset


RATING_COLUMNS = ("user_id", "item_id", "rating", "timestamp")
MOVIE_COLUMNS = ("item_id", "title", "genres")
USER_COLUMNS = ("user_id", "gender", "age", "occupation", "zip_code")
MOVIELENS_100K_GENRES = (
    "unknown",
    "Action",
    "Adventure",
    "Animation",
    "Children's",
    "Comedy",
    "Crime",
    "Documentary",
    "Drama",
    "Fantasy",
    "Film-Noir",
    "Horror",
    "Musical",
    "Mystery",
    "Romance",
    "Sci-Fi",
    "Thriller",
    "War",
    "Western",
)


@dataclass(frozen=True)
class MovieLensTables:
    """Raw MovieLens tables loaded without modifying the source files."""

    ratings: pd.DataFrame
    movies: pd.DataFrame
    users: pd.DataFrame


@dataclass(frozen=True)
class DataSplits:
    """Prepared positive interactions and metadata used by later stages."""

    train: pd.DataFrame
    validation: pd.DataFrame
    test: pd.DataFrame
    user_to_index: dict[int, int]
    index_to_user: dict[int, int]
    item_to_index: dict[int, int]
    index_to_item: dict[int, int]
    known_items_by_user: dict[int, frozenset[int]]
    num_users: int
    num_items: int
    positive_threshold: float

    def summary(self) -> dict[str, int | float]:
        return {
            "num_users": self.num_users,
            "num_items": self.num_items,
            "train_positives": len(self.train),
            "validation_positives": len(self.validation),
            "test_positives": len(self.test),
            "total_positives": len(self.train) + len(self.validation) + len(self.test),
            "positive_threshold": self.positive_threshold,
        }


@dataclass(frozen=True)
class CandidateSet:
    """One positive target and fixed unrated negatives for one user."""

    user_idx: int
    target_item_idx: int
    item_indices: np.ndarray
    labels: np.ndarray


def load_movielens_100k(data_dir: str | Path) -> MovieLensTables:
    """Load the official MovieLens 100K ratings, movies, and users."""

    directory = Path(data_dir)
    required_files = ("u.data", "u.item", "u.user")
    for filename in required_files:
        if not (directory / filename).is_file():
            raise FileNotFoundError(
                f"Required MovieLens 100K file not found: {directory / filename}"
            )

    ratings = pd.read_csv(
        directory / "u.data",
        sep="\t",
        names=list(RATING_COLUMNS),
        encoding="latin-1",
    )
    raw_movies = pd.read_csv(
        directory / "u.item",
        sep="|",
        engine="python",
        header=None,
        encoding="latin-1",
    )
    if raw_movies.shape[1] != 24:
        raise ValueError(
            f"MovieLens 100K u.item must have 24 columns, got {raw_movies.shape[1]}"
        )
    genre_flags = raw_movies.iloc[:, 5:24].to_numpy(dtype=np.int8)
    genre_strings = [
        "|".join(
            genre
            for genre, enabled in zip(MOVIELENS_100K_GENRES, flags)
            if enabled
        )
        for flags in genre_flags
    ]
    movies = pd.DataFrame(
        {
            "item_id": raw_movies.iloc[:, 0].astype(int),
            "title": raw_movies.iloc[:, 1].astype(str),
            "genres": genre_strings,
        }
    )
    users = pd.read_csv(
        directory / "u.user",
        sep="|",
        names=["user_id", "age", "gender", "occupation", "zip_code"],
        encoding="latin-1",
    )[list(USER_COLUMNS)]

    _validate_raw_tables(ratings, movies, users)
    return MovieLensTables(ratings=ratings, movies=movies, users=users)


def _validate_raw_tables(
    ratings: pd.DataFrame, movies: pd.DataFrame, users: pd.DataFrame
) -> None:
    if ratings.empty or movies.empty or users.empty:
        raise ValueError("MovieLens tables must not be empty")
    if ratings[list(RATING_COLUMNS)].isnull().any().any():
        raise ValueError("Ratings contain missing values")
    if not ratings["rating"].between(1, 5).all():
        raise ValueError("MovieLens ratings must be between 1 and 5")
    if ratings.duplicated(["user_id", "item_id"]).any():
        raise ValueError("Duplicate user-item ratings are not supported")
    if movies["item_id"].duplicated().any():
        raise ValueError("Movie IDs must be unique")
    if users["user_id"].duplicated().any():
        raise ValueError("User IDs must be unique")
    if not set(ratings["user_id"]).issubset(set(users["user_id"])):
        raise ValueError("Ratings reference unknown users")
    if not set(ratings["item_id"]).issubset(set(movies["item_id"])):
        raise ValueError("Ratings reference unknown movies")


def prepare_implicit_splits(
    ratings: pd.DataFrame,
    positive_threshold: float = 4.0,
    minimum_user_positives: int = 3,
) -> DataSplits:
    """Create a deterministic time-based leave-one-out split.

    Only items present in the ratings table are included in the model item
    vocabulary. Negative sampling excludes every item the user has rated,
    including ratings below the positive threshold.
    """

    if not 1 <= positive_threshold <= 5:
        raise ValueError("positive_threshold must be between 1 and 5")
    if minimum_user_positives < 3:
        raise ValueError("minimum_user_positives must be at least 3")

    required = set(RATING_COLUMNS)
    if not required.issubset(ratings.columns):
        missing = sorted(required.difference(ratings.columns))
        raise ValueError(f"Ratings are missing columns: {missing}")
    if ratings.empty:
        raise ValueError("Ratings must not be empty")

    positives = ratings.loc[
        ratings["rating"] >= positive_threshold,
        ["user_id", "item_id", "rating", "timestamp"],
    ].copy()
    positive_counts = positives.groupby("user_id").size()
    eligible_users = positive_counts[
        positive_counts >= minimum_user_positives
    ].index
    positives = positives[positives["user_id"].isin(eligible_users)].copy()
    if positives.empty:
        raise ValueError("No users satisfy the positive-interaction requirement")

    user_ids = sorted(int(value) for value in positives["user_id"].unique())
    item_ids = sorted(int(value) for value in ratings["item_id"].unique())
    user_to_index = {raw_id: index for index, raw_id in enumerate(user_ids)}
    item_to_index = {raw_id: index for index, raw_id in enumerate(item_ids)}
    index_to_user = {index: raw_id for raw_id, index in user_to_index.items()}
    index_to_item = {index: raw_id for raw_id, index in item_to_index.items()}

    positives["user_idx"] = positives["user_id"].map(user_to_index)
    positives["item_idx"] = positives["item_id"].map(item_to_index)
    positives = positives.sort_values(
        ["user_idx", "timestamp", "item_id"], kind="mergesort"
    ).reset_index(drop=True)
    positives["position"] = positives.groupby("user_idx").cumcount()
    positives["group_size"] = positives.groupby("user_idx")["user_idx"].transform(
        "size"
    )

    test = positives[positives["position"] == positives["group_size"] - 1]
    validation = positives[positives["position"] == positives["group_size"] - 2]
    train = positives[positives["position"] < positives["group_size"] - 2]
    output_columns = [
        "user_idx",
        "item_idx",
        "user_id",
        "item_id",
        "rating",
        "timestamp",
    ]

    eligible_ratings = ratings[ratings["user_id"].isin(eligible_users)].copy()
    eligible_ratings["user_idx"] = eligible_ratings["user_id"].map(user_to_index)
    eligible_ratings["item_idx"] = eligible_ratings["item_id"].map(item_to_index)
    known_items_by_user = {
        int(user_idx): frozenset(int(item) for item in items)
        for user_idx, items in eligible_ratings.groupby("user_idx")["item_idx"]
    }

    splits = DataSplits(
        train=train[output_columns].reset_index(drop=True),
        validation=validation[output_columns].reset_index(drop=True),
        test=test[output_columns].reset_index(drop=True),
        user_to_index=user_to_index,
        index_to_user=index_to_user,
        item_to_index=item_to_index,
        index_to_item=index_to_item,
        known_items_by_user=known_items_by_user,
        num_users=len(user_to_index),
        num_items=len(item_to_index),
        positive_threshold=float(positive_threshold),
    )
    validate_splits(splits)
    return splits


def validate_splits(splits: DataSplits) -> None:
    """Raise an error if the prepared data violates the approved protocol."""

    if len(splits.validation) != splits.num_users:
        raise ValueError("Validation must contain exactly one item per user")
    if len(splits.test) != splits.num_users:
        raise ValueError("Test must contain exactly one item per user")
    if splits.validation["user_idx"].nunique() != splits.num_users:
        raise ValueError("Validation users are not unique")
    if splits.test["user_idx"].nunique() != splits.num_users:
        raise ValueError("Test users are not unique")
    if set(splits.user_to_index.values()) != set(range(splits.num_users)):
        raise ValueError("User indices must be contiguous")
    if set(splits.item_to_index.values()) != set(range(splits.num_items)):
        raise ValueError("Item indices must be contiguous")

    train_pairs = set(zip(splits.train["user_idx"], splits.train["item_idx"]))
    validation_pairs = set(
        zip(splits.validation["user_idx"], splits.validation["item_idx"])
    )
    test_pairs = set(zip(splits.test["user_idx"], splits.test["item_idx"]))
    if train_pairs & validation_pairs:
        raise ValueError("Train and validation positive interactions overlap")
    if train_pairs & test_pairs:
        raise ValueError("Train and test positive interactions overlap")
    if validation_pairs & test_pairs:
        raise ValueError("Validation and test positive interactions overlap")

    train_max_time = splits.train.groupby("user_idx")["timestamp"].max()
    validation_time = splits.validation.set_index("user_idx")["timestamp"]
    test_time = splits.test.set_index("user_idx")["timestamp"]
    if (train_max_time > validation_time.loc[train_max_time.index]).any():
        raise ValueError("Training contains interactions after validation")
    if (validation_time > test_time).any():
        raise ValueError("Validation contains interactions after test")

    for frame in (splits.train, splits.validation, splits.test):
        for user_idx, item_idx in frame[["user_idx", "item_idx"]].itertuples(
            index=False
        ):
            if int(item_idx) not in splits.known_items_by_user[int(user_idx)]:
                raise ValueError("A positive item is missing from known interactions")


class NegativeSampler:
    """Sample unrated items reproducibly for training or evaluation."""

    def __init__(
        self,
        num_items: int,
        known_items_by_user: Mapping[int, frozenset[int]],
        seed: int,
    ) -> None:
        if num_items <= 0:
            raise ValueError("num_items must be positive")
        self.num_items = num_items
        self.known_items_by_user = known_items_by_user
        self.rng = np.random.default_rng(seed)

    def sample(self, user_idx: int, count: int, replace: bool = False) -> np.ndarray:
        if count <= 0:
            raise ValueError("count must be positive")
        known = self.known_items_by_user[user_idx]
        available_count = self.num_items - len(known)
        if available_count <= 0:
            raise ValueError(f"User {user_idx} has no unrated candidate items")
        if not replace and count > available_count:
            raise ValueError(
                f"Requested {count} unique negatives, but only "
                f"{available_count} are available"
            )

        if available_count <= count * 4:
            pool = np.fromiter(
                (item for item in range(self.num_items) if item not in known),
                dtype=np.int64,
            )
            return self.rng.choice(pool, size=count, replace=replace)

        negatives: list[int] = []
        selected: set[int] = set()
        while len(negatives) < count:
            candidate = int(self.rng.integers(self.num_items))
            if candidate in known:
                continue
            if not replace and candidate in selected:
                continue
            negatives.append(candidate)
            selected.add(candidate)
        return np.asarray(negatives, dtype=np.int64)


class PointwiseTrainingDataset(Dataset):
    """Positive interactions with pointwise sampled negatives."""

    def __init__(
        self,
        positive_interactions: pd.DataFrame,
        num_items: int,
        known_items_by_user: Mapping[int, frozenset[int]],
        negatives_per_positive: int,
        seed: int,
    ) -> None:
        if negatives_per_positive <= 0:
            raise ValueError("negatives_per_positive must be positive")
        sampler = NegativeSampler(num_items, known_items_by_user, seed)
        users: list[int] = []
        items: list[int] = []
        labels: list[float] = []

        for user_idx, item_idx in positive_interactions[
            ["user_idx", "item_idx"]
        ].itertuples(index=False):
            user_idx = int(user_idx)
            users.append(user_idx)
            items.append(int(item_idx))
            labels.append(1.0)
            negatives = sampler.sample(
                user_idx, negatives_per_positive, replace=False
            )
            users.extend([user_idx] * negatives_per_positive)
            items.extend(int(item) for item in negatives)
            labels.extend([0.0] * negatives_per_positive)

        self.users = torch.tensor(users, dtype=torch.long)
        self.items = torch.tensor(items, dtype=torch.long)
        self.labels = torch.tensor(labels, dtype=torch.float32)

    def __len__(self) -> int:
        return len(self.labels)

    def __getitem__(self, index: int) -> tuple[torch.Tensor, ...]:
        return self.users[index], self.items[index], self.labels[index]


def build_evaluation_candidates(
    targets: pd.DataFrame,
    splits: DataSplits,
    negatives_per_user: int,
    seed: int,
) -> list[CandidateSet]:
    """Build a fixed candidate list shared by every evaluated model."""

    required = {"user_idx", "item_idx"}
    if not required.issubset(targets.columns):
        raise ValueError(f"Targets must contain columns: {sorted(required)}")
    sampler = NegativeSampler(
        splits.num_items, splits.known_items_by_user, seed
    )
    order_rng = np.random.default_rng(seed + 1)
    candidates: list[CandidateSet] = []
    for user_idx, target_item_idx in targets[
        ["user_idx", "item_idx"]
    ].itertuples(index=False):
        user_idx = int(user_idx)
        target_item_idx = int(target_item_idx)
        negatives = sampler.sample(user_idx, negatives_per_user, replace=False)
        ordered_items = np.concatenate(
            [np.asarray([target_item_idx], dtype=np.int64), negatives]
        )
        ordered_labels = np.zeros(len(ordered_items), dtype=np.float32)
        ordered_labels[0] = 1.0
        permutation = order_rng.permutation(len(ordered_items))
        item_indices = ordered_items[permutation]
        labels = ordered_labels[permutation]
        candidates.append(
            CandidateSet(
                user_idx=user_idx,
                target_item_idx=target_item_idx,
                item_indices=item_indices,
                labels=labels,
            )
        )
    return candidates


def iter_known_raw_items(
    splits: DataSplits, user_idx: int
) -> Iterable[int]:
    """Yield original MovieLens item IDs rated by an internal user index."""

    for item_idx in sorted(splits.known_items_by_user[user_idx]):
        yield splits.index_to_item[item_idx]
