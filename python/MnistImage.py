import numpy as np
import matplotlib.pyplot as plt

width = 256
height = 256

with open("generated-img0.txt", "r") as f:
    values = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
    plt.imshow(values, 'gray')
    plt.show()
