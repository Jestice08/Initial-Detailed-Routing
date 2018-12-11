#include<vector>
#include<string>
#include<algorithm>
#include "overlap.h"  //can I directly use panelArray[index] to get current layer info? and use layer[index+1]to get info of upper layer??
#include "layer.h"
using namespace std;
vector<APC> overlap(Layer &layer_low,Layer & layer_high,Panel &panel_low,int layerindex){  //we can first use vector.size to get size of panel array and then for loop for (panel++)
  double x1=panel_low.left;
  double x2=panel_low.right;
  double unit=layer_high.unitWidth;//need to judge whether top layer??
  int lowindex,upindex;
  //cout << "panel low left: "<< x1 << endl;
  //cout << "panel low right: "<< x2 << endl;
  //cout << "come into function overlap: unit width next layer" << unit << endl;
  vector<APC> ApcArray;
  //cout << "panel_low: " << panel_low.guideArray.size() << endl;
  for (int i = 0;i<panel_low.guideArray.size();i++){
    
    //cout <<"ith loop: "<< i << endl; //test if enter into here
    double y2=panel_low.guideArray[i].top; //for current layer panel's all guides,each guide find top/down coordinate
    double y1=panel_low.guideArray[i].bottom;
    //cout << "low panel ith guide bottom= " << y1<< endl;
    //cout << "low panel ith guide top= "<< y2<< endl;
    if((int)(y2-layer_high.panelArray[0].left)%(int)unit==0){
      lowindex=(y1-layer_high.panelArray[0].left)/unit;  //find corresponding panel index from upper layer
      upindex=(y2-layer_high.panelArray[0].left)/unit-1;
      //cout << "upper layer panel lowindex is :" << lowindex << endl;//when layer1.panel1.guide1 overlap properly with layer2.panel1
      //cout << "upper layer panel upindex is :" << upindex << endl;
    }
    else{
      lowindex=(y1-layer_high.panelArray[0].left)/unit;  //find corresponding panel index for upper layer
      upindex=(y2-layer_high.panelArray[0].left)/unit;
      //cout << "upper layer panel lowindex is :" << lowindex << endl;//when layer1.panel1.guide1 overlap properly with layer2.panel1
      //cout << "upper layer panel upindex is :" << upindex << endl;
    }
    for(int j=lowindex;j<=upindex;j++){ //search from possible upper panel index
      vector <int> upperGuideArray;
      //cout << "when upper layer panel number=" << j << endl;
      for(int k=0;k<layer_high.panelArray[j].guideArray.size();k=k+1){
          if((layer_high.panelArray[j].guideArray[k].top>x1)&&(layer_high.panelArray[j].guideArray[k].bottom<x2)){
            upperGuideArray.push_back(k);
          }
      }
      for(int l=0; l< upperGuideArray.size(); l++){  // for each guide, find if has same net first,if yes then output overlay apcs
        vector<std::string> sameNetarray;
        sort(layer_high.panelArray[j].guideArray[upperGuideArray[l]].net.begin(),layer_high.panelArray[j].guideArray[upperGuideArray[l]].net.end());//sort upper layer guide net
        sort(panel_low.guideArray[i].net.begin(),panel_low.guideArray[i].net.end());
        //cout << "l= " << l<< endl;
        // for(int zzz=0;zzz<layer_high.panelArray[j].guideArray[upperGuideArray[l]].net.size();zzz++){
        //   cout << "layer_high.panelArray[j].guideArray[upperGuideArray[l]].net included: "<< layer_high.panelArray[j].guideArray[upperGuideArray[l]].net[zzz] << endl;
        // }
        // for(int yyy=0;yyy<panel_low.guideArray[i].net.size();yyy++){
        //   cout << "panel_low.guideArray[i].net included: "<< panel_low.guideArray[i].net[yyy] << endl;
        // }


        std::set_intersection(   //save net into sameNetarray
          panel_low.guideArray[i].net.begin(),panel_low.guideArray[i].net.end(),
          layer_high.panelArray[j].guideArray[upperGuideArray[l]].net.begin(),layer_high.panelArray[j].guideArray[upperGuideArray[l]].net.end(),
          std::back_inserter( sameNetarray )
        );

        // for(int z=0; z<sameNetarray.size();z++){
        //   cout << "samearray: "<< sameNetarray[z] <<endl;
        // }

        if(sameNetarray.begin()!=sameNetarray.end()){ //for every common net, create one apc
          for(int m = 0;m<sameNetarray.size();m++){
            APC ApcCreated=APC();
            ApcCreated.lowerLayer = layer_low.layerName;
            //cout <<"low layer name: " <<ApcCreated.lowerLayer << endl;
            ApcCreated.upperLayer = layer_high.layerName;
            ApcCreated.net= sameNetarray[m];
            //cout <<"ApcCreated.net :" << ApcCreated.net<<endl;
            ApcCreated.promote = false;
            ApcCreated.connect = false;

            // cout <<"panel_low.guideArray[i]: " << i << endl;
            // cout <<"layer_high.panelArray[j].guideArray[upperGuideArray[l]].l: " << upperGuideArray[l] << endl;
            // cout <<"layer_high.panelArray[j].j: " << j << endl;
            // cout <<"layerindex: " << layerindex << endl;
            ApcCreated.aps = CreateApcs(panel_low.guideArray[i],layer_high.panelArray[j].guideArray[upperGuideArray[l]],panel_low,layer_high.panelArray[j],layerindex);
            //copy (CreateApcs(panel_low.guideArray[i],layer_high.panelArray[j].guideArray[l],panel_low,layer_high.panelArray[j],layerindex).begin(),CreateApcs(panel_low.guideArray[i],layer_high.panelArray[j].guideArray[l],panel_low,layer_high.panelArray[j],layerindex).end(),ApcCreated.aps.begin());
            
            //cout<<"ApcCreated.promote :" << ApcCreated.promote<< endl;

            // for(int zz=0;zz<ApcCreated.aps.size();zz++){
            //   cout <<"ApcCreated.aps.xCoordinate :"<< ApcCreated.aps[zz].xCoordinate << endl;
            //   cout <<"ApcCreated.aps.yCoordinate :"<< ApcCreated.aps[zz].yCoordinate << endl;
            // }

            ApcCreated.apcLeft=ApcCreated.aps[0].xCoordinate;
            ApcCreated.apcRight=ApcCreated.aps[ApcCreated.aps.size()-1].xCoordinate;
            ApcCreated.apcTop=ApcCreated.aps[ApcCreated.aps.size()-1].yCoordinate;
            ApcCreated.apcDown=ApcCreated.aps[0].yCoordinate;
            ApcArray.push_back(ApcCreated);
          }
        }
      }
    }
  }
  return ApcArray;
}                                                                                     
