/*
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
*/
#include <iostream>
#include <tuple>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

double degtoTrad(double geoDeg)
{
    return geoDeg * M_PI / 180;
}

string removePar(string coordinates){
    int i=0;
    while(i < coordinates.size()){
        if(coordinates[i] == '(' || coordinates[i] == ')')
        {
            coordinates.erase(i,1);
        } else {
            i++;
        }
    }
    return coordinates;
}

vector<string> split(string x, char delim = ',')
{
    x += delim; //includes a delimiter at the end so last word is also read
    vector<string> splitted;
    string temp = "";
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == delim)
        {
            splitted.push_back(temp); //store coordinates in "splitted" vector
            temp = "";
            i++;
        }
        temp += x[i];
    }
    return splitted;
}


tuple<double,double> geoCordTrans(string points){
    string coordinates = removePar(points);
    vector<string> result = split(coordinates);
    double lati = stod(result[0]);
    double longitu = stod(result[1]);


    // semi-major axis of the ellipse - WGS 84
    long A = 6378137;

    // semi-minor axis of the ellipse - WGS 84
    long B = 6356752;

    // Now convert degrees to radians
    double latitude = degtoTrad(lati);
    double longitude = degtoTrad(longitu);

    // no height specified in our dataset. And considering the formula, the height appears to have no significant impact on the final results.

    double e = sqrt(1 - pow(B,2)/pow(A,2));
    double N = A / sqrt(1 - pow(e,2) * pow(sin(latitude),2));
    double X = (N) * cos(latitude) * cos(longitude);
    double Y = (N) * cos(latitude) * sin(longitude);

    X = (int)(X * 100 + .5);
    X = (double)X / 100;
    Y = (int)(Y * 100 + .5);
    Y = (double)Y / 100;

    tuple <double,double> cartCoord;
    cartCoord = make_tuple(X,Y);
    return cartCoord;

}

/*
int main(){
    ifstream dataFile("../Dataset/geo_coordinates.csv");

  
    // Open an existing file
    //fin.open("../Dataset/geo_coordinates.csv", ios::in);
    cout << get<0>(geoCordTrans(("(35.6897,139.6922)"))) << ',' << get<0>(geoCordTrans(("(-6.2146,106.8451)"))) << endl;


}*/