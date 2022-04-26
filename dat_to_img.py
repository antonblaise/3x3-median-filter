import numpy as np
from PIL import Image

input_dat = './data/out.gold.dat'
im = Image.open('./data/input.png')
width, height = im.size
output_png = "output.png"

with open(input_dat, 'r') as file:
    data = file.readlines()

for i in range(len(data)):
    # data[i] = int(data[i].replace(';\n',''))
    data[i] = int(data[i])

data = np.array(data)

newimage = Image.new('L', (width,height))
print(f">> Opening and processing dat file {input_dat} width {width}, height {height}")
print(f">> Total number of pixels: {width*height}")
print(f">> PNG file generated as {output_png}")
newimage.putdata(data)
newimage.save(f"./{output_png}") 
newimage.save(f"./data/{output_png}") 
