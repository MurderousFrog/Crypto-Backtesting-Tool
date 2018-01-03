//
// Created by nisky on 14.11.17.
//

#include <random>
#include "TradingAlgorithm.h"

TradingAlgorithm::TradingAlgorithm(string name, int id, TradingExchange *exchange,
                                   AccountBalance &balance)
  : exchange(exchange), balance(balance), id(id), name(name)
{
  
}

void TradingAlgorithm::SetExchange(TradingExchange *ex)
{
  exchange = ex;
}

double TradingAlgorithm::Random(double min, double max)
{
  return min + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(max-min)));
}
