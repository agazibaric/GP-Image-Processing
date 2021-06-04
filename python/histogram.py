import matplotlib.pyplot as plt

x = [5.81, 5.76, 5.88, 6.10, 6.05, 6.04, 5.74, 5.76, 6.54, 5.82]

plt.title('Eksperiment s linearnim skaliranjem')
plt.xlabel('Iznos dobrote')
plt.ylabel('Frekvencija')

plt.hist(x, bins=10, color='grey')
plt.show()
