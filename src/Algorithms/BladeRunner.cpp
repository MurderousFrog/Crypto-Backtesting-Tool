//
// Created by nisky on 29.11.17.
//

#include <iostream>
#include "BladeRunner.h"


BladeRunner::BladeRunner(string name, int id, TradingExchange *exchange,
                       AccountBalance &balance, double lock, double backOff)
  : TradingAlgorithm(name, id, exchange, balance),
    lock(lock),
    backOff(backOff)
{
  
}


void BladeRunner::Trade(double price)
{
  max = std::max(max, price);
  min = std::min(min, price);
  if(lastTradePoint == 0)
  {
    AdjustWindow(price);
  }else
  {
    if(price > lastTradePoint * (1 + lock))
    {
      if(price <= max * (1 - backOff))
      {
        //if(sell)
        {
          exchange->sellCrypto(balance.crypto, balance);
          AdjustWindow(price);
        }
      }
    }
    else if (price < lastTradePoint * (1 - lock))
    {
      if(price >= min * (1 + backOff))
      {
        //if(!sell)
        {
          exchange->buyCrypto(balance.fiat / price, balance);
          AdjustWindow(price);
        }
      }
    }
  }
}

void BladeRunner::AdjustWindow(double price)
{
  lastTradePoint = price;
  max = price;
  min = price;
  sell = !sell;
}

void BladeRunner::InitializeBalance(double price)
{
  double totalCryptoHalf = balance.GetTotalInCrypto(price)/2;
  if(balance.crypto > totalCryptoHalf){
    exchange->sellCrypto(balance.crypto - totalCryptoHalf, balance);
  }
  else
  {
    exchange->buyCrypto(totalCryptoHalf - balance.crypto, balance);
  }
}

void BladeRunner::PrintParameters()
{
  cout << lock << "\t" << backOff;
}

void BladeRunner::Initialize()
{
  //exchange.registerEMA(ema);
}


