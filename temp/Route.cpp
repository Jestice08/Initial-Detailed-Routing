#include "Route.h"

void Route (vector <Layer> &layerarray, vector <SegmentResult> &segmentarray, vector <ViaResult> &viaarray, RawDataBase &db, MacroDataBase &macro_db, double layer1start, double layer2start, double stepxx, double stepyy)
{
	int layer_size;
	int layer_index;
	layer_size = layerarray.size();
	for (layer_index = 0; layer_index < layer_size; layer_index++)
	{
		CreateGrid(layerarray[layer_index], db, layer1start, layer2start, stepxx, stepyy);
	}

	for (layer_index = 1; layer_index < layer_size-1; layer_index++)
	{
		int panelSize;
		int panelIdx;
		for (panelIdx = 0; panelIdx < panelSize; panelIdx++)
		{
			vector <APC> apcArray_temp;
			apcArray_temp = overlap(layerarray[layer_index], layerarray[layer_index+1], layerarray[layer_index].panelArray[panelIdx] , layer_index);
			int apcArray_temp_size = apcArray_temp.size();
			for (int temp_idx = 0; temp_idx < apcArray_temp_size; temp_idx++)
			{
				layerarray[layer_index].panelArray[panelIdx].apcArray.push_back(apcArray_temp[temp_idx]);
			}
			// int apcsize;
			// int apcidx;
			// for (apcidx = 0; apcidx < apcsize; apcidx++)
			// {

			// }
			APC_process(layerarray, segmentarray, viaarray, layer_index, panelIdx, layer1start, layer2start, stepxx, stepyy);


		}
	}
}
