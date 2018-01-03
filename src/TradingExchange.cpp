//
// Created by nisky on 14.11.17.
//

#include <iostream>
#include "TradingExchange.h"

TradingExchange::TradingExchange(double fee, double slippage):
  fee(fee), slippage(slippage)
{
  
}

void TradingExchange::registerEMA(int x)
{
  emas[x] = 1;
}

double TradingExchange::getEMA(int x)
{
  cout << emas.size() << endl;
  auto ema = emas.find(x);
  if(ema != emas.end()){
    cout << ema->second << endl;
    return ema->second;
  }
  return 0.0;
}

void TradingExchange::updateEMAs(double currentPrice)
{
  cout << emas.size() << endl;
  for (auto &it : emas)
  {
    double k = 2 / (it.first + 1);
    double previousPrice = it.second;
    double result = ((currentPrice - previousPrice) * k) - previousPrice;
    it.second = result;
  }
}

double TradingExchange::sellCrypto(double amount, AccountBalance &balance)
{
  double remaining = 0;
  if(balance.crypto == 0){
    return remaining;
  }
  if(amount <= balance.crypto)
  {
    remaining = balance.crypto - amount;
    balance.crypto = remaining;
    balance.fiat += amount * currentPrice * (1 - getTotalFees());
    balance.trades++;
  }
  else
  {
    double correctedAmount = balance.crypto;
    balance.crypto = 0;
    balance.fiat += correctedAmount * currentPrice * (1 - getTotalFees());
    balance.trades++;
  }
  return remaining;
}

double TradingExchange::getTotalFees()
{
  return fee + slippage;
}

double TradingExchange::buyCrypto(double amount, AccountBalance &balance)
{
  double remaining = 0;
  if(balance.fiat == 0){
    return remaining;
  }
  if (amount * currentPrice <= balance.fiat){
    remaining = balance.fiat - amount * currentPrice;
    balance.fiat = remaining;
    balance.crypto += amount * (1 - getTotalFees());
    balance.trades++;
  }
  else{
    double correctedAmount = balance.fiat / currentPrice;
    balance.fiat = 0;
    balance.crypto += correctedAmount * (1 - getTotalFees());
    balance.trades++;
  }
  return remaining;
}

void TradingExchange::update(double price)
{
  currentPrice = price;
  //updateEMAs(currentPrice);
}

TradingExchange::TradingExchange(const TradingExchange *exchange)
{
  emas = exchange->emas;
  fee = exchange->fee;
  slippage = exchange->slippage;
  currentPrice = exchange->currentPrice;
}
