import numpy as np
import matplotlib.pyplot as plt

width = 512
height = 512

with open("generated-img-edges.txt", "r") as f:
    values = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
    plt.imshow(values, 'gray')
    plt.show()
