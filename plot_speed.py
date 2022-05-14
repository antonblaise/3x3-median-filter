import numpy as np
import matplotlib.pyplot as plt

def smooth(y, box_pts):
    box = np.ones(box_pts)/box_pts
    y_smooth = np.convolve(y, box, mode='same')
    return y_smooth

print(">> Reading speed data...")

speedData = [element * 1000 for element in list(map(float, open('./data/speed_ns.dat', 'r').read().splitlines()))]

print(">> Plotting the data...")

plt.figure(figsize=(20,15))
plt.plot(speedData, color='blue', linewidth=1)
plt.plot(smooth(speedData, 5000), color='red', linewidth=1)
plt.legend(['Speed','Smoothed'], loc='upper right')
# plt.ylim(0, 0.1)
plt.grid(True)
plt.title("3x3 Median Filter - Processing Speed\n", fontsize=30)
plt.xlabel("\nPixel number", fontsize=20)
plt.ylabel("Speed (megapixels per second)\n", fontsize=20)
plt.savefig("Speed.png")
# plt.show()

print(">> Speed per pixel plotted and saved as Speed.png.")