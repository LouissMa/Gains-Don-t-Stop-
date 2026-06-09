from __future__ import annotations

import unittest
import tempfile
from pathlib import Path

import numpy as np
import pandas as pd

from src.movie_recommender.data import (
    NegativeSampler,
    PointwiseTrainingDataset,
    build_evaluation_candidates,
    load_movielens_100k,
    prepare_implicit_splits,
)
from tests.helpers import make_small_ratings


def make_ratings() -> pd.DataFrame:
    return make_small_ratings()


class DataPreparationTests(unittest.TestCase):
    def setUp(self) -> None:
        self.splits = prepare_implicit_splits(make_ratings())

    def test_filters_users_and_uses_time_order(self) -> None:
        self.assertEqual(self.splits.num_users, 2)
        self.assertEqual(len(self.splits.train), 4)
        self.assertEqual(len(self.splits.validation), 2)
        self.assertEqual(len(self.splits.test), 2)
        user_10 = self.splits.user_to_index[10]
        validation_item = self.splits.validation.set_index("user_idx").loc[
            user_10, "item_id"
        ]
        test_item = self.splits.test.set_index("user_idx").loc[
            user_10, "item_id"
        ]
        self.assertEqual(validation_item, 104)
        self.assertEqual(test_item, 105)

    def test_known_items_include_low_ratings(self) -> None:
        user_10 = self.splits.user_to_index[10]
        low_rated_item = self.splits.item_to_index[102]
        self.assertIn(low_rated_item, self.splits.known_items_by_user[user_10])

    def test_negative_sampler_is_reproducible_and_unrated(self) -> None:
        user_10 = self.splits.user_to_index[10]
        first = NegativeSampler(
            self.splits.num_items, self.splits.known_items_by_user, seed=7
        ).sample(user_10, 2)
        second = NegativeSampler(
            self.splits.num_items, self.splits.known_items_by_user, seed=7
        ).sample(user_10, 2)
        np.testing.assert_array_equal(first, second)
        self.assertTrue(
            set(first).isdisjoint(self.splits.known_items_by_user[user_10])
        )
        self.assertEqual(len(set(first)), 2)

    def test_pointwise_dataset_has_expected_labels(self) -> None:
        dataset = PointwiseTrainingDataset(
            self.splits.train,
            self.splits.num_items,
            self.splits.known_items_by_user,
            negatives_per_positive=2,
            seed=11,
        )
        self.assertEqual(len(dataset), len(self.splits.train) * 3)
        self.assertEqual(int(dataset.labels.sum().item()), len(self.splits.train))
        for user, item, label in zip(
            dataset.users.tolist(),
            dataset.items.tolist(),
            dataset.labels.tolist(),
        ):
            if label == 0.0:
                self.assertNotIn(
                    item, self.splits.known_items_by_user[user]
                )

    def test_fixed_evaluation_candidates(self) -> None:
        first = build_evaluation_candidates(
            self.splits.test, self.splits, negatives_per_user=2, seed=21
        )
        second = build_evaluation_candidates(
            self.splits.test, self.splits, negatives_per_user=2, seed=21
        )
        self.assertEqual(len(first), self.splits.num_users)
        for left, right in zip(first, second):
            np.testing.assert_array_equal(left.item_indices, right.item_indices)
            np.testing.assert_array_equal(left.labels, right.labels)
            self.assertEqual(int(left.labels.sum()), 1)
            positive_position = int(np.flatnonzero(left.labels == 1)[0])
            self.assertEqual(
                left.item_indices[positive_position], left.target_item_idx
            )
            self.assertTrue(
                set(left.item_indices[left.labels == 0]).isdisjoint(
                    self.splits.known_items_by_user[left.user_idx]
                )
            )


class MovieLens100KLoaderTests(unittest.TestCase):
    def test_loads_official_file_layout(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            (directory / "u.data").write_text(
                "1\t1\t5\t100\n1\t2\t3\t101\n",
                encoding="latin-1",
            )
            genre_flags = ["0"] * 19
            genre_flags[1] = "1"
            genre_flags[5] = "1"
            item_rows = [
                "|".join(
                    ["1", "Movie One (1995)", "01-Jan-1995", "", "http://one"]
                    + genre_flags
                ),
                "|".join(
                    ["2", "Movie Two (1996)", "01-Jan-1996", "", "http://two"]
                    + ["0"] * 19
                ),
            ]
            (directory / "u.item").write_text(
                "\n".join(item_rows) + "\n",
                encoding="latin-1",
            )
            (directory / "u.user").write_text(
                "1|25|M|programmer|00000\n",
                encoding="latin-1",
            )

            tables = load_movielens_100k(directory)
            self.assertEqual(len(tables.ratings), 2)
            self.assertEqual(tables.movies.loc[0, "genres"], "Action|Comedy")
            self.assertEqual(tables.users.loc[0, "gender"], "M")
            self.assertEqual(tables.users.loc[0, "age"], 25)


if __name__ == "__main__":
    unittest.main()
