#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Pin
{
public:
  string name;
  double pinX1,pinY1,pinXh,pinYh;
};


class StdCell
{
public:
  std::string macroName;
  double sizeX;
  double sizeY;

  int leftEdge;
  int rightEdge;

  vector<Pin> pinArray;

  void setSizeX(double size){
    sizeX = size;
  }

  void setSizeY(double size){
    sizeY = size;
  }

  void setEdgeLeft(int edge){
    leftEdge = edge;
  }

  void setEdgeRight(int edge){
    rightEdge = edge;
  }

  void setBottomVss(bool vss){
    Pin *p = new Pin();
    if (vss) {
      p->name = "vss";
      pinArray.push_back(*p);
    } else {
      p->name = "vdd";
      pinArray.push_back(*p);
    }

  }

  void setMacroName(std::string name){
    macroName = name;
  }

  void addPin(double x1, double y1, double xh, double yh, std::string name){
    Pin *p = new Pin();
    p->pinX1 = x1;
    p->pinY1 = y1;
    p->pinXh = xh;
    p->pinYh = yh;
    p->name = name;
    pinArray.push_back(*p);
  }

};

class Unit
{
public:
  bool haspower;
  bool hasDatabase;
  bool hasCapacitance;
  double power;
  double capacitance;
  std::string databaseName;
  double databaseNumber;
};

class EolSpacing
{
public:
  double spacing;
  double spacingEolWidth;
  double spacingEolWithin;
};

class SpacingTable
{
public:
  vector<double> spacingTableParallelRunLength;
  vector<double> spacingTableWidth;
  vector<double> spacingTableSpacing;
};

class LefLayerCut
{
public:
    std::string name;
    double width;
    double spacing;
};

class LefLayerRouting
{
public:
    std::string name;
    bool hasPitch;
    bool hasXYPitch;
    bool hasWidth;
    bool hasArea;
    bool hasSpacingNumber;
    bool hasDirection;
    bool hasMinWidth;
    bool hasMaxWidth;
    double pitch;
    double pitchX;
    double pitchY;
    double width;
    double area;
    std::int32_t numSpacing;
    std::string direction;
    double minWidth;
    double maxWidth;
    int numSpacingTable;
    vector<EolSpacing> eolSpacingArray;
    vector<double> spacing;
    vector<SpacingTable> spacingTableArray; //Should I write the add function to call it or just directly call it?

    vector<EolSpacing> addEolSpacingArray(){
      return eolSpacingArray;
    }

    vector<double> addSpacingArray(){
      return spacing;
    }
};

class LefLayerOverlap
{
public:
    std::string name;
};

class cutLayerRect
{
public:
  double rect[4];
};

class LefRawFixedVia
{
public:
  std::string name;
  std::string bottomLayer;
  std::string cutLayer;
  std::string topLayer;
  bool isDefault;
  bool hasResistance;
  double resistance;
  double bottomLayerRect[4];
  std::uint32_t numCutRect;
  vector<cutLayerRect> cutLayerRectArray; //cutLayerRect should be a 4 double array
  double topLayerRect[4];
};

class MacroDataBase
{
public:
//LEF code
  double siteSizeX;
  double siteSizeY;

  string busBitChars;
  string clearanceMeasure;
  string divideChar;
  string version;
  double manufacturingGrid;

  vector<Unit> unitArray;
  vector<StdCell> stdCellArray;
  vector<LefLayerCut> cutLayersArray;
  vector<LefLayerRouting> routingLayersArray;
  vector<LefLayerOverlap> overlapLayersArray;
  vector<LefRawFixedVia> fixedViaArray;

  void setLefSiteSizeX(double sizeX){
    siteSizeX = sizeX;
  }

  void setLefSiteSizeY(double sizeY){
    siteSizeY = sizeY;
  }

  void addStdCellLib(StdCell stdCell){
    stdCellArray.push_back(stdCell);
  }

  StdCell getStdCellLib(std::string name){
    for (int i = 0; i < stdCellArray.size(); ++i){
      if (name.compare(stdCellArray[i].macroName) == 0){
        return stdCellArray[i];
      }
    }
  }

  void setVersion(const std::string &v){
    version = v;
  }

  void setDivideChar(const std::string &v){
    divideChar = v;
  }

  void setManufacturingGrid(double v){
    manufacturingGrid = v;
  }

  void setClearanceMeasure(const std::string &v){
    clearanceMeasure = v;
  }

  void addUnitArray(Unit &unit){
    unitArray.push_back(unit);
  }

  vector<Unit>  getUnitArray(){
    return unitArray;
  }

  void setBusBitChars(const std::string &v){
    busBitChars = v;
  }

  vector<LefLayerCut> cutLayers() {
    return cutLayersArray;
  }

  vector<LefLayerRouting> routingLayers() {
    return routingLayersArray;
  }

  vector<LefLayerOverlap> overlapLayers() {
    return overlapLayersArray;
  }

  vector<LefRawFixedVia> fixedVias() {
    return fixedViaArray;
  }
};
