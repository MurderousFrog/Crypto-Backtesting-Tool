

#include "../TradingAlgorithm.h"

#ifndef BACKTESTING_TOOL_RUNNINGTURTLE_H
#define BACKTESTING_TOOL_RUNNINGTURTLE_H


class RunningTurtle: public TradingAlgorithm
{
private:
  double max;
  double min;
  double lock;
  double lockOffset;
  double backOff;
  double backOffOffset;
  double upperLock;
  double lowerLock;
  double upperThreshold;
  double lowerThreshold;
  double lastTradePoint = 0;
  
  void InitializeBalance(double price);
  void AdjustWindow(double price);

public:
  RunningTurtle(string name, int id, TradingExchange *exchange, AccountBalance &balance,
              double lock, double lockOffset, double backOff, double backOffOffset);
  void Trade(double price);
  void PrintParameters();
  void Initialize();
  
};
#endif //BACKTESTING_TOOL_RUNNINGTURTLE_H
