import cv2
import numpy as np

imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

width, height = 256, 256

for imageName in imageNames:
    img = cv2.imread('images/' + imageName + '.tif', cv2.IMREAD_GRAYSCALE)
    grad_x = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=3)
    grad_y = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=3)

    abs_grad_x = cv2.convertScaleAbs(grad_x)
    abs_grad_y = cv2.convertScaleAbs(grad_y)

    grad = cv2.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)
    grad = cv2.resize(grad, (width, height))

    img = grad.reshape((width * height, 1))
    with open("sobel/" + imageName + "-sobel.txt", "w") as f:
        f.write(" ".join([str(int(x)) for x in img]))
