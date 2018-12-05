#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include "../parser/lefdef/GuideReader.h"


int main(){

  string def_file = "../benchmark/def/ispd18_sample.input.def";
  string lef_file = "../benchmark/lef/ispd18_sample.input.lef";
  string guide_file = "../benchmark/guide/ispd18_sample.input.guide";


  RawDataBase* db = new RawDataBase();
  MacroDataBase* macro_db = new MacroDataBase();
  GuideDataBase* gdb = new GuideDataBase();

  readDef(def_file, *db);
  readLef(lef_file, *macro_db);
  readGuide(guide_file, *gdb);

//  CreateLayer

  //Route(*db,*macro_db, *gdb);

  //printf("row name: %d\n",db->getRowArray()[0].step[0]); //test
  //printf("macro name: %f\n",macro_db->siteSizeX); //test

  //test
  /*
  int guidesize = gdb->getOriginalGuide().size();
  for (int i = 0; i < guidesize; ++i)
  {
    cout << gdb->getOriginalGuide()[i].netName << endl;
    cout << gdb->getOriginalGuide()[i].layerName << endl;
    cout << "x1 = " << gdb->getOriginalGuide()[i].x1 << " y1 = " << gdb->getOriginalGuide()[i].y1 << endl;
    cout << "x2 = " << gdb->getOriginalGuide()[i].x2 << " y2 = " << gdb->getOriginalGuide()[i].y2 << endl;
    cout << endl;
  }*/

}
