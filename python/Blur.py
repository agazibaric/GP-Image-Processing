import cv2
import numpy as np

size = 10
width = 512
height = 512

# generating the kernel
with open("lenna.txt", "r") as f, open("lenna-blured.txt", "w") as f2:
    img = np.array([float(x) for x in f.readline().strip().split()]).reshape(width, height)

    kernel_motion_blur = np.zeros((size, size))
    kernel_motion_blur[int((size - 1) / 2), :] = np.ones(size)
    kernel_motion_blur = kernel_motion_blur / size

    # applying the kernel to the input image
    output = cv2.filter2D(img, -1, kernel_motion_blur).reshape(width * height, 1)
    out_format = " ".join([str(int(x)) for x in output])
    f2.write(out_format)
    cv2.imwrite("lenna-blured.png", output)


