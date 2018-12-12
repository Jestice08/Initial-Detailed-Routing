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
<<<<<<< HEAD
#include "../impl/overlap.h"
#include "../impl/creategrid.h"
using namespace std;
using namespace DefParser;
=======
#include "../impl/PinAccess.h"
#include "../impl/Results.h"
#include "../impl/Route.h"

>>>>>>> yizheng

int main(){
  int layeridx =0;
  double startx=83800;
  double starty=72010;
  double stepx=400;
  double stepy=380;

<<<<<<< HEAD
  vector<APC> Apc_Array;
  string def_file = "../benchmark/def/ispd18_sample.input.def";
  string lef_file = "../benchmark/lef/ispd18_sample.input.lef";
  string guide_file = "../benchmark/guide/ispd18_sample.input.guide";
=======
  string def_file = "../benchmark/def/ispd18_sample.input.def";
  string lef_file = "../benchmark/lef/ispd18_sample.input.lef";
  string guide_file = "../benchmark/guide/ispd18_sample.input.guide";

>>>>>>> yizheng

  RawDataBase* db = new RawDataBase();
  MacroDataBase* macro_db = new MacroDataBase();
  GuideDataBase* gdb = new GuideDataBase();

  readDef(def_file, *db);
  readLef(lef_file, *macro_db);
  readGuide(guide_file, *gdb);

   vector <Layer> layerArray;
  CreateLayer (*gdb, layerArray);


  double layer1_start, layer2_start, stepxx, stepyy;
  layer1_start = 72010;
  layer2_start = 83800;
  stepyy = 380;
  stepxx = 400;

  PinAccess (layerArray[0], layerArray[1], *db, *macro_db, layer1_start, layer2_start, stepxx, stepyy);

  vector <SegmentResult> SegmentArray;
  vector <ViaResult> ViaArray;

  Route (layerArray, SegmentArray, ViaArray, *db, *macro_db, layer1_start, layer2_start, stepxx, stepyy);

  cout << "FINISH" << endl;

  // //segment test
  int segment_size;
  int segment_idx;
  segment_size = SegmentArray.size();
  cout << "seg size:" << segment_size << endl;
  for (segment_idx = 0; segment_idx < segment_size; segment_idx++)
  {
    cout << "this segment layer: " << SegmentArray[segment_idx].layerName << "  this segment net: " << SegmentArray[segment_idx].net << endl;
    cout << "this segment point number: " << SegmentArray[segment_idx].pointArray.size() << endl;
    if (SegmentArray[segment_idx].pointArray.size() > 0)
    {
      for (int point_idx = 0; point_idx < SegmentArray[segment_idx].pointArray.size(); point_idx++)
      {
        //cout << "this segment first point x= " << SegmentArray[segment_idx].pointArray[0].xCoordinate << "  y= " << SegmentArray[segment_idx].pointArray[0].yCoordinate << endl;
        cout << "point index: " << point_idx <<  " x= " << SegmentArray[segment_idx].pointArray[point_idx].xCoordinate << "  y= " << SegmentArray[segment_idx].pointArray[point_idx].yCoordinate << endl;
  
      }
    }
    //cout << "this segment first point x= " << SegmentArray[segment_idx].pointArray[0].xCoordinate << "  y= " << SegmentArray[segment_idx].pointArray[0].yCoordinate << endl;
    //cout << "this segment last point x= " << SegmentArray[segment_idx].pointArray[SegmentArray[segment_idx].pointArray.size()-1].xCoordinate << "  y= " << SegmentArray[segment_idx].pointArray[SegmentArray[segment_idx].pointArray.size()-1].yCoordinate << endl;
  }

  int via_size;
  int via_idx;
  via_size = ViaArray.size();
  cout << via_size << endl;
  for(via_idx = 0; via_idx < via_size ; via_idx++)
  {
    cout << "via index: " << via_idx;
    cout << " via type: " << ViaArray[via_idx].viaType;
    cout << " via net : " <<  ViaArray[via_idx].net;
    cout << " x: " << ViaArray[via_idx].location.xCoordinate << " y: " << ViaArray[via_idx].location.yCoordinate << endl;
  }

  for ( int i = 1; i < 3 ; i++)
  {
    int panelindex;
    for ( panelindex = 0;  panelindex < layerArray[i].panelArray.size() ; panelindex++)
    {
      for ( int apcindex = 0; apcindex < layerArray[i].panelArray[panelindex].apcArray.size(); apcindex++)
      {
        if(layerArray[i].panelArray[panelindex].apcArray[apcindex].net == "net1233")
        {
          cout << "now in layer" << i+1 << " in panel " << panelindex << endl;
          cout << "connect status: " << layerArray[i].panelArray[panelindex].apcArray[apcindex].connect << endl;
          cout << "promote status: " << layerArray[i].panelArray[panelindex].apcArray[apcindex].promote << endl;
          cout << "point number: " << layerArray[i].panelArray[panelindex].apcArray[apcindex].aps.size() << endl;
          if (layerArray[i].panelArray[panelindex].apcArray[apcindex].aps.size()!=0)
          {
            for (int apsindex = 0; apsindex < layerArray[i].panelArray[panelindex].apcArray[apcindex].aps.size(); apsindex++)
            {
              cout << "x= " << layerArray[i].panelArray[panelindex].apcArray[apcindex].aps[apsindex].xCoordinate << " y= " << layerArray[i].panelArray[panelindex].apcArray[apcindex].aps[apsindex].yCoordinate << endl;
            }
          }
        }
      }
    }
  }

  // int layer3panelsize;
  // layer3panelsize = layerArray[2].panelArray.size();
  // for (int i = 0; i < layer3panelsize; i++)
  // {
  //   cout << "current panel: " << i << endl;
  //   cout << "current panel apc num: " << layerArray[2].panelArray[i].apcArray.size() <<endl;
  //   int apcsizeee = layerArray[2].panelArray[i].apcArray.size();
  //   for (int j = 0 ; j < apcsizeee ; j++)
  //   {
  //     cout << "current apc: " << j << " connect status: " << layerArray[2].panelArray[i].apcArray[j].connect << " promote status: " << layerArray[2].panelArray[i].apcArray[j].promote << endl;
  //   }
  // }

  // int stdcell_size = macro_db->stdCellArray.size();
  // cout << "stdcell number:" << stdcell_size << endl;
  // for (int i =0 ; i < stdcell_size ; i++)
  // cout << "pin number:" << macro_db->stdCellArray[i].pinArray.size() << endl;

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

<<<<<<< HEAD
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
=======

  //layer1 panel1 testbench
  // int layersize = layerArray.size();
  // cout << "Layer number: " << layersize << endl;
  // int panelsize = layerArray[0].panelArray.size();
  // for (int k = 0; k < panelsize ; k++)
  // {
  // int guidesize = layerArray[0].panelArray[k].guideArray.size();
  // cout << "Layer1 Panel " << k <<  " guide number is :" << guidesize << endl;
  // for (int i = 0; i<guidesize; i++)
  // {
  //  cout << "Guide bottom location:" << layerArray[0].panelArray[k].guideArray[i].bottom << endl; 
  //  cout << "Guide top location:" << layerArray[0].panelArray[k].guideArray[i].top << endl; 
  //  int netsize = layerArray[0].panelArray[k].guideArray[i].net.size();
  //  cout << " Has net:";
  //  for (int j = 0; j<netsize; j++)
  //  {
  //   cout << layerArray[0].panelArray[k].guideArray[i].net[j] << " ";
  //  }
  //  cout << endl;
  // }
  // }
  //track test
    //cout << db->netArray.size() << endl;
   // cout << db->trackArray.size() << endl;
  // cout << db->trackArray[0].x << endl;
  // cout << db->trackArray[0].xNum << endl;
  // cout << db->trackArray[0].xStep << endl;
  // cout << db->trackArray[0].macro_name << endl;

  //pin access test
  // int layer2_panel_size;
  // layer2_panel_size = layerArray[1].panelArray.size();
  // for (int i = 0; i < layer2_panel_size; i++)
  // {
  //   cout << "Now at panel" << i << ":" << endl;
  //   int apc_size = layerArray[1].panelArray[i].apcArray.size();
  //   cout << "APC number is:" << apc_size << endl;
  //   for (int m = 0; m < apc_size; m++)
  //   {
  //     cout << "net = " << layerArray[1].panelArray[i].apcArray[m].net;
  //     cout << " x = " << layerArray[1].panelArray[i].apcArray[m].aps[0].xCoordinate;
  //     cout << " y = " << layerArray[1].panelArray[i].apcArray[m].aps[0].yCoordinate << endl;
  //   }
  // }
>>>>>>> yizheng

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
