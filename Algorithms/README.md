# Algorithm Training Index

> A structured index of my competitive-programming practice, reusable templates, and topic-based training.

[![C++](https://img.shields.io/badge/Language-C++-00599C?logo=cplusplus&logoColor=white)](./)
[![Codeforces](https://img.shields.io/badge/Codeforces-1438-03A89E?logo=codeforces&logoColor=white)](https://codeforces.com/profile/Mabingnan__V)
[![AtCoder](https://img.shields.io/badge/AtCoder-1695-2563EB)](https://atcoder.jp/users/MaBingNan_Louiss)

## Overview

This directory records my long-term algorithm training across Codeforces, AtCoder, ICPC/CCPC, Nowcoder, and Luogu. It currently contains **800+ C++ files** and **170+ date-based training folders**, covering contest submissions, upsolving, topic practice, and reusable implementations.

| Platform / Category | Recognizable C++ files | Typical content |
| --- | ---: | --- |
| AtCoder ABC | 240+ | ABC practice and upsolving, including higher-letter problems |
| Codeforces / Educational CF | 130+ | Div. 2, Div. 3, and Educational Round practice |
| ICPC / CCPC | 50+ | Regional-contest problem sets and team-contest training |
| Nowcoder | 70+ | Contest practice and topic reinforcement |
| Luogu | 50+ | Templates and classical algorithm problems |

> Counts are derived from recognizable filenames in the current repository. A file may be excluded when its name is only `A.cpp`, `B.cpp`, and so on.

## Topic Map

### Data Structures

| Topic | Representative implementation |
| --- | --- |
| Heap | [Luogu P3378 / Heap](./2025/11-01/Heap/3378.cpp) |
| Fenwick Tree | [CCPC Jinan — Fenwick Tree](./2026/01-09/CCPC_Jinan_Fenwick.cpp) |
| Segment Tree | [Range update and query](./2026/04-19/SegmentTree_3372.cpp) |
| Segment Tree Template | [Template 1](./2026/04-19/SegmentTree_Template1.cpp) · [Template 2](./2026/04-20/SegmentTree_Template2.cpp) |
| Interval operations | [Interval merge](./2025/12-10/ICPC_Nanjing_Interval_Merge.cpp) |

### Graphs & Trees

| Topic | Representative implementation |
| --- | --- |
| Minimum Spanning Tree | [Kruskal template](./Basic-Algorithms/Kruskal.cpp) · [Luogu practice](./2026/01-03/Luogu_Kruskal.cpp) |
| Topological Sort | [Topological sort](./2026/02-10/Topological_Sort.cpp) |
| Tree algorithms | [Tree centroid](./2026/02-10/Tree_Center_of_Gravity.cpp) |

### Dynamic Programming

| Topic | Representative implementation |
| --- | --- |
| 0/1 Knapsack | [0/1 Knapsack](./Basic-Algorithms/01_Knapsack.cpp) |
| Complete Knapsack | [Complete Knapsack](./Basic-Algorithms/Complete_Knapsack.cpp) |
| Multiple Knapsack | [Multiple Knapsack](./Basic-Algorithms/Multiple_Knapsack.cpp) |
| Group Knapsack | [Group Knapsack](./Basic-Algorithms/Group_Knapsack.cpp) |
| Interval DP | [Stone Merge](./Basic-Algorithms/Stone_Merge.cpp) |

### Mathematics

| Topic | Representative implementation |
| --- | --- |
| Prime algorithms | [Prime Sieve](./Basic-Algorithms/Prime_Sieve.cpp) · [Prime Factorization](./Basic-Algorithms/Prime_Factorization.cpp) |
| Fast exponentiation | [Binary Exponentiation](./Basic-Algorithms/快速幂.cpp) |
| Modular inverse | [Inverse with fast exponentiation](./Basic-Algorithms/快速幂求逆元.cpp) |
| Combinatorics | [Method 1](./Basic-Algorithms/组合数1.cpp) · [Method 2](./Basic-Algorithms/组合数2.cpp) · [Method 3](./Basic-Algorithms/组合数3.cpp) · [Method 4](./Basic-Algorithms/组合数4.cpp) |

### General Techniques

| Topic | Representative implementation |
| --- | --- |
| Discretization & Prefix Sum | [Discretized interval sum](./Basic-Algorithms/Discretization_Interval_Sum.cpp) |
| Contest application | [AtCoder ABC357 — discretization and interval sum](./2025/12-09/Abc357_Discretization_Interval_Sum.cpp) |
| Interval Merge | [ICPC Nanjing](./2025/12-10/ICPC_Nanjing_Interval_Merge.cpp) · [2025 ICPC Nanjing](./2026/03-27/ICPC_2025_Nanjing_Interval_Merge.cpp) |

## Contest Archive

| Period | Training folders | C++ files | Entry |
| --- | ---: | ---: | --- |
| 2025 | 59 | 300+ | [Browse 2025](./2025/) |
| 2026 | 113 | 460+ | [Browse 2026](./2026/) |

The archive includes AtCoder Beginner Contests, Codeforces rounds, ICPC/CCPC regional sets, Nowcoder contests, and Luogu topic practice. Files are organized by practice date to preserve the training timeline.

## Solution Documentation Standard

New representative solutions should gradually include the following metadata so that the reasoning is as easy to verify as the code:

```cpp
// Problem: contest + problem name
// URL: original problem link
// Topics: graph / DP / data structure / mathematics / ...
// Time: O(...)
// Space: O(...)
// Key idea: one-sentence summary
```

For important problems, I also plan to add short editorials covering the approach, correctness argument, complexity analysis, and mistakes found during upsolving.

## Profiles

- [Codeforces — Mabingnan__V, Rating 1438](https://codeforces.com/profile/Mabingnan__V)
- [AtCoder — MaBingNan_Louiss, Rating 1695](https://atcoder.jp/users/MaBingNan_Louiss)

[Back to repository overview](../README.md)