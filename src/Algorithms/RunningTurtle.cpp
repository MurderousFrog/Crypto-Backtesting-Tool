
#include <iostream>
#include "RunningTurtle.h"


RunningTurtle::RunningTurtle(string name, int id, TradingExchange *exchange,
                         AccountBalance &balance, double lock, double lockOffset,
                             double backOff, double backOffOffset)
  : TradingAlgorithm(name, id, exchange, balance),
    lock(lock),
    lockOffset(lockOffset),
    backOff(backOff),
    backOffOffset(backOffOffset)
{
  
}


void RunningTurtle::Trade(double price)
{
  if(price > max){
    max = price;
    upperThreshold = max * (1 - backOff + backOffOffset);
  }else if (price < min){
    min = price;
    lowerThreshold = min * (1 + backOff + backOffOffset);
  }
  
  if(lastTradePoint == 0){
    AdjustWindow(price);
  }else{
    if(price > upperLock){
      if(price <= upperThreshold){
        exchange->sellCrypto(balance.crypto, balance);
        AdjustWindow(price);
      }
    }else if (price < lowerLock){
      if(price >= lowerThreshold){
        exchange->buyCrypto(balance.fiat/price, balance);
        AdjustWindow(price);
      }
    }
  }
}

void RunningTurtle::AdjustWindow(double price)
{
  lastTradePoint = price;
  max = price;
  min = price;
  upperLock = lastTradePoint * (1 + lock + lockOffset);
  lowerLock = lastTradePoint * (1 - lock + lockOffset);
}

void RunningTurtle::InitializeBalance(double price)
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

void RunningTurtle::PrintParameters()
{
  cout << lock << "\t" << lockOffset << "\t" << backOff  << "\t" << backOffOffset;
}

void RunningTurtle::Initialize()
{
  //exchange.registerEMA(ema);
}


