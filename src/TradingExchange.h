//
// Created by nisky on 14.11.17.
//


#ifndef BACKTESTING_TOOL_TRADINGEXCHANGE_H
#define BACKTESTING_TOOL_TRADINGEXCHANGE_H

#include <unordered_map>
#include <map>
#include "AccountBalance.h"

using namespace std;

class TradingExchange
{
private:
  map<int,double> emas;
  double fee;
  double slippage;
  double currentPrice;
  
  double getTotalFees();
  void updateEMAs(double currentPrice);
public:
  TradingExchange(double fee, double slippage);
  TradingExchange & operator=(const TradingExchange&) = delete;
  TradingExchange(const TradingExchange *exchange);
  double getEMA(int x);
  void registerEMA(int x);
  void update(double price);
  double sellCrypto(double amount, AccountBalance &balance);
  double buyCrypto(double amount, AccountBalance &balance);
  
};


#endif //BACKTESTING_TOOL_TRADINGEXCHANGE_H
