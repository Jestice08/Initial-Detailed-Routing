#ifndef _CREATEAPC
#define _CREATEAPC

#include <iostream>
#include <vector>
//#include <RawDataBase.h>
using namespace std;
#include "layer.h"
//#include "layer.h"
//#include "creategrid.h"
vector<AP>  CreateApcs(Guide &guideLow, Guide &guideHigh,Panel &panelLow, Panel &panelHigh, int layerindex);

#endif