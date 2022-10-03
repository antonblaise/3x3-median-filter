import os

requirements = [
    "numpy",
    "Pillow",
    "matplotlib"
]

for package in requirements:
    os.system(f"pip install {package}")