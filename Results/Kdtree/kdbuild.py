


import numpy as np
import matplotlib.pyplot as plt
 
  
# creating the dataset
data = {'100':369, '500':1694, '1000':3151, '1500':5897, '2000':6468, '2500':8143, '3000':9817}
cities = list(data.keys())
time = list(data.values())
  
#fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(cities, time, color ='maroon',
        width = 0.4)
 
plt.xlabel("Number of spatial objects (points as cities/towns)")
plt.ylabel("Time in microseconds")
plt.title("Multidimensional Object Storage (Tree Construction) with Kd-tree")
plt.show()