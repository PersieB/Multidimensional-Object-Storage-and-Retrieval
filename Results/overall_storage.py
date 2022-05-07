import numpy as np 
import matplotlib.pyplot as plt 
  
X = ['100','500','1000','1500', '2000', '2500', '3000']
Ygirls = [5,5,5,5,5,5,6]
Zboys = [11,12,12,10,14,11,15]
  
X_axis = np.arange(len(X))
  
plt.bar(X_axis - 0.2, Ygirls, 0.4, color = 'maroon', label = 'Kd-tree')
plt.bar(X_axis + 0.2, Zboys, 0.4, color = 'grey', label = 'R-tree')
  
plt.xticks(X_axis, X)
plt.xlabel("Number of spatial objects")
plt.ylabel("Storage Time (microseconds")
plt.title("Multidimensional Object Removal in Kd-tree and R-tree")
plt.legend()
plt.show()