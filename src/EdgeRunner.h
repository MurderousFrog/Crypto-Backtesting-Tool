//
// Created by nisky on 26.11.17.
//

#ifndef BACKTESTING_TOOL_EDGERUNNER_H
#define BACKTESTING_TOOL_EDGERUNNER_H


#include "TradingAlgorithm.h"

class EdgeRunner : public TradingAlgorithm
{
private:
  double sellBorder = 0;
  double buyBorder = 0;
  double middle = 0;
  double upper = 0;
  double lower = 0;
  double bsfactor = 0;
  
  void InitializeBalance(double price);
  void AdjustWindow(double price);
  
public:
  EdgeRunner(string name, int id, TradingExchange *exchange, AccountBalance &balance,
    double sellBorder, double buyBorder, double bsFactor);
  void Trade(double price);
  void PrintParameters();
  void Initialize();
};


#endif //BACKTESTING_TOOL_EDGERUNNER_H
