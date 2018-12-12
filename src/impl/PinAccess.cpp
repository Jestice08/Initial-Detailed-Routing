#include "PinAccess.h"

bool APCForPin (Layer &layer2, double overlapXl, double overlapXh, double overlapYl, double overlapYh, string current_net, double layer1_start, double layer2_start, double stepx, double stepy)
{
	cout <<  "storing apc ..." << endl;
	bool flag;
	bool hasAPFlag;
	flag = false;
	APC temp_apc = APC();
	temp_apc.promote = true;
	temp_apc.connect = false;
	temp_apc.apcLeft = overlapXl;
	temp_apc.apcRight = overlapXh;
	temp_apc.apcTop = overlapYh;
	temp_apc.apcDown = overlapYl;
	temp_apc.net = current_net;
	temp_apc.lowerLayer = "Metal1";
	temp_apc.upperLayer = "Metal2";

	int layer2panel_idx;
	int layer2panel_idx_apc_size;

	cout << "current net: " << current_net << endl;
	cout << " overlapXl: " << overlapXl;
	cout << " overlapXh: " << overlapXh;
	cout << " overlapYl: " << overlapYl;
	cout << " overlapYh: " << overlapYh << endl;


	//cout << (overlapXl - layer2.panelArray[0].left) << endl;
	//cout << (int)layer2.unitWidth << endl;
	layer2panel_idx = (int)(overlapXl - layer2.panelArray[0].left) / (int)(layer2.unitWidth);
	cout << "currently in panel: " << layer2panel_idx << endl;
	layer2panel_idx_apc_size = layer2.panelArray[layer2panel_idx].apcArray.size();
	for (int i = 0; i < layer2panel_idx_apc_size; i++)
	{
		if(layer2.panelArray[layer2panel_idx].apcArray[i].net == current_net)
			flag = true;
	}

	if (flag == false)
	{
		cout << "to be pushed!" << endl;
		int startingx_idx, startingy_idx;
		startingx_idx = ((int) (overlapXl - layer2_start) / (int)(stepx)) +1;
		startingy_idx = ((int) (overlapYl - layer1_start) / (int)(stepy)) +1;
 		for(double i = layer2_start + stepx*startingx_idx; i<overlapXh; i=i+stepx)
 		{
   			for(double j = layer1_start + stepy*startingy_idx; j<overlapYh; j=j+stepy)
   			{
     			AP ap=AP ();
      			ap.xCoordinate=i;
      			ap.yCoordinate=j;
      			temp_apc.aps.push_back(ap);
    		}
		}
		if(temp_apc.aps.size()==0)
		{
			hasAPFlag = false;
		}
		else
		{
			hasAPFlag = true;
		}
		cout <<  "pushing back apc..." << endl;
		cout << "currently in panel: " << layer2panel_idx << endl;
		if (hasAPFlag == true) layer2.panelArray[layer2panel_idx].apcArray.push_back(temp_apc);
		cout << layer2.panelArray[layer2panel_idx].apcArray.size() << endl;
		cout << hasAPFlag << endl;
	}
	return hasAPFlag;
}


