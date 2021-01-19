import cv2
import numpy as np

width = 512
height = 512

# generating the kernel
with open("training-img.txt", "r") as f:
    img = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
    cv2.imwrite("goal-img-blured.png", img)


