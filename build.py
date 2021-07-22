from pathlib import Path
import subprocess
import os

proj_dir = Path(__file__).parent

os.chdir(proj_dir)

if not proj_dir.joinpath("build.ninja").exists():
    subprocess.run(["python3", "configure.py"])

subprocess.run(["ninja"])