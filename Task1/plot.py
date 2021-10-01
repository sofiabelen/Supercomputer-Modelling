import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from scipy.optimize import curve_fit
from scipy.interpolate import UnivariateSpline

# def line(x, a, b):
#     return a*x + b

data = np.genfromtxt('data.csv', names=True)

# popt, pcov = curve_fit(f=line, xdata=data['m'],
#         ydata=data['r']**2)
# 
# print(popt[0])
# print(pcov)

x = [1, 2, 4, 8, 16, 24, 32, 40, 38]

sns.set(context='notebook', style='darkgrid')
fig, ax = plt.subplots(figsize=(6, 6))

ax.set_xlabel(r'Number of threads')
ax.set_ylabel(r'Time, s')

plt.plot(x, data['a'], label='Matrix 500 x 500')
plt.plot(x, data['b'], label='Matrix 1000 x 1000')
plt.plot(x, data['c'], label='Matrix 1500 x 1500')

ax.legend()

fig.savefig("img/graph1.pdf")
plt.show()
