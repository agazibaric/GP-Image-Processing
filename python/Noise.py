import numpy as np
import random

width = 512
height = 512


def get_pixel_value():
    if random.uniform(0, 1) < 0.5:
        return 0
    return 255


with open("lenna.txt", "r") as f, open("lenna-noised.txt", "w") as f2:
    values = np.array([float(x) for x in f.readline().strip().split()])
    noised = np.array([get_pixel_value() if random.uniform(0, 1) < 0.05 else x for x in values])
    f2.write(" ".join([str(int(x)) for x in noised]))
