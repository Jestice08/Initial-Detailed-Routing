#include "Route.h"

void Route (vector <Layer> &layerarray, vector <SegmentResult> &segmentarray, vector <ViaResult> &viaarray, RawDataBase &db, MacroDataBase &macro_db, double layer1start, double layer2start, double stepxx, double stepyy)
{
	cout << "routing ..." << endl;
	int layer_size;
	int layer_index;
	layer_size = layerarray.size();
	for (layer_index = 0; layer_index < layer_size; layer_index++)
	{
		// cout << "creating grid ..." << endl;
		CreateGrid(layerarray[layer_index], db, layer1start, layer2start, stepxx, stepyy);
	}

	for (layer_index = 1; layer_index < layer_size-1; layer_index++)
	{
		int panelSize;
		int panelIdx;
		panelSize = layerarray[layer_index].panelArray.size();
		for (panelIdx = 0; panelIdx < panelSize; panelIdx++)
		{
			vector <APC> apcArray_temp;
			// cout << "current layer:" << layer_index << endl;
			// cout << "upper layer:" << layer_index+1 << endl;
			// cout << "panel idx:" << panelIdx << endl;
			apcArray_temp = overlap(layerarray[layer_index], layerarray[layer_index+1], layerarray[layer_index].panelArray[panelIdx] , layer_index);
			cout << "overlap done!" << endl;
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
		layer_index = layer_index +1;
	//top layer
	cout << "current layer size - 1: " << layer_size-1 << endl;
	cout << "current layer index: " << layer_index << endl;
	if (layer_index == layer_size-1)
	{
		int panelSize2 = layerarray[layer_index].panelArray.size();
		int panelIdx2;
		for (panelIdx2 = 0; panelIdx2 < panelSize2; panelIdx2++)
		{	
		APC_process(layerarray, segmentarray, viaarray, layer_index, panelIdx2, layer1start, layer2start, stepxx, stepyy);
		}
	}
	}
}
