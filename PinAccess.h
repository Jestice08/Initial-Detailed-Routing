#ifndef _PIN_ACCESS
#define _PIN_ACCESS


#include <algorithm>
#include <vector>
#include <boost/bind.hpp>
#include <iostream>
#include "layer.h"
#include "../parser/lefdef/RawDataBase.h"
#include "../parser/lefdef/RawDataBase2.h"
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include "../parser/lefdef/DefDriver.h"
#include "../parser/lefdef/LefDriver.h"
#include "PinAccess.h"
using namespace std;
using namespace boost;
using namespace DefParser;

void APCForPin (Layer &layer2, double overlapXl, double overlapXh, double overlapYl, double overlapYh, string current_net, double layer1_start, double layer2_start, double stepx, double stepy);

void LocateArea (Layer &layer2, RawDataBase &db, MacroDataBase &macro_db, Guide &current_guide, double panel_left, double panel_right, double layer1_start, double layer2_start, double stepx, double stepy);

void PinAccess (Layer &layer1, Layer &layer2, RawDataBase &db, MacroDataBase &macro_db, double layer1_start, double layer2_start, double stepx, double stepy);

#endif