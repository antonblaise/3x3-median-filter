import os

requirements = [
    "numpy",
    "Pillow"
]

for package in requirements:
    os.system(f"pip install {package}")