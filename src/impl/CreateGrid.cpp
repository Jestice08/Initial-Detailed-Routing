#include <iostream>
#include <vector>
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include "../parser/lefdef/GuideReader.h"
#include "../parser/lefdef/DefDriver.h"
#include "../parser/lefdef/LefDriver.h"
#include "../parser/lefdef/RawDataBase.h"
#include "../parser/lefdef/RawDataBase2.h"
#include "layer.h"
#include "creategrid.h"
using namespace std;
using namespace DefParser;

void  CreateGrid(Layer & layer,RawDataBase &db, double starty,double startx,double stepx,double stepy)
{//vector<Grid>  CreateGrid(double startx,double starty,RawDataBase & db ,double stepx, double stepy) //startx: track starting point;DieXh: die area size;stepx:track step specified in .def file
  int xnumber=0;
  int ynumber=0;
  double y;
  double x;
  for(y = starty; y <db. DieYh; y=y+stepy){
    for(x= startx; x <db. DieXh; x=x+stepx){
      Grid p; 
      p.xcoordinate=x;
      p.ycoordinate=y;
      p.used= 0;
      layer.congestionGridArray.push_back(p);
    }
  }
  xnumber = (x-startx)/stepx;
  ynumber = (y-starty)/stepy;
  layer.xsize=xnumber;
  layer.ysize=ynumber;
}
