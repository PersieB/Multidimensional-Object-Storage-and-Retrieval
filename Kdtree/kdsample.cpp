/*
Author: Percy Brown
Date: 28th February 2022 @ 01:23 GMT

Description:
A custom implementation of KD-Tree.
KD-Tree in the form of 2D-tree, since our location data will be represented in 2D-coordinates form
Algorithm is built for our benchmark dataset from World Cities Databases containing about 41,000 cities ond/or towns/islands.
*/

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
#include <chrono>
#include "../CT/coordTrans.cpp"

using namespace std;
using namespace std::chrono;

// dimension of KD-tree
const int kDimension = 2;

/* 
Just like every other tree, KD-tree contains nodes
We define a structure (struct) to represent KD-tree node
Every node contains the spatial data, and pointers to their left or right subtrees (if any)
*/

struct KDTreeNode{
    double coordinates[kDimension];
    KDTreeNode *leftSubtree, *rightSubtree;
};

/*
A function that creates a node in a KD-tree
Takes the location points as parameter and creates a node for each point
Returns the new Node created
*/

KDTreeNode* createKDNode(double spatialData[kDimension]){
    KDTreeNode *newNode = new KDTreeNode;
    for(int i=0; i<kDimension; i++){
        newNode->coordinates[i] = spatialData[i];
    }
    newNode->leftSubtree = newNode->rightSubtree = NULL;
    return newNode;
};

/* 
Storing data into Kd-tree
Takes the root node, the new point to be inserted and the axis of comparison for splitting (depth)
*/

KDTreeNode *storeSpatial(KDTreeNode *rootNode, double spatialData[kDimension], unsigned depth){
    // first check if tree is empty
    if (rootNode == NULL){
        return createKDNode(spatialData);
    }

    /*
    KD-tree nodes are constructed based on splitting on the axis
    The axis alternate during splitting. In 2D, 0 means x-aligned plane splitting while 1 means y-aligned
    Parameter depth starts from 0, and the alternating aligned planes are achieved by taking the depth % kDimension (2)
    Hence, 0 % 2 gives 0r0, whre r=0 stands for an x-aligned plane while 1%2 = 0r1, where r=1 stands for a
    y-aligned plane. The depth increases by 1 on each level of the tree, resulting in the alternation of the
    axis-aligned planes for splitting from 0s to 1s. Here, we calculate the current dimension of comparison to
    determine the axis-aligned plane for the levels in the tree
    */

   unsigned axisAligned = depth % kDimension;

    /*
    Now, let us compare the new point to be added to the root's dimension
    To determine if the point should be in the left or right subtree based on the value to compare
    */

    // Recursively compare before insertion at each level in the tree by alternating the axis-aligned plane
    if (spatialData[axisAligned] < rootNode->coordinates[axisAligned]){
        rootNode->leftSubtree = storeSpatial(rootNode->leftSubtree, spatialData, depth+1);
    }
    else{
        rootNode->rightSubtree = storeSpatial(rootNode->rightSubtree, spatialData, depth+1);
    }
    return rootNode;
}

/*
A function to insert a new location point into the tree
Uses the function "storeSpatial" recursively
Returns the root
*/

KDTreeNode *storeData(KDTreeNode *rootNode, double locationData[kDimension]){
    return storeSpatial(rootNode, locationData, 0);
}

/*
A helper function to check if two location points are the same
Would be useful when searching for points in the tree
Takes two points as parameters
Returns a boolean value based on comparison
*/

bool areEqual(double point1[kDimension], double point2[kDimension])
{
    // Compare individual pointinate values
    for (int i = 0; i < kDimension; ++i)
        if (point1[i] != point2[i])
            return false;
  
    return true;
}

/*
A function to query tree and search for location point
Takes the root, point to be searched, and depth as parameters
The parameter depth, as explained earlier will be used to determine the current axis-aligned plane for comparison
Returrns a boolean after search
*/

bool checkTree(KDTreeNode *rootNode, double locationData[kDimension], unsigned depth){
    // Base cases
    if (rootNode == NULL){
        return false;
    }
    // check if location data to be searched is at the root
    if (areEqual(rootNode->coordinates, locationData)){
        return true;
    }

    // compute current axis dimension
    unsigned axisAligned = depth % kDimension;

    // compare point with root to decide whether to search left or right subtree
    if (locationData[axisAligned] < rootNode->coordinates[axisAligned]){
        return checkTree(rootNode->leftSubtree, locationData, depth+1);
    }
    return checkTree(rootNode->rightSubtree, locationData,depth+1);

   
}

