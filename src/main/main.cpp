#include <stdlib.h>
#include <iostream>
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include <string>

int main(){

  string def_file = "/home/cadmium/CAD_project/parser/src/main/ispd18_sample.input.def";
  string lef_file = "/home/cadmium/CAD_project/parser/src/main/ispd18_sample.input.lef";


  RawDataBase* db = new RawDataBase();
  MacroDataBase* macro_db = new MacroDataBase();

  readDef(def_file, *db);
  readLef(lef_file, *macro_db);

  printf("row name: %d\n",db->getRowArray()[0].step[0]);
  printf("macro name: %f\n",macro_db->siteSizeX);

}
