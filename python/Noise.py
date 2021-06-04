import numpy as np
import random

width = 256
height = 256


def get_pixel_value():
    if random.uniform(0, 1) < 0.5:
        return 0
    return 255


imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

dirName = "noiseHard"

for imageName in imageNames:
    with open(imageName + ".txt", "r") as f, open(dirName + "/" + imageName + "-" + dirName + ".txt", "w") as f2:
        values = np.array([float(x) for x in f.readline().strip().split()])
        noised = np.array([get_pixel_value() if random.uniform(0, 1) < 0.1 else x for x in values])
        f2.write(" ".join([str(int(x)) for x in noised]))
