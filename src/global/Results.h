#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Point
{
public:
  double xCoordinate;
  double yCoordinate;
};

class ViaResult
{
public:
  string viaType;
  string net;
  Point location;
};

class SegmentResult
{
public:
  string layerName;
  string net;
  vector <Point> pointArray;
  vector <Point> terminalArray; //stores points for promotion
};

vector <ViaResult> viaResultArray;
vector <SegmentResult> segmentResultArray;
