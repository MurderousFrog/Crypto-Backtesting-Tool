//
// Created by nisky on 14.11.17.
//

#ifndef BACKTESTING_TOOL_TRADINGALGORITHM_H
#define BACKTESTING_TOOL_TRADINGALGORITHM_H


#include "AccountBalance.h"
#include "TradingExchange.h"


class TradingAlgorithm
{
protected:
  TradingExchange *exchange;
public:
  double score = 0;
  double value = 0;
  string name;
  int id;
  
  AccountBalance balance;
  TradingAlgorithm(string name, int id, TradingExchange *exchange, AccountBalance &balance);
  virtual void Trade(double price) = 0;
  virtual void PrintParameters() = 0;
  //virtual void Breed(int count, TradingExchange &exchange, AccountBalance &balance);
  static double Random(double min, double max);
  
  virtual void Initialize() = 0;
  void SetExchange(TradingExchange *ex);
};


#endif //BACKTESTING_TOOL_TRADINGALGORITHM_H
