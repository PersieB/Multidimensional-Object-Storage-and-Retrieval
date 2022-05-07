import numpy as np
import matplotlib.pyplot as plt
 
  
# creating the dataset
data = {'100':11, '500':12, '1000':12, '1500':10, '2000':14, '2500':11, '3000':15}
cities = list(data.keys())
time = list(data.values())
  
#fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(cities, time, color ='maroon',
        width = 0.4)
 
plt.xlabel("Number of spatial objects (points as cities/towns)")
plt.ylabel("Time in microseconds")
plt.title("Multidimensional Object Removal with R-tree")
plt.show()