/*
Function searches for a point in our KD-tree
Uses the function "checkTree" recirsively
Returns a boolean
*/

bool searchData(KDTreeNode *rootNode, double locationData[kDimension]){
    return checkTree(rootNode, locationData,0);
}

/*
PRINT TREE IN A NEAT WAY
*/

void printBT(const string& prefix, const KDTreeNode* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        cout << node->coordinates[0] << ',' << node->coordinates[1] << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->leftSubtree, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->rightSubtree, false);
    }
}

void printBT(const KDTreeNode* node)
{
    printBT("", node, false);    
}

/*
Utility function for minimum of 3 (float) numbers 
Returns the node under consideration
*/

KDTreeNode *getminNode(KDTreeNode *x, KDTreeNode *y, KDTreeNode *z, unsigned dthDimension)
{
    KDTreeNode *resultNode = x;
    if (y != NULL && y->coordinates[dthDimension] < resultNode->coordinates[dthDimension])
       resultNode = y;
    if (z != NULL && z->coordinates[dthDimension] < resultNode->coordinates[dthDimension])
       resultNode = z;
    return resultNode;
}

/*
Function that recursively finds the dth dimension in the KD-tree
Parameter depth is used to indicate the current axis under consideration at each level
Returns the node with the minimum dth dimension
*/

KDTreeNode *findMinRec(KDTreeNode* rootNode, unsigned dthDimension, unsigned depth)
{
    // Base cases
    if (rootNode == NULL){
        return NULL;
    }
  
    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned axisAligned = depth % kDimension;
  
    // Compare point with root with respect to axisAligned (Current dimension)
    if (axisAligned == dthDimension)
    {
        if (rootNode->leftSubtree == NULL)
            return rootNode;
        return findMinRec(rootNode->leftSubtree, dthDimension, depth+1);
    }
  
    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return getminNode(rootNode,
               findMinRec(rootNode->leftSubtree, dthDimension, depth+1),
               findMinRec(rootNode->rightSubtree, dthDimension, depth+1), dthDimension);
}

/*
A wrapper function of "findMinRec"
Returns the node with the minimum dth dimension
*/

KDTreeNode *findMin(KDTreeNode* rootNode, unsigned dthDimension)
{
    // Pass current level or depth as 0
    return findMinRec(rootNode, dthDimension, 0);
}

// Copies point p2 to p1
void copyPoint(double point1[], double point2[])
{
   for (int i=0; i<kDimension; i++)
       point1[i] = point2[i];
}

/*
Function to delete location point (node)
Returns the modified root, if there is
*/

