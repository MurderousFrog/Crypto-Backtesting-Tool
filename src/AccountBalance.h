//
// Created by nisky on 14.11.17.
//

#ifndef BACKTESTING_TOOL_ACCOUNTBALANCE_H
#define BACKTESTING_TOOL_ACCOUNTBALANCE_H


class AccountBalance
{
public:
  double crypto;
  double fiat;
  int trades = 0;
  AccountBalance(double fiat, double crypto);
  double GetTotalInFiat(double price) const;
  double GetTotalInCrypto(double price) const;
};


#endif //BACKTESTING_TOOL_ACCOUNTBALANCE_H
