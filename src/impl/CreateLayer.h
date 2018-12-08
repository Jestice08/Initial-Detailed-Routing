#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include<algorithm>
#include "../parser/lefdef/GuideReader.h"
#include "layer.h"
using namespace std;

std::string Generate_Tobepushed (int idx, GuideDataBase &gdb, vector <OriginalGuide> &to_be_pushed_guide);

int extractLayerFromLayerName (std::string str);

int gcd(int a, int b);

int findGCD(vector<int> &arr);

double findUnitWidthH (vector <OriginalGuide> &to_be_pushed_guide, vector <int > &width, double &maxRightLocation);

double findUnitWidthV (vector <OriginalGuide> &to_be_pushed_guide, vector <int > &width, double &maxRightLocation);

void CreatePanelH (vector <OriginalGuide> &to_be_pushed_guide, Layer &temp, double unitWidth, double &minLeftLocation, double maxRightLocation);

void CreatePanelV (vector <OriginalGuide> &to_be_pushed_guide, Layer &temp, double unitWidth, double &minLeftLocation, double maxRightLocation);

void CreateLayer (GuideDataBase &gdb, vector <Layer> &layerarray);

bool less_bottom(const Guide & m1, const Guide & m2);
