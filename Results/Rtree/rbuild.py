import numpy as np
import matplotlib.pyplot as plt
 
  
# creating the dataset
data = {'100':640, '500':3283, '1000':6942, '1500':10145, '2000':15323, '2500':18269, '3000':24975}
cities = list(data.keys())
time = list(data.values())
  
#fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(cities, time, color ='maroon',
        width = 0.4)
 
plt.xlabel("Number of spatial objects (points as cities/towns)")
plt.ylabel("Time in microseconds")
plt.title("Multidimensional Object Storage with R-tree")
plt.show()