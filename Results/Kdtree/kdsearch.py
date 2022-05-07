import numpy as np
import matplotlib.pyplot as plt
 
  
# creating the dataset
data = {'100':5, '500':5, '1000':5, '1500':5, '2000':5, '2500':5, '3000':6}
cities = list(data.keys())
time = list(data.values())
  
#fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(cities, time, color ='maroon',
        width = 0.4)
 
plt.xlabel("Number of spatial objects (points as cities/towns)")
plt.ylabel("Time in microseconds")
plt.title("Multidimensional Object Search with Kd-tree")
plt.show()