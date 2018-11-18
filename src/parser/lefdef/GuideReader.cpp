#include <stdlib.h>
#include <iostream>
#include "GuideReader.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

void readGuide(std::string const &fileName, GuideDataBase &gdb)
{
  cout << "Reading Guide File ..." << endl;
  vector <buffer> bufferArray;
  int numLine;
  int idx, j;
  //GuideDataBase* gdb = new GuideDataBase();

  fstream outFile;
  outFile.open(fileName.c_str(),ios::in);
  while(!outFile.eof())
  {
    buffer temp = buffer();
    outFile.getline(temp.line,256,'\n');
    bufferArray.push_back(temp);
  }
  outFile.close();
  numLine = bufferArray.size();

  std::string netName;
  std::string layerName;

  for (idx = 0; idx < numLine; idx++)
  {

    //update netname
    if (bufferArray[idx].line[0] == 'n')
    {
      netName = bufferArray[idx].line;
    }

    else if ( (bufferArray[idx].line[0]>='0') && (bufferArray[idx].line[0]<='9') )
    {
      OriginalGuide temp2 = OriginalGuide();
      temp2.netName = netName;
      vector <char> separate;
      vector <double> location;
      separate.clear();
      location.clear();
      for (j=0; j<256; j++)
      {
        if ((bufferArray[idx].line[j]!=' ') && (bufferArray[idx].line[j]!='\0'))
        {
          separate.push_back(bufferArray[idx].line[j]);
        }

        else if ((bufferArray[idx].line[j]==' '))
        {
          std::string location_char = "";
          int charsize = separate.size();
          for (int i = 0; i < charsize; ++i)
          {
            location_char += separate[i];
          }
          location.push_back(atof(location_char.c_str()));
          vector <char>().swap(separate); //release memory
        }

        else if (bufferArray[idx].line[j]=='\0')
        {
          temp2.layerName = "";
          int charsize = separate.size();
          for (int i = 0; i < charsize; ++i)
          {
            temp2.layerName += separate[i];
          }
          vector <char>().swap(separate);
          temp2.x1 = location[0];
          temp2.y1 = location[1];
          temp2.x2 = location[2];
          temp2.y2 = location[3];
          gdb.setOriginalGuide(temp2);
          vector <double>().swap(location);
          break;
        }
      }
    }

    else {}
      //cout<<bufferArray[idx].line[0]<<endl;
      //cout<<bufferArray[idx].line[j]<<endl;
  }
  cout << "Guide File stored ..." << endl;
  cout << "Guide number is :" << gdb.getOriginalGuide().size() << endl;
}
