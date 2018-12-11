#ifndef _ASTARSEARCH
#define _ASTARSEARCH

#include "Results.h"
#include "layer.h"
#include <iostream>
#include <vector> // for 2D vector

#include<bits/stdc++.h>
using namespace std;

#define ROW 51
#define COL 52

typedef pair<int, int> Pair;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the neccesary parameters
struct cell
{
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

bool isValid(int row, int col);

bool isUnBlocked(int grid[][COL], int row, int col);

bool isDestination(int row, int col, Pair dest);

double calculateHValue(int row, int col, Pair dest);

void printArray(int temp_vector[][COL], int row, int col);

void printVector(vector<vector<int> > temp_vector);

double distanceBetweenTwoPoints(double x, double y, double a, double b);

void tracePath(stack<Pair>& foo, int grid[][COL], cell cellDetails[][COL], Pair src, Pair dest);

void aStarSearch(stack<Pair>& foo, int grid[][COL], Pair src, Pair dest);

vector<Point> Promote_segment(vector<Layer> &layerarray, int grid[][COL], APC apc0, APC apc1, double layer1start, double layer2start, double stepxx, double stepyy, int layer_index, vector <ViaResult> &viaarray);

int vector_uniqueness(vector<int> vec);

void APC_process(vector <Layer> &layerarray, vector <SegmentResult> &segmentarray, vector <ViaResult> &viaarray, int layer_index, int panelIdx, double layer1start, double layer2start, double stepxx, double stepyy);

#endif