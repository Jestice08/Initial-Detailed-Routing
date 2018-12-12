#include "../parser/lefdef/LefReader.h"
#include "../parser/lefdef/GuideReader.h"
#include "../parser/lefdef/DefDriver.h"
#include "../parser/lefdef/LefDriver.h"
#include "../parser/lefdef/RawDataBase.h"
#include "../parser/lefdef/RawDataBase2.h"
#include <iostream>
#include <vector>
#include "layer.h"
using namespace std;
using namespace DefParser;
void  CreateGrid(Layer & layer,RawDataBase &db, double starty,double startx,double stepx,double stepy);