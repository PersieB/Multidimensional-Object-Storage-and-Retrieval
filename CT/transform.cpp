
// import modules
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>
#include <tuple>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

int main()
{     
    ifstream data("temp1.csv");
    ofstream out_file("transform.txt");
    if (!data.is_open())
    {
        exit(EXIT_FAILURE);
    }
    string str;
    getline(data, str); // skip the first line
    while (getline(data, str))
    {
        istringstream iss(str);
        string token;
        while (getline(iss, token))
        {   
            // process each token

                token.erase( remove( token.begin(), token.end(), '\"' ),token.end());
                //std::cout << token << endl;
                out_file << token << endl;
        }
    }
}