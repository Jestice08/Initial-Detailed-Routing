#include "PinAccess.h"

void APCForPin (Layer &layer2, double overlapXl, double overlapXh, double overlapYl, double overlapYh, string current_net, double layer1_start, double layer2_start, double stepx, double stepy)
{
	bool flag;
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
	layer2panel_idx = (int)(overlapXl) / (int)(layer2.unitWidth);
	layer2panel_idx_apc_size = layer2.panelArray[layer2panel_idx].apcArray.size();
	for (int i = 0; i < layer2panel_idx_apc_size; i++)
	{
		if(ayer2.panelArray[layer2panel_idx].apcArray[i].net == current_net)
			flag = true;
	}

	if (flag = false)
	{
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
		layer2.panelArray[layer2panel_idx].apcArray.push_back(temp_apc);
	}

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

	size_net = current_guide.net.size();
	for (net_idx = 0; net_idx < size_net; net_idx++)
	{
		std::string current_net = current_guide.net[net_idx];
		int base_net_size = db.NetArray.size();
		int base_net_idx;
		for (base_net_idx = 0; base_net_idx < base_net_size; base_net_idx++)
		{
			if (current_net == db.NetArray[base_net_idx].net_name)
			{
				int pin_size;
				int pin_idx;
				string node;
				string pin;
				string macroname;
				int comLocationX, comLocationY;
				int databaseUnit = 2000;

				pin_size = db.NetArray[base_net_idx].vNetPin.size();
				for (pin_idx = 0; pin_idx < pin_size; pin_idx++)
				{
					//search_pin_access_area
					node = get<0>(db.NetArray[base_net_idx].vNetPin[pin_idx]);
  					pin = get<1>(db.NetArray[base_net_idx].vNetPin[pin_idx]);
  					vector<DefParser::Component>iterator iter;
					//iter is component
					iter = find_if(db.componentArray.begin(),db.componentArray.end(),bind(&DefParser::Component::comp_name,_1)==node);
					macroname = (*iter).macro_name;
					comLocationX = (*iter).origin[0];
					comLocationY = (*iter).origin[1];
					
					//map to stdcell via macroname
					vector<StdCell>iterator iter2;
					//iter2 is std cell
					iter2 = find_if(macro_db.stdCellArray.begin(),macro_db.stdCellArray.end(),bind(StdCell::macroName,_1)==macroname);
					int std_pin_size;
					int std_pin_idx;
					std_pin_size = (*iter2).PinArray.size();
					for (std_pin_idx = 0; std_pin_idx < std_pin_size; std_pin_idx++)
					{
						if ((*iter2).PinArray[std_pin_idx].name == pin)
						{
							double pinXl,pinYl,pinXh,pinYh;
							pinXl = comLocationX + 2000 * (*iter2).PinArray[std_pin_idx].pinXl;
							pinXh = comLocationX + 2000 * (*iter2).PinArray[std_pin_idx].pinXh;
							pinYl = comLocationY + 2000 * (*iter2).PinArray[std_pin_idx].pinYl;
							pinYh = comLocationY + 2000 * (*iter2).PinArray[std_pin_idx].pinYh;

							//FindOverlap;
							if((pinXh >= guideXl) && (pinXl <= guideXh) && (pinYh >=guideYl) && (pinYl <= guideYh))
							{
								overlapXl = max(pinXl,guideXl);
								overlapXh = min(pinXh,guideXh);
								overlapYl = max(pinYl,guideYl);
								overlapYh = min(pinYh,guideYh);
								APCForPin (layer2, overlapXl, overlapXh, overlapYl, overlapYh, current_net);

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
	int size_panel;
	int size_guide;
	int panel_idx, guide_idx;
	size_panel = layer1.panelArray.size();
	for (panel_idx = 0; panel_idx < size_panel; panel_idx++)
	{
		size_guide = layer1.panelArray[panel_idx].guideArray.size();
		for (guide_idx = 0; guide_idx < size_guide; guide_idx++)
		{
			LocateArea (layer2, db, macro_db, layer1.panelArray[panel_idx].guideArray[guide_idx], panel_left, panel_right);
		}
	}
}