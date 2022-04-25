import glob, os

#clear pre-existing files to avoid overlap
for f in glob.glob("./data/*.dat"):
    os.remove(f)


