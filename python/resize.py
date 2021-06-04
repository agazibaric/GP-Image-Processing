import cv2

width = 256
height = 256

imageNames = ["cameraman", "lenna", "house", "jetplane", "lake", "livingroom", "mandril", "peppers", "pirate",
              "walkbridge", "woman_blonde"]

for imageName in imageNames:
    with open("original/" + imageName + ".txt", "w") as f:
        image = cv2.imread('images/' + imageName + '.tif', 0)
        resized = cv2.resize(image, (width, height))
        resized = resized.reshape(width * height, 1)
        out_format = " ".join([str(int(x)) for x in resized])
        f.write(out_format)
