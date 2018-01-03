//
// Created by nisky on 14.11.17.
//

#ifndef BACKTESTING_TOOL_DATASET_H
#define BACKTESTING_TOOL_DATASET_H

#include <vector>
#include <string>
#include <fstream>
#include "TradingAlgorithm.h"

using namespace std;

class DataSet
{
private:
  vector<double> prices;
public:
  DataSet(vector<double> prices): prices(prices){};
  vector<double> *GetPrices();
  static DataSet* LoadFromFile(string filepath);
  static vector<DataSet*> CreateSamples(DataSet *set, int sampleCount, int sampleSize);
  
  static double Random(double min, double max);
};


#endif //BACKTESTING_TOOL_DATASET_H
