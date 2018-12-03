#include<vector>
#include<string>
#include<algorithm>
#include "overlap.h"  //can I directly use panelArray[index] to get current layer info? and use layer[index+1]to get info of upper layer??

using namespace std;
vector<APC> overlap(Layer &layer_low,Layer & layer_high,Panel &panel_low,int layerindex){  //we can first use vector.size to get size of panel array and then for loop for (panel++)
  double x1=panel_low.left;
  double x2=panel_low.right;
  double unit=layer_high.unitWidth;//need to judge whether top layer??
  vector<APC> ApcArray;
  for (int i = 0;i<panel_low.guideArray.size();i++){  ///will the compiler differentiate panelArray[].guideARRAY//A class index, and guideArray[].size,a function?
    double y2=panel_low.guideArray[i].top; //for current layer panel's all guides,each guide find top/down coordinate
    double y1=panel_low.guideArray[i].bottom;
    int lowindex=y1/unit;  //find corresponding panel index for upper layer
    int upindex=y2/unit;
      for(int j=lowindex;j<=upindex;j++){ //for each possible overlap panel
        int guideindexl=0;//need to consider lowindex=upindex??
        int guideindexh=0;
        int k=0;
        while(k<layer_high.panelArray[j].guideArray.size()){
          if(layer_high.panelArray[j].guideArray[k].top>x1){
            guideindexl=k;
            k=0;///will this affect guideindexl output???to reset to 0??
            break;
          }
          else{
            k=k++;
          }
        }//find guide lower index of upper layer panel
        while(k<layer_high.panelArray[j].guideArray.size()){
          if(layer_high.panelArray[j].guideArray[k].bottom>x2){
            guideindexh=k-1;
            k=0;
          }
          else{
            k=k++;
          }
        }//find guide upper index of upper layer panel
        for(int l=guideindexl; l<=guideindexh; l++){  // for each guide, find if has same net first,if yes then output overlay apcs
          vector<std::string> sameNetarray;
          sort(layer_high.panelArray[j].guideArray[l].net.begin(),layer_high.panelArray[j].guideArray[l].net.end());//sort upper layer guide net
          sort(panel_low.guideArray[i].net.begin(),panel_low.guideArray[i].net.end());
          std::set_intersection(   //save net into sameNetarray
            panel_low.guideArray[i].net.begin(),panel_low.guideArray[i].net.end(),
            layer_high.panelArray[j].guideArray[l].net.begin(),layer_high.panelArray[j].guideArray[l].net.end(),
            std::back_inserter( sameNetarray )
          );//set_intersection  need to give to an variable?
          if(sameNetarray.begin()!=sameNetarray.end()){ //for every common net, create one apc
            for(int m = 0;m<sameNetarray.size();m++){
              APC ApcCreated=APC();
              ApcCreated.lowerLayer = layer_low.layerName;
              ApcCreated.upperLayer = layer_high.layerName;
              ApcCreated.net= sameNetarray[m];
              ApcCreated.promote = false;
              ApcCreated.connect = false;
              //ApcCreated.aps = CreateApcs(panel_low.guideArray[i],layer_high.panelArray[j].guideArray[l],panel_low,layer_high.panelArray[j],layerindex);
              copy (CreateApcs(panel_low.guideArray[i],layer_high.panelArray[j].guideArray[l],panel_low,layer_high.panelArray[j],layerindex).begin(),CreateApcs(panel_low.guideArray[i],layer_high.panelArray[j].guideArray[l],panel_low,layer_high.panelArray[j],layerindex).end(),ApcCreated.aps.begin());
              ApcArray.push_back(ApcCreated);
            }
          }
        }
      }
    }
  }                                                                                        //overlap
//}
