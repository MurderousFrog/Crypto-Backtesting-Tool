//
// Created by nisky on 14.11.17.
//

#include "AccountBalance.h"

AccountBalance::AccountBalance(double fiat, double crypto)
  :fiat(fiat), crypto(crypto)
{
  
}

double AccountBalance::GetTotalInFiat(double price) const
{
  return fiat + crypto * price;
}

double AccountBalance::GetTotalInCrypto(double price) const
{
  return crypto + fiat / price;
}
