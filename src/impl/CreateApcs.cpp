#include<vector>
#include<string>
#include<algorithm>
#include "createapcs.h"
using namespace std;
vector<AP>  CreateApcs(Guide &guideLow, Guide &guideHigh,Panel &panelLow, Panel& panelHigh, int layerindex){//layerindex is lower layer index
  vector <AP> accesspoints_array;      // for sample,stepx=400;stepy=380;startx=83800;starty=72010
    double x1,x2,y1,y2;
    double stepx=400.0;
    double stepy=380.0;
    double startx=83800.0;
    double starty=72010.0;
    double xstart,ystart;  //startx is defined in .def to specify starting x coordinate 
    cout << "layerindex: " << layerindex<<endl;
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
  cout << "x1="<< x1 <<endl;
  cout << "x2="<< x2 <<endl;
  cout << "y1="<< y1 <<endl;
  cout << "y2="<< y2 <<endl;
  if (x1<=startx){
    xstart=startx;
  }
  else if(((int)(x1-startx)%(int)(stepx))==0){ // if corner coordinate align with track, apc starts from xstart=x1
    xstart=x1;
  }
  else{
    xstart=startx+(int)((x1-startx)/stepx+1)*stepx;  //replace stepx to 380
    cout << "xstart=" << xstart << endl;
    cout << "(x1-startx)/stepx=" << (int) ((x1-startx)/stepx) << endl;
  }
  
  if(y1<=starty){
    ystart=starty;
  }
  else if(((int)(y1-starty)%(int)(stepy))==0){
    ystart=y1;
  }
  else{
    ystart=starty+(int)((y1-starty)/stepy+1)*stepy;
  }
  cout << "ystart=" << ystart << endl;
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
