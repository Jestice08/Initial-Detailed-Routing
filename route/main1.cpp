#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
// #include "lefdef/DefReader.h"
// #include "lefdef/LefReader.h"
// #include "lefdef/GuideReader.h"

#include "overlap.h"
int main(){
  double a,b,c,d,diex,diey;
  a=0;
  b=0;
  c=0;
  d=0;
  diex=0;
  diey=0;
  int layeridx=0;
  Guide guideLow= Guide();
  Guide guideHigh=Guide();
  Panel panelLow=Panel();
  Panel panelHigh=Panel();
  Layer layer1=Layer();
  Layer layer2=Layer();
  Panel panel=Panel();
  int  layerindex=0;
  string def_file = "../benchmark/def/ispd18_sample.input.def";
  string lef_file = "../benchmark/lef/ispd18_sample.input.lef";
  string guide_file = "../benchmark/guide/ispd18_sample.input.guide";


//  RawDataBase* db = new RawDataBase();
//  MacroDataBase* macro_db = new MacroDataBase();
  //GuideDataBase* gdb = new GuideDataBase();

//  readDef(def_file, *db);
/*  readLef(lef_file, *macro_db);
  readGuide(guide_file, *gdb);*/

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
//CreateGrid(a,b,diex,diey,c,d);
//CreateApcs(guideLow, guideHigh, panelLow, panelHigh,  layerindex);
overlap(layer1,layer2,panel,layeridx);
}
