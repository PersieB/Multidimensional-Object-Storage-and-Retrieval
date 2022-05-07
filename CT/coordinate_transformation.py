"""
Convert lat/long coordinates into cartesian form (x,y) coordinates. The geodetic coordinates including latitude and longitude in degrees
and optionally the ellipsoid height (in metres): (h, φ, λ) are related to the corresponding Cartesian coordinates (x, y, z)
by (Heiskanen and Moritz, 1967), where x = λ,y = φ and z = h

Assumption that the earth is an ellipsoid.

Formulae:

X = (N + h) * cos φ * cos λ

Y = (N + h) * cos φ * sin λ

Z = [ N* (1-e²) + h ] * sin φ

Where : N = radius of curvature in the prime vertical : N = A/(√1 - e² *sin a ² φ)

e = first eccentricity : e² = (A² - B²)/A² or e² = 1-(B²/A²)
"""

#Import modules
import math
import csv
import pandas as pd
import re
import time

#Load Data
data_source = '../Dataset/geo_coordinates.csv'
dataset = pd.read_csv(data_source, engine='python')

def removeSpace(sentence):
    sentence = re.sub(r"\s+", "", sentence, flags=re.UNICODE)
    print(sentence)

#Function for CT
def coordinate_transformation(geographic_tuple):   #returns x, y and (optionally) z
    geographic_tuple = eval(geographic_tuple)
    latitude = geographic_tuple[0]
    longitude = geographic_tuple[1]

    #semi-major axis of the ellipse - WGS 84
    A = 6378137

    #semi-minor axis of the ellipse - WGS 84
    B = 6356752

    # Now convert degrees to radians
    latitude = math.radians(latitude)
    longitude = math.radians(longitude)

    #   no height specified in our dataset. And considering the formula, the height appears to have no significant impact on the final results.

    e = math.sqrt(1 - (B**2)/(A**2))
    N = A / math.sqrt(1 - e**2 * math.sin(latitude)**2)
    X = (N) * math.cos(latitude) * math.cos(longitude)
    Y = (N) * math.cos(latitude) * math.sin(longitude)

    return (X, Y)

#Apply CT to all spatial data in the dataset





start = time.time()
dataset['cartesian'] = dataset['geo_tuple'].apply(coordinate_transformation)
end = time.time()
print(end - start)
dataset['cartesian'].to_csv('temp.csv', index=False)

#Remove space in coordinate
with open('temp.csv', 'r') as f:
    txt = f.read().replace('(', '').replace(')','').replace(' ','')

with open('temp.csv', 'w') as f:
    f.write(txt)

