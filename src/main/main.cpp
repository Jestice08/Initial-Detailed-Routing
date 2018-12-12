#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include "../parser/lefdef/GuideReader.h"
// #include "../parser/lefdef/DefDriver.h"
// #include "../parser/lefdef/LefDriver.h"
#include "../impl/layer.h"
#include "../parser/lefdef/RawDataBase.h"
#include "../parser/lefdef/RawDataBase2.h"
#include "../impl/CreateLayer.h"
#include "../impl/overlap.h"
#include "../impl/creategrid.h"
using namespace std;
using namespace DefParser;

int main(){
  int layeridx =0;
  double startx=83800;
  double starty=72010;
  double stepx=400;
  double stepy=380;

  vector<APC> Apc_Array;
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

  vector <Layer> layerArray;
  CreateLayer (*gdb, layerArray);
  
  //CreateGrid (layerArray[0],*db,starty,startx,stepx,stepy);
  // cout << "layer1 grid size=" << layerArray[0].congestionGridArray.size() << endl;
  // cout << "layer1 xnumber =" <<layerArray[0].xsize << endl;
  // cout << "layer1 ynumber =" <<layerArray[0].ysize << endl;
  //layer1 panel1 testbench
  // int layersize = layerArray.size();
  // cout << "Layer number: " << layersize << endl;
  // int guidesize = layerArray[0].panelArray[3].guideArray.size();
  // double unitwidth_upperlayer= layerArray[1].unitWidth;
  // for(int xxx=0; xxx< layerArray[1].panelArray[0].guideArray[0].net.size(); xxx=xxx+1){
  //   cout<< "layer2 panel0 guide0 net=" << layerArray[1].panelArray[0].guideArray[0].net[xxx] << endl;
  // }
  // cout << "Layer1 Panel3 guide number is :" << layerArray[0].panelArray[3].guideArray.size()<< endl;
  // for (int ff=0; ff< layerArray[1].panelArray[0].guideArray.size();ff=ff+1){
  //   cout <<"layer2 panel0 guide number=" <<  ff <<" --layer2 panel0 guide top=" << layerArray[1].panelArray[0].guideArray[ff].top << "--layer2 panel0 guide bottom=" << layerArray[1].panelArray[0].guideArray[ff].bottom << endl;
  // }

  
  cout << "metal layer2 panel1 guide number: "<< layerArray[1].panelArray[0].guideArray.size()<< endl;
  for (int jj=0; jj<layerArray[1].panelArray[0].guideArray[0].net.size(); jj++){
    cout << "metal layer2 panel1 guide0 net=" << layerArray[1].panelArray[0].guideArray[0].net[jj] <<endl;
  }

  for (int pp=0; pp<layerArray[1].panelArray[0].guideArray[1].net.size(); pp++){
    cout << "metal layer2 panel1 guide1 net=" << layerArray[1].panelArray[0].guideArray[1].net[pp] <<endl;
  }

  for (int cc=0; cc<layerArray[1].panelArray[0].guideArray[2].net.size(); cc++){
    cout << "metal layer2 panel1 guide2 net=" << layerArray[1].panelArray[0].guideArray[2].net[cc] <<endl;
  }

  for (int gg=0; gg<layerArray[1].panelArray[0].guideArray[3].net.size(); gg++){
    cout << "metal layer2 panel1 guide3 net=" << layerArray[1].panelArray[0].guideArray[3].net[gg] <<endl;
  }
  // cout << "Layer2 panel unit width is :" << unitwidth_upperlayer<< endl;
  
  // cout << "layer1 panel0 guide3 netsize=" << layerArray[0].panelArray[0].guideArray[3].net.size()<< endl;
  // cout << "layer2 panel2 guidesize=" << layerArray[1].panelArray[2].guideArray.size()<< endl;

  // for(int mm=0;mm<layerArray[0].panelArray[0].guideArray[4].net.size();mm++){
  //   cout << "layer1 panel0 guide4 net=" << layerArray[0].panelArray[0].guideArray[4].net[mm] <<endl;
  // }


  // for(int aa=0; aa<layerArray[1].panelArray[2].guideArray[0].net.size();aa++){
  //   cout << "layer2 panel2 guide 0 net=" << layerArray[1].panelArray[2].guideArray[0].net[aa] << endl;
  // }

  // for(int bb=0; bb<layerArray[1].panelArray[2].guideArray[1].net.size();bb++){
  //   cout << "layer2 panel2 guide 1 net=" << layerArray[1].panelArray[2].guideArray[1].net[bb] << endl;
  // }

  // cout << "Layer2 panel1 guide0 top: " << layerArray[1].panelArray[1].guideArray[0].top<< endl;
  // cout << "Layer2 panel1 guide0 bottom :" << layerArray[1].panelArray[1].guideArray[0].bottom<<endl;
  // cout << "layer2panel1guide1top :" << layerArray[1].panelArray[1].guideArray[1].top<<endl;
  // cout << "layer2panel1guide1bottom :" << layerArray[1].panelArray[1].guideArray[1].bottom<<endl;
  // int netsize = layerArray[0].panelArray[0].guideArray[0].net.size();
  Apc_Array=overlap (layerArray[0],layerArray[1],layerArray[0].panelArray[0],layeridx); //overlap test
  // //layer1 panel1 test

  // int apcsize = Apc_Array.size();
  // cout << "APC size is :"<< apcsize << endl;
  // cout << "Apc_Array[0].net is:" << Apc_Array[0].net << endl;

  return 0;
}
