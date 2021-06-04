import cv2
import numpy as np

size = 5
width = 256
height = 256

imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

for imageName in imageNames:
    # generating the kernel
    with open("original/" + imageName + ".txt", "r") as f, open("dilate/" + imageName + "-dilate.txt", "w") as f2:
        img = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
        kernel = np.ones((size, size))
        output = cv2.dilate(img, kernel, iterations=1).reshape(width * height, 1)
        f2.write(" ".join([str(int(x)) for x in output]))
