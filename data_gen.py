import numpy as np
import matplotlib.pyplot as plt

x = 5 * np.random.rand(1,150)
y = -2 * pow(x,3) + 9 *pow(x,2) + -3 * x + 7 + 4 * np.random.rand(1,150) 

xx = open("data_150.txt","w")
xx.write("150")
for i in range(150):
    xx.write("\n")
    xx.write(str(round(x[0][i],5)))
    xx.write("\t")
    xx.write(str(round(y[0][i],5)))
xx.close()
