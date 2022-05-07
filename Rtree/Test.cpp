//
// Test.cpp
//
// This is a direct port of the C version of the RTree test program.
//
#include "RTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>
#include <string>
#include <tuple>
#include <cmath>
#include <sstream>
#include <chrono>
#include "../CT/coordTrans.cpp"


using namespace std;
using namespace std::chrono;

struct Rect
{
  Rect()  {}

  Rect(double X, double Y)
  {
    int a_minX = round(X);
    int a_minY = round(Y);
    min[0] = a_minX;
    min[1] = a_minY;
    max[0] = a_minX;
    max[1] = a_minY;
  }


  int min[2];
  int max[2];
};



bool MySearchCallback(int id, void* arg) 
{
  printf("Hit data rect %d\n", id);
  return true; // keep going
}

int main(){
    RTree<int, int, 2, float> tree;
    ifstream ifs("../Dataset/tempworld.csv");
    string line;
    getline(ifs, line); // skip the first line
    string city, lat, lng, cty, popln,geotup;

        // measure time for building
    auto startBuild = high_resolution_clock::now();
    int i=0;
    while(getline(ifs, line)) // read one line from ifs
    {
        istringstream lineStream(line);
        getline(lineStream, city, ',');
        getline(lineStream, lat, ',');
        getline(lineStream, lng, ',');

        string token = (lat +',' + lng);
        tuple<double,double> transformed = geoCordTrans(token);
        //cout << get<0>(transformed) << ',' << get<1>(transformed) << endl;
        double arr[2] = {get<0>(transformed), get<1>(transformed)};
        struct Rect rects{get<0>(transformed), get<1>(transformed)};
        tree.Insert(rects.min, rects.max, i);
        i++;
    }
    auto stopBuild = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit use duration cast method
    auto durationBuild = duration_cast<microseconds>(stopBuild - startBuild);
    cout << "Time taken to build R-tree: " << durationBuild.count() << " microseconds" << endl;

    // Tree searching time
  
    string latitude2 = "19.4333"; string longitude2 = "-99.1333"; 
    string geoCords1 = (latitude2 + ',' + longitude2);
    auto startSearch = high_resolution_clock::now();
    tuple<double, double> cart1 = geoCordTrans(geoCords1);
    double search1[] = {get<0>(cart1), get<1>(cart1)};
    Rect search_rect(round(search1[0]), round(search1[1])); // search will find above rects that this one overlaps
    int nhits = tree.Search(search_rect.min, search_rect.max, MySearchCallback, NULL);
    auto stopSearch = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit use duration cast method
    auto durationSearch = duration_cast<microseconds>(stopSearch - startSearch);
    cout << "Time taken to search given geographic coordinates in R-tree: " << durationSearch.count() << " microseconds" << endl;
    
    cout << endl;

    printf("Search resulted in %d hits\n", nhits);

    // Tree deletion time
    string latitude3 = "35.6897"; string longitude3 = "139.6922"; 
    string geoCords2 = (latitude3 + ',' + longitude3);
    auto startDelete = high_resolution_clock::now();
    tuple<double, double> cart2 = geoCordTrans(geoCords2);
    double p1[] = {get<0>(cart2), get<1>(cart2)};
    Rect search_rect1(round(p1[0]), round(p1[1]));
    tree.Remove(search_rect1.min, search_rect1.max, 5);
    auto stopDelete = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto durationDelete = duration_cast<microseconds>(stopDelete - startDelete);
    cout << "Time taken to search delete geographic coordinates in R-tree: " << durationSearch.count() << " microseconds" << endl;

    /*
    // Iterator test 
    int itIndex = 0;
    RTree<int, int, 2, float>::Iterator it;
    for( tree.GetFirst(it); 
        !tree.IsNull(it);
        tree.GetNext(it) )
    {
      int value = tree.GetAt(it);
      
      int boundsMin[2] = {0,0};
      int boundsMax[2] = {0,0};
      it.GetBounds(boundsMin, boundsMax);
      printf("it[%d] %d = (%d,%d,%d,%d)\n", itIndex++, value, boundsMin[0], boundsMin[1], boundsMax[0], boundsMax[1]);
    }
    
    // Iterator test, alternate syntax
    itIndex = 0;
    tree.GetFirst(it);
    while( !it.IsNull() )
    {
      int value = *it;
      ++it;
      printf("it[%d] %d\n", itIndex++, value);
    }


    /*
    string latitude4 = "35.6897"; string longitude4 = "139.6922"; 
    string geoCords3 = (latitude4 + ',' + longitude4);
    auto startSearch1 = high_resolution_clock::now();
    tuple<double, double> cart3 = geoCordTrans(geoCords3);
    double search2[] = {get<0>(cart3), get<1>(cart3)};
    Rect search_rect2(round(search2[0]), round(search2[1])); // search will find above rects that this one overlaps
    int nhits1 = tree.Search(search_rect2.min, search_rect2.max, MySearchCallback, NULL);
    auto stopSearch1 = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit use duration cast method
    auto durationSearch1 = duration_cast<microseconds>(stopSearch1 - startSearch1);
    cout << "Time taken to search given geographic coordinates in R-tree: " << durationSearch1.count() << " microseconds" << endl;
    
    cout << endl;

    printf("Search resulted in %d hits\n", nhits1);  */


    return 0; 
}
