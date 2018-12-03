#include<vector>
#include<string>
#include<algorithm>
#include "createapcs.h"
using namespace std;
vector<AP>  CreateApcs(Guide &guideLow, Guide &guideHigh,Panel &panelLow, Panel& panelHigh, int layerindex){
  vector <AP> accesspoints_array;
    double x1,x2,y1,y2,startx,starty,stepx,stepy,xstart,ystart;
  if(layerindex%2==0){
    x1 = max(guideLow.bottom,panelHigh.left);
    y1 = max(panelLow.left,guideHigh.bottom);
    x2 = min(guideLow.top,panelHigh.right);
    y2 = min(panelLow.right,guideHigh.top);
  }// define corner coordinates of a apc
  else{
     x1 = max(panelLow.left,guideHigh.bottom);
     y1 = max(guideLow.bottom,panelHigh.left);
     x2 = min(panelLow.right, guideHigh.top);
     y2 = min(guideLow.top,panelHigh.right);
  }
  if(((int)(x1-startx)%(int)(stepx))==0){
    xstart=x1;
  }
  else{
    xstart=startx+((x1-startx)/stepx+1)*stepx;
  }
  if(((int)(y1-starty)%(int)(stepy))==0){
    ystart=y1;
  }
  else{
    ystart=starty+((y1-starty)/stepy+1)*stepy;
  }
  for(double i = xstart; i<x2; i=i+stepx){
    for(double j = ystart; j<y2; j=j+stepy){
      AP ap=AP ();
      ap.xCoordinate=i;
      ap.yCoordinate=j;
      accesspoints_array.push_back(ap);
    }
  }
  return accesspoints_array;
}
