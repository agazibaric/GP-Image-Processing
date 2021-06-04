import numpy as np
import cv2

imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

width, height = 256, 256

for imageName in imageNames:
    img = cv2.imread("images/" + imageName + '.tif', 0)
    img = cv2.resize(img, (width, height))
    mean = 0
    sigma = 12
    gauss = np.random.normal(mean, sigma, (width, height))
    gauss = gauss.reshape(width, height)
    noisy = img + gauss

    noisy = noisy.reshape((width * height, 1))
    with open("gaussian/" + imageName + "-gaussian.txt", "w") as f:
        f.write(" ".join([str(int(x)) for x in noisy]))
