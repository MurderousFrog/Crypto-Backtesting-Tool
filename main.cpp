#include <iostream>
#include "src/BacktestTool.h"

using namespace std;

int main()
{
  TradingExchange exchange(0.0025, 0.000);
  BacktestEngine bte(&exchange);
  BacktestTool btt(bte);
  return btt.start();
}