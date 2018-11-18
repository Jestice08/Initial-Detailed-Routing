#include <vector>
#include <string>
#include <iostream>
using namespace std;

class AP
{
public:
  double xCoordinate;
  double yCoordinate;
};

class APC
{
public:
  bool promote;
  bool connect;
  double apcLeft, apcRight, apcTop, apcDown;
  std::string lowerLayer;
  std::string upperLayer;
  vector <AP> aps;
  std::string net;
};

class Guide
{
public:
  double top;
  double bottom;
  vector <std::string> net;
};

class Grid
{
public:
  double xcoordinate;
  double ycoordinate;
  bool used;
};

class Panel
{
public:
    vector <Guide> guideArray;
    vector <APC>  apcArray;
    double left;
    double right;

    void addGuideArray(Guide guide)
    {
      guideArray.push_back(guide);
    }

    void addPanelArray(APC apc)
    {
      apcArray.push_back(apc);
    }
};

class Layer
{
public:
  vector <Panel> panelArray;
  std::string layerName;
  double unitWidth;
  vector <Grid> congestionGridarray;
  void addPanelArray(Panel panel)
  {
    panelArray.push_back(panel);
  }
};
