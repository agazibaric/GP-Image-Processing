import cv2
import numpy as np

width = 256
height = 256

imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

dirName = "inpaintingHard"

for imageName in imageNames:
    img = cv2.imread("images/" + imageName + '.tif', 0)
    img = cv2.resize(img, (width, height))
    for index, row in enumerate(img):
        if (index + 2) % 4 == 0 or (index + 1) % 4 == 0:
            for i in range(len(row)):
                row[i] = 0

    img = img.reshape((width * height, 1))
    with open(dirName + "/" + imageName + "-" + dirName + ".txt", "w") as f:
        f.write(" ".join([str(int(x)) for x in img]))
