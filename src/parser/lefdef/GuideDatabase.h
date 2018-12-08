#include <vector>
#include <string>
#include <iostream>
using namespace std;

class OriginalGuide
{
public:
  double x1,x2,y1,y2;
  std::string layerName;
  std::string netName;
  bool pushed;
};

class GuideDataBase
{
public:
  vector<OriginalGuide> originalGuideArray;

  void setOriginalGuide(OriginalGuide &guide){
    originalGuideArray.push_back(guide);
  }

  vector<OriginalGuide> getOriginalGuide() {
    return originalGuideArray;
  }
};
