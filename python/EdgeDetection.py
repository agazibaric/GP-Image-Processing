import cv2
import numpy as np
from matplotlib import pyplot as plt

width = 512
height = 512

img = cv2.imread('lenna.png', 0)
edges = cv2.Canny(img, 100, 100)

with open("lenna-edges.txt", "w") as f:
    values = edges.reshape(width * height, 1)
    f.write(" ".join([str(int(x)) for x in values]))


plt.subplot(121), plt.imshow(img,cmap = 'gray')
plt.title('Original Image'), plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(edges,cmap = 'gray')
plt.title('Edge Image'), plt.xticks([]), plt.yticks([])

plt.show()
