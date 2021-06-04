import cv2
import numpy as np

width = 256
height = 256

# generating the kernel
imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

dirName = "./pngs/"
targetName = "inpaintingHard"
for imageName in imageNames:
    with open("./{}/".format(targetName) + "{}-{}.txt".format(imageName, targetName), "r") as f:
        img = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)
        cv2.imwrite(dirName + "/{}/".format(targetName) + "{}-{}.png".format(imageName, targetName), img)


