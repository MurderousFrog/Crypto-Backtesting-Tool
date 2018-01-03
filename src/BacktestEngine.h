//
// Created by nisky on 14.11.17.
//

#ifndef BACKTESTING_TOOL_BACKTESTENGINE_H
#define BACKTESTING_TOOL_BACKTESTENGINE_H

#include <vector>
#include "TradingAlgorithm.h"
#include "TradingExchange.h"
#include "DataSet.h"
#include <math.h>
using namespace std;

class BacktestEngine
{
private:
  vector<TradingAlgorithm*> algorithms;
  vector<DataSet*> dataSets;
  TradingExchange *exchange;
  static const int threadCount = 8;
  
  void initializeAlgorithms();
public:
  BacktestEngine(TradingExchange *exchange);
  void runTests(double gracePeriod, double dropoutFactor, double minimumSize);
  int loadDataset(string filepath);
  void addAlgorithm(TradingAlgorithm &algorithm);
  
  void CalculateScore(double finalPrice);
  
  void DisplayStatistics();
  
  void ResetBalances(double fiat, double crypto);
  TradingExchange* getExchange();
  
  void updateAlgorithms(double price, vector<TradingAlgorithm *>::iterator begin,
                        vector<TradingAlgorithm *>::iterator end);
  
  void testAlgorithmRange(vector<TradingAlgorithm *>::iterator begin,
                          vector<TradingAlgorithm *>::iterator end,
                          vector<double> *prices);
  
  void SampleDataSet(int index, int sampleCount, int sampleLength);
  
  void ListDataSets();
  
  void RemoveDataSet(int i);
};


#endif //BACKTESTING_TOOL_BACKTESTENGINE_H
