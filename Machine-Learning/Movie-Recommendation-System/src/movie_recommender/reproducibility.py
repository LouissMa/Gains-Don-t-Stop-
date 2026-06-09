"""Random seeds, environment metadata, and file hashing."""

from __future__ import annotations

import hashlib
import json
import os
import platform
import random
import sys
from pathlib import Path
from typing import Any

import numpy as np
import torch


def set_global_seed(seed: int, deterministic: bool = True) -> None:
    """Seed Python, NumPy, and PyTorch random number generators."""

    if seed < 0:
        raise ValueError("seed must be non-negative")
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)
    if deterministic:
        torch.use_deterministic_algorithms(True, warn_only=True)
        torch.backends.cudnn.benchmark = False


def sha256_file(path: str | Path, chunk_size: int = 1024 * 1024) -> str:
    """Calculate a file hash without loading the complete file into memory."""

    file_path = Path(path)
    digest = hashlib.sha256()
    with file_path.open("rb") as file:
        while chunk := file.read(chunk_size):
            digest.update(chunk)
    return digest.hexdigest()


def collect_environment_metadata() -> dict[str, Any]:
    """Collect runtime details needed to audit a formal experiment."""

    cuda_available = torch.cuda.is_available()
    return {
        "python": sys.version,
        "platform": platform.platform(),
        "processor": platform.processor(),
        "pytorch": torch.__version__,
        "cuda_available": cuda_available,
        "cuda_version": torch.version.cuda,
        "cudnn_version": torch.backends.cudnn.version(),
        "gpu": torch.cuda.get_device_name(0) if cuda_available else None,
        "numpy": np.__version__,
        "pid": os.getpid(),
    }


def write_json(path: str | Path, payload: Any) -> None:
    """Write UTF-8 JSON with stable indentation."""

    output_path = Path(path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w", encoding="utf-8", newline="\n") as file:
        json.dump(payload, file, ensure_ascii=False, indent=2, sort_keys=True)
