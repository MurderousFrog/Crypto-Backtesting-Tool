//
// Created by nisky on 26.11.17.
//

#include <iostream>
#include "EdgeRunner.h"

EdgeRunner::EdgeRunner(string name, int id, TradingExchange *exchange,
                       AccountBalance &balance, double sellBorder,
                       double buyBorder, double bsFactor)
  : TradingAlgorithm(name, id, exchange, balance),
    sellBorder(sellBorder),
    buyBorder(buyBorder),
    bsfactor(bsFactor)
{
  
}

void EdgeRunner::Trade(double price)
{
  if(middle == 0){
    AdjustWindow(price);
    InitializeBalance(price);
  }else{
    //bot algorithm
    if(price > upper && balance.crypto > 0){
      AdjustWindow(price);
      exchange->sellCrypto(balance.GetTotalInCrypto(price) * bsfactor, balance);
    }else if(price < lower && balance.fiat > 0){
      AdjustWindow(price);
      exchange->buyCrypto(balance.GetTotalInCrypto(price) * bsfactor, balance);
    }
  }
}

void EdgeRunner::AdjustWindow(double price)
{
  middle = price;
  upper = sellBorder * middle;
  lower = buyBorder * middle;
}

void EdgeRunner::InitializeBalance(double price)
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

void EdgeRunner::PrintParameters()
{
  cout << sellBorder << "\t" << buyBorder << "\t" << bsfactor;
}

void EdgeRunner::Initialize()
{
  
}
