import cv2
import numpy as np
from matplotlib import pyplot as plt

width = 256
height = 256

imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

for imageName in imageNames:
    img = cv2.imread("images/" + imageName + '.tif', 0)
    img = cv2.resize(img, (width, height))
    edges = cv2.Canny(img, 100, 100)
    values = edges.reshape(width * height, 1)

    with open("edge/" + imageName + "-edge.txt", "w") as f:

        f.write(" ".join([str(int(x)) for x in values]))

# plt.subplot(121), plt.imshow(img,cmap = 'gray')
# plt.title('Original Image'), plt.xticks([]), plt.yticks([])
# plt.subplot(122),plt.imshow(edges,cmap = 'gray')
# plt.title('Edge Image'), plt.xticks([]), plt.yticks([])
#
# plt.show()