KDTreeNode *deleteSpatial(KDTreeNode *rootNode, double point[kDimension], unsigned depth)
{
    // Given point is not present
    if (rootNode == NULL)
        return NULL;

    // Find dimension of current node
    unsigned axisAligned = depth % kDimension;

    // If the point to be deleted is present at root

    if (areEqual(rootNode->coordinates, point))
    {
        // 2.b) If right child is not NULL
        if (rootNode->rightSubtree != NULL)
        {
            // Find minimum of root's dimension in right subtree
            KDTreeNode* minNode = findMin(rootNode->rightSubtree, axisAligned);

            // copy
            copyPoint(rootNode->coordinates, minNode->coordinates);
  
            // Recursively delete the minimum
            rootNode->rightSubtree = deleteSpatial(rootNode->rightSubtree,minNode->coordinates, depth+1);
        }
        else if (rootNode->leftSubtree != NULL) // same as above
        {
            
            KDTreeNode * minNode = findMin(rootNode->leftSubtree, axisAligned);
            copyPoint(rootNode->coordinates, minNode->coordinates);
            rootNode->rightSubtree = deleteSpatial(rootNode->leftSubtree, minNode->coordinates, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            delete rootNode;
            return NULL;
        }
        return rootNode;
    }
    
  
    // 2) If current node doesn't contain point, search downward
    if (point[axisAligned] < rootNode->coordinates[axisAligned])
        rootNode->leftSubtree = deleteSpatial(rootNode->leftSubtree, point, depth+1);
    else
        rootNode->rightSubtree = deleteSpatial(rootNode->rightSubtree, point, depth+1);

    return rootNode;
}

/* 
Function to delete a given point from K D Tree with 'root'
A wrapper function for "deleteSpatial"
Returns the new root
*/
KDTreeNode* deleteNode(KDTreeNode *rootNode, double point[])
{
   // Pass depth as 0
   return deleteSpatial(rootNode, point, 0);
}

tuple<double,double> separate(string str)
{
    vector<string> coords;
    string word = "";
    for (auto x : str) 
    {
        if (x == ',')
        {
            //cout << word << endl;
            coords.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    coords.push_back(word);
    double X = stof(coords[0]);
    double Y = stof(coords[1]);
    tuple <double,double> cartCoord;
    cartCoord = make_tuple(X,Y);
    return cartCoord;
}

vector<float> check(string str){
    vector<string> coords;
    vector<float> cs;
    string word = "";
    for (auto x : str) 
    {
        if (x == ',')
        {
            //cout << word << endl;
            coords.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    coords.push_back(word);
    float x = stof(coords[0]);
    float y = stof(coords[0]);
    cs.push_back(x);
    cs.push_back(y);
    return cs;
    
}

/*

vector<string> change(string x, char delim = ',')
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

/*
Main function for testing above functions
*/

int main(){

    KDTreeNode *rootNode = NULL;
    
    // creating KD-tree with all data points
    string x;
    ifstream dataFile("../CT/transform.txt");
    double coord[kDimension];

    // measure time for building
    auto startBuild = high_resolution_clock::now();
    while (!dataFile.fail() && !dataFile.eof() )
    {
          dataFile >> x ;
            stringstream  data(x);
            string line;
            while(getline(data,line))
            {
                vector<string> result = split(line);
                double xc = stod(result[0]);
                double yc = stod(result[1]);
                double arr[result.size()] = {xc, yc};
               rootNode = storeData(rootNode, arr);
            }
    }
    auto stopBuild = high_resolution_clock::now();
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto durationBuild = duration_cast<microseconds>(stopBuild - startBuild);
    cout << "Time taken to build Kd-tree: " << durationBuild.count() << " microseconds" << endl;

    printBT(rootNode);
/*
    cout << "TREE BUILDING & OBJECT STORAGE" << endl;
    cout << endl;
    cout << "Left subtree notation: ├──,    Right subtree notation: └──" << endl;
    cout << endl;
    // pass the root node of your binary tree to start printing the tree
    printBT(rootNode);

    cout << endl;
    cout << "NODE SEARCH \n";
    cout << "NODE with Data (10,19) \n";




    // measure time for search

    tuple<string, string> geoCords1 = {"35.6897","139.6922"};
    auto startSearch = high_resolution_clock::now();
    tuple<double, double> cart1 = geoCordTrans(geoCords1);
    double point1[] = {get<0>(cart1), get<1>(cart1)};
    //double point1[] = {-3954863.760086529,3354894.1017490793};
   // cout << point1[1] << endl;
    (searchData(rootNode, point1))? cout << "Found\n": cout << "Not Found\n";
    auto stopSearch = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto durationSearch = duration_cast<microseconds>(stopSearch - startSearch);
    cout << "Time taken to search given geographic coordinates: " << durationSearch.count() << " microseconds" << endl;
    
    cout << endl;

    
    // Delete (6,12);
    cout << endl;
    cout << "NODE DELETION \n";
    //cout << "NODE with Data (6,12) \n";



    // measure time for deletion

    tuple<string, string> geoCords2 = {"35.6897","139.6922"};
    auto startDelete = high_resolution_clock::now();
    tuple<double, double> cart2 = geoCordTrans(geoCords2);
    double p1[] = {get<0>(cart2), get<1>(cart2)};
    //double p1[] = {6,12};
    KDTreeNode * newrootNode = deleteNode(rootNode, p1);
    auto stopDelete = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto durationDelete = duration_cast<microseconds>(stopDelete - startDelete);
    cout << "Time taken to delete given geographic coordinates: " << durationSearch.count() << " microseconds" << endl;
    
    cout << endl;
*/
    return 0; 
}