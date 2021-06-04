import numpy as np
import matplotlib.pyplot as plt
import cv2

width = 512
height = 512

with open("lenna-edges.txt", "r") as f, open("generated-img-edges.txt", "r") as f2:
    img1 = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
    img2 = np.array([float(x) for x in f2.readline().strip().split()]).reshape(width, height)
    c = np.concatenate((img1, img2), axis=1)
    cv2.imwrite("edges-concat.png", c)
