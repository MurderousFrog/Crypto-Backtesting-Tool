//
// Created by nisky on 29.11.17.
//

#ifndef BACKTESTING_TOOL_BLADERUNNER_H
#define BACKTESTING_TOOL_BLADERUNNER_H


#include "../TradingAlgorithm.h"

class BladeRunner: public TradingAlgorithm
{
private:
  double max;
  double min;
  double lock;
  double backOff;
  double lastTradePoint = 0;
  bool sell = true;
  
  void InitializeBalance(double price);
  void AdjustWindow(double price);

public:
  BladeRunner(string name, int id, TradingExchange *exchange, AccountBalance &balance,
  double lock, double backOff);
  void Trade(double price);
  void PrintParameters();
  void Initialize();
  
};


#endif //BACKTESTING_TOOL_BLADERUNNER_H