void LocateArea (Layer &layer2, RawDataBase &db, MacroDataBase &macro_db, Guide &current_guide, double panel_left, double panel_right, double layer1_start, double layer2_start, double stepx, double stepy)
{
	int size_net;
	int net_idx;
	double guideXl,guideXh, guideYl, guideYh;
	double overlapXl, overlapXh, overlapYl, overlapYh;
	guideXl = current_guide.bottom;
	guideXh = current_guide.top;
	guideYl = panel_left;
	guideYh = panel_right;
	//cout << "finding overlap area..." << endl;
	size_net = current_guide.net.size();
	for (net_idx = 0; net_idx < size_net; net_idx++)
	{
		std::string current_net = current_guide.net[net_idx];
		int base_net_size = db.netArray.size();
		int base_net_idx;
		for (base_net_idx = 0; base_net_idx < base_net_size; base_net_idx++)
		{
			if (current_net == db.netArray[base_net_idx].net_name)
			{
				//cout << "comparing net..." << endl;
				int pin_size;
				int pin_idx;
				string node;
				string pin;
				string macroname;
				int comLocationX, comLocationY;
				int databaseUnit = 2000;
				string direction;
				int direction_number;

				pin_size = db.netArray[base_net_idx].vNetPin.size();
				//cout << pin_size << endl;
				for (pin_idx = 0; pin_idx < pin_size; pin_idx++)
				{
					//search_pin_access_area
					node = get<0>(db.netArray[base_net_idx].vNetPin[pin_idx]);
  					pin = get<1>(db.netArray[base_net_idx].vNetPin[pin_idx]);
  					//cout << "node: " << node << " " << "pin: " << pin << endl; 
  					vector<DefParser::Component>::iterator iter;
					
					//iter is component
					iter = find_if(db.componentArray.begin(),db.componentArray.end(),bind(&DefParser::Component::comp_name,_1)==node);
					macroname = (*iter).macro_name;
					comLocationX = (*iter).origin[0];
					comLocationY = (*iter).origin[1];
					direction = (*iter).orient;
					if (direction == "N")	direction_number = 1;
					else if (direction == "FS") direction_number = 2;
					//cout << "map to:" << macroname << endl;

					//map to stdcell via macroname
					vector<StdCell>::iterator iter2;
					//iter2 is std cell
					iter2 = find_if(macro_db.stdCellArray.begin(),macro_db.stdCellArray.end(),bind(&StdCell::macroName,_1)==macroname);
					int std_pin_size;
					int std_pin_idx;
					//cout << "std cell:" << (*iter2).macroName << endl;
					std_pin_size = (*iter2).pinArray.size();
					//cout << "std cell pin size: " << std_pin_size << endl;
					//cout << endl;
					for (std_pin_idx = 0; std_pin_idx < std_pin_size; std_pin_idx++)
					{
						if ((*iter2).pinArray[std_pin_idx].name == pin)
						{
							double pinXl,pinYl,pinXh,pinYh;
							int netindex = 0;
							int rec_size;
							rec_size = (*iter2).pinArray[std_pin_idx].recArray.size();
							double stdcell_top;

							bool done_flag;
							done_flag = false;
							//cout << "ready" << endl;
							while (done_flag == false)
							{
									// pinXl = comLocationX + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinXl;
									// pinXh = comLocationX + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinXh;
									// pinYl = comLocationY + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinYl;
									// pinYh = comLocationY + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinYh;
								cout << "direction: " << direction_number << endl;

								if (direction_number == 1)
								{
									pinXl = comLocationX + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinXl;
									pinXh = comLocationX + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinXh;
									pinYl = comLocationY + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinYl;
									pinYh = comLocationY + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinYh;
								}
								else 
								{
									pinXl = comLocationX + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinXl;
									pinXh = comLocationX + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinXh;
									pinYl = comLocationY + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinYl;
									pinYh = comLocationY + 2000 * (*iter2).pinArray[std_pin_idx].recArray[netindex].pinYh;
									stdcell_top = (*iter2).sizeY * 2000 + comLocationY;
									pinYl = (stdcell_top - pinYl) + comLocationY;
									pinYh = (stdcell_top - pinYh) + comLocationY;
									double pintemp;
									pintemp = pinYl;
									pinYl = pinYh;
									pinYh = pintemp; 
								}
								// cout << "sizey: " << (*iter2).sizeY << endl;
								// cout << "std top: " << stdcell_top << endl;
								// cout << "pinXl: " << pinXl << " pinXh: " << pinXh << " pinYl: " << pinYl << " pinYh: " << pinYh << endl; 

							//cout << "testing1" << endl;
							//FindOverlap;
							cout << "current Net: " << current_net << endl; 
							if((pinXh > guideXl) && (pinXl < guideXh) && (pinYh >guideYl) && (pinYl < guideYh))		//some bugs here
							{
								overlapXl = max(pinXl,guideXl);
								overlapXh = min(pinXh,guideXh);
								overlapYl = max(pinYl,guideYl);
								overlapYh = min(pinYh,guideYh);
								done_flag = APCForPin (layer2, overlapXl, overlapXh, overlapYl, overlapYh, current_net,layer1_start,layer2_start, stepx,stepy);
								//cout << done_flag << endl;
							}
							// else
							// {
							// 	done_flag = true;
							// }								
							netindex = netindex + 1;
							if(netindex == rec_size) done_flag = true;
							}
						}
					}
				}
			}
		}
	}
}


void PinAccess (Layer &layer1, Layer &layer2, RawDataBase &db, MacroDataBase &macro_db, double layer1_start, double layer2_start, double stepx, double stepy)
{
	cout << "Creating Pin Access ..." << endl;

	int size_panel;
	int size_guide;
	int panel_idx, guide_idx;
	size_panel = layer1.panelArray.size();
	for (panel_idx = 0; panel_idx < size_panel; panel_idx++)
	{
		size_guide = layer1.panelArray[panel_idx].guideArray.size();
		double panel_left = layer1.panelArray[panel_idx].left;
		double panel_right = layer1.panelArray[panel_idx].right;
		for (guide_idx = 0; guide_idx < size_guide; guide_idx++)
		{
			LocateArea (layer2, db, macro_db, layer1.panelArray[panel_idx].guideArray[guide_idx], panel_left, panel_right,layer1_start, layer2_start, stepx, stepy);
		}
	}

	cout << "Pin Access stored as APCs" << endl;
}