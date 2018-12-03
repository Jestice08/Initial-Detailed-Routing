// #include <iostream>
// #include <vector>
// //#include <RawDataBase.h>
using namespace std;
#include "creategrid.h"

vector<Grid>  CreateGrid(double startx,double starty,data DieXh, double DieYh ,double stepx, double stepy)
{//vector<Grid>  CreateGrid(double startx,double starty,RawDataBase & db ,double stepx, double stepy)

  vector<Grid> grid_array;
  for(double x = startx; x <DieXh; x=x+stepx) {
    for(double y= starty; y < DieYh; y=y+stepy){
      Grid p;
      p.xcoordinate=x;
      p.ycoordinate=y;
      p.used= false;
      grid_array.push_back(p);
    }
  }
return grid_array;
}
