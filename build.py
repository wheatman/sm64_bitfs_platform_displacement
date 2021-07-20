import subprocess
import sys

def find_tool(name: str):
    cmd = "where" if sys.platform == "windows" else "which"
    result = subprocess.run([cmd, name])
    if result.returncode != 0:
        return None
    else:
        return result.stdout

def run():
    if find_tool('clang++') is None:
        raise RuntimeError("Clang is required to compile this thing")   
    
    if sys.platform == "win32":
        result = subprocess.run(["ninja", "windows.ninja"])
