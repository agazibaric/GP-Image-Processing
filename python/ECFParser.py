import matplotlib.pyplot as plt

fileName = "log.txt"

mins, maxs, avgs = [], [], []
gens = 0
with open(fileName) as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        if "min" in line:
            mins.append(float(line.split(" ")[1]))
        elif "max" in line:
            maxs.append(float(line.split(" ")[1]))
        elif "avg" in line:
            avgs.append(float(line.split(" ")[1]))
        elif "Generation" in line:
            gens = int(line.split(" ")[1])

plt.plot([i for i in range(0, gens + 1, 10)], mins)
plt.show()