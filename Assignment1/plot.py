import pandas as pd
import numpy as np
import math
data = pd.read_csv('time.txt',sep=',',header=None)
data = pd.DataFrame(data)
import matplotlib.pyplot as plt
x = data[0]
plt.xlabel('p')
plt.ylabel('log(t)')
y = np.log(data[1])
plt.plot(x, y,'ro')
plt.show()
