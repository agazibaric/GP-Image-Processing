import cv2
import numpy as np

width = 256
height = 256

pngDirName = "./pngs/"
dirName = "denoised9"

# Generated
for i in range(2):
    with open("./generated-img{}.txt".format(i), "r") as f:
        img = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
        cv2.imwrite("./{}/{}/{}-{}.png".format(pngDirName, dirName, dirName, i), img)

# Validation
for i in range(2, 8):
    with open("./validation-img{}.txt".format(i-2), "r") as f:
        img = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
        cv2.imwrite("./{}/{}/{}-{}.png".format(pngDirName, dirName, dirName, i), img)
