#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "../CAD/src/parser/lefdef/DefReader.h"
#include "../CAD/src/parser/lefdef/LefReader.h"
#include "../CAD/src/parser/lefdef/GuideReader.h"
#include "layer.h"
using namespace std;
vector <Grid> CreateGrid(double startx,double starty,RawDataBase & db,double stepx, double stepy);
int main(){
  double startx,starty,stepx,stepy;
  vector <Grid> grid_array;
  string def_file = "../benchmark/def/ispd18_sample.input.def";
  string lef_file = "../benchmark/lef/ispd18_sample.input.lef";
  string guide_file = "../benchmark/guide/ispd18_sample.input.guide";


  RawDataBase* db = new RawDataBase();
  //MacroDataBase* macro_db = new MacroDataBase();
//  GuideDataBase* gdb = new GuideDataBase();

  readDef(def_file, *db);
  //readLef(lef_file, *macro_db);
  //readGuide(guide_file, *gdb);
  grid_array=CreateGrid(startx,starty,*db, stepx, stepy);
}
