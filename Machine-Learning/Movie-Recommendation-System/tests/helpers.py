from __future__ import annotations

import pandas as pd

from src.movie_recommender.data import prepare_implicit_splits


def make_small_ratings() -> pd.DataFrame:
    rows = [
        (10, 101, 5, 10),
        (10, 102, 2, 11),
        (10, 103, 4, 12),
        (10, 104, 5, 13),
        (10, 105, 4, 14),
        (20, 101, 4, 20),
        (20, 102, 5, 21),
        (20, 103, 1, 22),
        (20, 106, 4, 23),
        (20, 107, 5, 24),
        (30, 101, 5, 30),
        (30, 108, 4, 31),
        (40, 109, 2, 40),
        (40, 110, 1, 41),
    ]
    return pd.DataFrame(
        rows, columns=["user_id", "item_id", "rating", "timestamp"]
    )


def make_small_splits():
    return prepare_implicit_splits(make_small_ratings())


def make_small_movies() -> pd.DataFrame:
    return pd.DataFrame(
        [
            (item_id, f"Movie {item_id}", "Drama")
            for item_id in range(101, 111)
        ],
        columns=["item_id", "title", "genres"],
    )
