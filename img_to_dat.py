import numpy as np
from PIL import Image, ImageOps

# image can be png or jpg format
loc = "./data/"
fname = "input.png"
im = Image.open(loc + fname)
width, height = im.size
outdat = "input.dat"

with open('./data/dimension.dat', 'w') as f:
    for item in [width, height]:
        f.write("%s\n" % item)

def write_dat (f, pix_val):
    for i in range (0, len(pix_val)):
        f.write(str(pix_val[i])+"\n")
    f.close()

# get pixel values
print(">> Opening and processing image "+loc + fname+ " width "+str(width)+" height "+str(height))
im = Image.open(loc+fname, 'r').convert('RGB')
pix_val = list(ImageOps.grayscale(im).getdata())
# pix_val = list(im.getdata())
print(">> Total number of pixels: "+str(len(pix_val)))

# write dat file
print(">> Dat file written at "+loc+outdat)
f = open(loc + outdat, 'w')
write_dat (f, pix_val)

# grayscale input image
newimage = Image.new('L', (width,height))
newimage.putdata(np.array(pix_val))
newimage.save(f"{loc}gray_{fname}") 