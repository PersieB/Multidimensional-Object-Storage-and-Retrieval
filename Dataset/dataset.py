# Import relevant modules
import csv
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import plotly.express as px
from shapely.geometry import Point
import geopandas as gpd
from geopandas import GeoDataFrame


#Load Data
data_source = 'https://raw.githubusercontent.com/PersieB/Thesis/master/worldcities.csv'
dataset = pd.read_csv(data_source, engine='python')

"""
#Data info
#print(dataset.info())
#print(dataset.head())
#print(dataset.tail())
"""

#Number of Countries
count = dataset['country'].value_counts()
#print(count)

"""
#Create tuple for spatial data(geographic coordinates i.e lat, long)
#Export this dataframe to a csv file to be used for coordinate transformation
"""
#dataset['geo_tuple'] = list(zip(dataset.lat, dataset.lng))
#dataset.to_csv('geo_coordinates.csv')
del dataset['city_ascii']
del dataset['iso2']
del dataset['iso3']
del dataset['admin_name']
del dataset['id']
del dataset['capital']
#Remove space in coordinate

dataset.to_csv('newworld.csv', index=False)
#dataset['geo_tuple'].to_csv('onlygeo.csv', index=False)

"""
#Plotting the towns and cities on a world map
#NB: Spatial data given as points
#Get world map geopandas dataset. Wordmap is a GeoDataFrame object
"""
world_data = gpd.read_file(gpd.datasets.get_path('naturalearth_lowres'))

#Check CRS
#print(world_data.crs)

"""
#Since GeoDataFrame objects are coordinates in an arbitrary space, a CRS tells Python how those coordinates are related to places on the
# Earth. So, we need to tell python the coordinate reference system
#Need to convert our pandas dataframe into a geodataframe object
#We use geopandas points_from_xy() to transform Longitude and Latitude into a list of shapely.Point objects and set it as a geometry
# while creating the GeoDataFrame.
"""
dataset_geo = gpd.GeoDataFrame(dataset, geometry = gpd.points_from_xy(dataset.lng, dataset.lat))


#Set CRS the same as world map's
dataset_geo.set_crs(epsg=4326, inplace=True)
#print(dataset_geo.crs)

#Confirm that they're both in the same CRS
#print(world_data.crs == dataset_geo.crs)

#Plot Dataset on World Map
axis = world_data.plot(
    color='lightblue', edgecolor = 'grey'
)
dataset_geo.plot(ax = axis, color = 'black')
plt.title('WORLD CITIES AND TOWNS')

fig = matplotlib.pyplot.gcf()
fig.set_size_inches(15,10)
fig.savefig('map.jpg', dpi = 200)