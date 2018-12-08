#include "CreateLayer.h"

std::string Generate_Tobepushed (int idx, GuideDataBase &gdb, vector <OriginalGuide> &to_be_pushed_guide)
{
  int j, originalGuideSize;
  std::string layerName = gdb.originalGuideArray[idx].layerName;
  originalGuideSize =  gdb.originalGuideArray.size();
  for (j = idx; j < originalGuideSize; ++j)
  {
    if (layerName == gdb.originalGuideArray[j].layerName)
    {
      to_be_pushed_guide.push_back(gdb.originalGuideArray[j]);
      gdb.originalGuideArray[j].pushed = true;
    }
  }
  return layerName;
}

int extractLayerFromLayerName (std::string str)
{
  	const char *s = str.c_str();
    const char *pstr;
    int i = 0, j = 0;
    pstr = &s[0];
    int layer = 0;
    int temp = 0;
    for (i = 0; *(pstr + i) != '\0'; i++)
    {
      if ((*(pstr + i) >= '0') && (*(pstr + i) <= '9'))
  			j++;
    }
    i = 0;
    pstr = &s[5];
    for (j; j>0; j--)
    {
      layer = int (*(pstr+i) - 48) + temp;
      i++;
      temp = 10*layer;
    }
    return layer;
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findGCD(vector<int> &arr)
{
    int n;
    int result = arr[0];
    n = arr.size();
    for (int i = 1; i < n; i++)
        result = gcd(arr[i], result);

    return result;
}

double findUnitWidthH (vector <OriginalGuide> &to_be_pushed_guide, vector <int > &width, double &maxRightLocation)
{
  int to_be_pushed_size = to_be_pushed_guide.size();
  vector <double> rightLocation;
  double unitWidth;

  for (int i = 0; i< to_be_pushed_size; i++)
  {
    rightLocation.push_back(to_be_pushed_guide[i].y2);
  }
  maxRightLocation = *max_element(rightLocation.begin(), rightLocation.end());

  for (int i = 0; i< to_be_pushed_size; i++)
  {
    if (to_be_pushed_guide[i].y2 != maxRightLocation)
    {
      width.push_back(int (to_be_pushed_guide[i].y2 - to_be_pushed_guide[i].y1));
    }
  }

  unitWidth = double(findGCD(width));

  return unitWidth;
}

double findUnitWidthV (vector <OriginalGuide> &to_be_pushed_guide, vector <int > &width, double &maxRightLocation)
{
  int to_be_pushed_size = to_be_pushed_guide.size();
  vector <double> rightLocation;
  double unitWidth;

  for (int i = 0; i< to_be_pushed_size; i++)
  {
    rightLocation.push_back(to_be_pushed_guide[i].x2);
  }
  maxRightLocation = *max_element(rightLocation.begin(), rightLocation.end());

  for (int i = 0; i< to_be_pushed_size; i++)
  {
    if (to_be_pushed_guide[i].x2 != maxRightLocation)
    {
      width.push_back(int (to_be_pushed_guide[i].x2 - to_be_pushed_guide[i].x1));
    }
  }

  unitWidth = double(findGCD(width));

  return unitWidth;
}

void CreatePanelH (vector <OriginalGuide> &to_be_pushed_guide, Layer &temp, double unitWidth, double &minLeftLocation, double maxRightLocation)
{
  int to_be_pushed_size = to_be_pushed_guide.size();
  vector <double> leftLocation;

  for (int i = 0; i< to_be_pushed_size; i++)
  {
    leftLocation.push_back(to_be_pushed_guide[i].y1);
  }
  minLeftLocation = *min_element(leftLocation.begin(), leftLocation.end());

  for (double nowLocation = minLeftLocation; nowLocation < maxRightLocation; nowLocation += unitWidth)
  {
    Panel paneltemp = Panel();
    paneltemp.left = nowLocation;
    paneltemp.right = min(nowLocation + unitWidth, maxRightLocation);
    temp.panelArray.push_back(paneltemp);
  }
}

void CreatePanelV (vector <OriginalGuide> &to_be_pushed_guide, Layer &temp, double unitWidth, double &minLeftLocation, double maxRightLocation)
{
  int to_be_pushed_size = to_be_pushed_guide.size();
  vector <double> leftLocation;

  for (int i = 0; i< to_be_pushed_size; i++)
  {
    leftLocation.push_back(to_be_pushed_guide[i].x1);
  }
  minLeftLocation = *min_element(leftLocation.begin(), leftLocation.end());

  for (double nowLocation = minLeftLocation; nowLocation < maxRightLocation; nowLocation += unitWidth)
  {
    Panel paneltemp = Panel();
    paneltemp.left = nowLocation;
    paneltemp.right = min(nowLocation + unitWidth, maxRightLocation);
    temp.panelArray.push_back(paneltemp);
  }
}

void PushGuideIntoPanelH (vector <OriginalGuide> &to_be_pushed_guide, Layer &layer, double unitWidth, double minLeftLocation)
{
  int to_be_pushed_size = to_be_pushed_guide.size();
  int index;
  for ( index = 0; index < to_be_pushed_size; index++ )
  {
    double guide_width;
    double guide_left, guide_right, guide_bottom, guide_top;
    guide_left = to_be_pushed_guide[index].y1;
    guide_right = to_be_pushed_guide[index].y2;
    guide_bottom = to_be_pushed_guide[index].x1;
    guide_top = to_be_pushed_guide[index].x2;
    guide_width = guide_right - guide_left;
    int panel_index;
    int current_guideArray_size;
    int push_flag = 0;

    while(guide_width > unitWidth)                                                //seperate guide
    {
      Guide guide_temp = Guide();
      guide_temp.top = guide_top;
      guide_temp.bottom = guide_bottom;
      guide_temp.net.push_back(to_be_pushed_guide[index].netName);
      panel_index = int ((guide_left- minLeftLocation)/unitWidth);
      current_guideArray_size = layer.panelArray[panel_index].guideArray.size();

      for (int i = 0; i< current_guideArray_size; i++)                          //add new net to a existing guide
      {
        if(layer.panelArray[panel_index].guideArray[i].bottom == guide_bottom)
        {
          if(layer.panelArray[panel_index].guideArray[i].top == guide_top)
          {
            layer.panelArray[panel_index].guideArray[i].net.push_back(to_be_pushed_guide[index].netName);
            push_flag = 1;
            break;
          }
        }
      }

      if (push_flag == 0) layer.panelArray[panel_index].guideArray.push_back(guide_temp);        
      guide_left += unitWidth;
      guide_width = guide_right - guide_left;
      push_flag = 0;
    }

    Guide guide_temp = Guide();
    guide_temp.top = guide_top;
    guide_temp.bottom = guide_bottom;
    guide_temp.net.push_back(to_be_pushed_guide[index].netName);
    panel_index = int ((guide_left- minLeftLocation)/unitWidth);
    current_guideArray_size = layer.panelArray[panel_index].guideArray.size();

    for (int i = 0; i< current_guideArray_size; i++)                          //add new net to a existing guide
    {
      if(layer.panelArray[panel_index].guideArray[i].bottom == guide_bottom)
      {
        if(layer.panelArray[panel_index].guideArray[i].top == guide_top)
        {
          layer.panelArray[panel_index].guideArray[i].net.push_back(to_be_pushed_guide[index].netName);
          push_flag = 1;
          break;
        }
      }
    }

    if (push_flag == 0) layer.panelArray[panel_index].guideArray.push_back(guide_temp);        
    push_flag = 0;
  }
}

void PushGuideIntoPanelV (vector <OriginalGuide> &to_be_pushed_guide, Layer &layer, double unitWidth, double minLeftLocation)
{
  int to_be_pushed_size = to_be_pushed_guide.size();
  int index;
  for ( index = 0; index < to_be_pushed_size; index++ )
  {
    double guide_width;
    double guide_left, guide_right, guide_bottom, guide_top;
    guide_left = to_be_pushed_guide[index].x1;
    guide_right = to_be_pushed_guide[index].x2;
    guide_bottom = to_be_pushed_guide[index].y1;
    guide_top = to_be_pushed_guide[index].y2;
    guide_width = guide_right - guide_left;
    int panel_index;
    int current_guideArray_size;
    int push_flag = 0;

    while(guide_width > unitWidth)                                                //seperate guide
    {
      Guide guide_temp = Guide();
      guide_temp.top = guide_top;
      guide_temp.bottom = guide_bottom;
      guide_temp.net.push_back(to_be_pushed_guide[index].netName);
      panel_index = int ((guide_left- minLeftLocation)/unitWidth);
      current_guideArray_size = layer.panelArray[panel_index].guideArray.size();

      for (int i = 0; i< current_guideArray_size; i++)                          //add new net to a existing guide
      {
        if(layer.panelArray[panel_index].guideArray[i].bottom == guide_bottom)
        {
          if(layer.panelArray[panel_index].guideArray[i].top == guide_top)
          {
            layer.panelArray[panel_index].guideArray[i].net.push_back(to_be_pushed_guide[index].netName);
            push_flag = 1;
            break;
          }
        }
      }

      if (push_flag == 0) layer.panelArray[panel_index].guideArray.push_back(guide_temp);        
      guide_left += unitWidth;
      guide_width = guide_right - guide_left;
      push_flag = 0;
    }

    Guide guide_temp = Guide();
    guide_temp.top = guide_top;
    guide_temp.bottom = guide_bottom;
    guide_temp.net.push_back(to_be_pushed_guide[index].netName);
    panel_index = int ((guide_left- minLeftLocation)/unitWidth);
    current_guideArray_size = layer.panelArray[panel_index].guideArray.size();

    for (int i = 0; i< current_guideArray_size; i++)                          //add new net to a existing guide
    {
      if(layer.panelArray[panel_index].guideArray[i].bottom == guide_bottom)
      {
        if(layer.panelArray[panel_index].guideArray[i].top == guide_top)
        {
          layer.panelArray[panel_index].guideArray[i].net.push_back(to_be_pushed_guide[index].netName);
          push_flag = 1;
          break;
        }
      }
    }

    if (push_flag == 0) layer.panelArray[panel_index].guideArray.push_back(guide_temp);        
    push_flag = 0;
  }
}

bool less_bottom(const Guide & m1,const Guide & m2) 
{
        return m1.bottom < m2.bottom;
}

void CreateLayer (GuideDataBase &gdb, vector <Layer> &layerarray)
{
  int idx, originalGuideSize;
  originalGuideSize =  gdb.originalGuideArray.size();

  for ( idx = 0; idx < originalGuideSize; ++idx)
  {
    if (gdb.originalGuideArray[idx].pushed == false)
    {
      std::string layerName;
      vector <OriginalGuide> to_be_pushed_guide;
      int layer;
      bool horizontalDirection;
      Layer temp = Layer();

      layerName = Generate_Tobepushed(idx, gdb, to_be_pushed_guide);
      temp.layerName = layerName;
      layer = extractLayerFromLayerName (layerName);
      horizontalDirection = (layer % 2) ? true : false;

      if (horizontalDirection)
      {
        double unitWidth;
        vector <int> width;
        double minLeftLocation;
        double maxRightLocation;
        unitWidth = findUnitWidthH (to_be_pushed_guide, width, maxRightLocation);
        temp.unitWidth = unitWidth;
        CreatePanelH (to_be_pushed_guide, temp, unitWidth, minLeftLocation, maxRightLocation);
        PushGuideIntoPanelH (to_be_pushed_guide, temp, unitWidth, minLeftLocation);
        layerarray.push_back(temp);
        //report panel
        /*
        cout << "Benchmark: Test1" << endl;
        cout << "In " << layerName << ":" << endl;
        cout << "Unit Width is: " << unitWidth << endl;
        cout << "Panel number:" << temp.panelArray.size() << endl;
        int sizeee;
        sizeee = temp.panelArray.size();
        for (int index =0; index < sizeee; index++)
        {
          if ((index <=9)||(index>=65))
          {
          cout << "Panel " << index << " " << "Left location: " << temp.panelArray[index].left << "  ";
          cout << "Right location: " << temp.panelArray[index].right << endl;
          }
        }
        */
      }
      else
      {
        double unitWidth;
        vector <int> width;
        double minLeftLocation;
        double maxRightLocation;
        unitWidth = findUnitWidthV (to_be_pushed_guide, width, maxRightLocation);
        temp.unitWidth = unitWidth;
        CreatePanelV (to_be_pushed_guide, temp, unitWidth, minLeftLocation, maxRightLocation);
        PushGuideIntoPanelV (to_be_pushed_guide, temp, unitWidth, minLeftLocation);
        layerarray.push_back(temp);
      }
    }
  }

  //sort guides in each panel
  int layer_size = layerarray.size();
  for (int layerindex = 0; layerindex < layer_size; layerindex++)
  {
    int panel_size = layerarray[layerindex].panelArray.size();
    for (int panelindex = 0; panelindex < panel_size; panelindex++)
    {
      stable_sort(layerarray[layerindex].panelArray[panelindex].guideArray.begin(),layerarray[layerindex].panelArray[panelindex].guideArray.end(), less_bottom);
      //sort(layerarray[layerindex].panelArray[panelindex].guideArray.begin(),layerarray[layerindex].panelArray[panelindex].guideArray.end(), less_bottom);
    }
  }

}
