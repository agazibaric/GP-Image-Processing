import numpy as np
import matplotlib.pyplot as plt

width = 28
height = 28

with open("Original.txt", "r") as f:
    values = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
    plt.imshow(values, 'gray')
    plt.show()
