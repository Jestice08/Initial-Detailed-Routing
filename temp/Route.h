#ifndef _ROUTE
#define _ROUTE

#include <algorithm>
#include <vector>
#include <boost/bind.hpp>
#include <iostream>
#include "layer.h"
#include "Results.h"
#include "overlap.h"
#include "creategrid.h"
#include "AStarSearch.h"
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include "../parser/lefdef/DefDriver.h"
#include "../parser/lefdef/LefDriver.h"
#include "../parser/lefdef/RawDataBase.h"
#include "../parser/lefdef/RawDataBase2.h"
using namespace std;
using namespace boost;
using namespace DefParser;


//void CreateGrid(Layer &layerarray[layer_index], RawDataBase &db,double layer1start,double layer2start,double stepxx,double stepyy);

void Route (vector <Layer> &layerarray, vector <SegmentResult> &segmentarray, vector <ViaResult> &viaarray, double layer1start, double layer2start, double stepxx, double stepyy);

#endif