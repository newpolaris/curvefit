import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


source = open("data_150.txt", "r")
src = source.read()
src = src.split("\n")
n_data = []
for i in src:
    n_data.append(i.split("\t"))
src = n_data[1:]
x = []
y = []
for i in src:
    x.append(float(i[0]))
    y.append(float(i[1]))

xxx = open("3-dgree-regression_results.txt", "r")
data = xxx.read()
data = data.split("\n")
n_data = []
for i in data:
    n_data.append(i.split("\t"))
data = n_data[:-1]
X = []
Y = []

for i in data:
    X.append(float(i[0]))
    Y.append(float(i[1]))
plt.title("data for regression")
plt.plot(X,Y,"r-",label="recovered")
plt.plot(x,y, "b.")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.show()
