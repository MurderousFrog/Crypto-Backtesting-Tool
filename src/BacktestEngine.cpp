//
// Created by nisky on 14.11.17.
//

#include <iostream>
#include <algorithm>
#include <thread>
#include "BacktestEngine.h"

BacktestEngine::BacktestEngine(TradingExchange *exchange): exchange(exchange)
{
  
}

void BacktestEngine::testAlgorithmRange(std::vector<TradingAlgorithm*>::iterator begin,
                                        std::vector<TradingAlgorithm*>::iterator end, vector<double> *prices){
  TradingExchange temp_exchange(*exchange);
  for(auto it = begin; it != end; it++){
    (*it)->SetExchange(&temp_exchange);
  }
  
  for(long i = 0; i < prices->size(); i++){
    if( i > 0 && std::abs((*prices)[i] - (*prices)[i - 1]) < 0.0001){
      continue;
    }
    temp_exchange.update((*prices)[i]);
    updateAlgorithms((*prices)[i], begin, end);
  }
}

void BacktestEngine::runTests(double gracePeriod, double dropoutFactor, double minimumSize)
{
  if(dataSets.size() <= 0)
  {
    cout << "Insufficient data - try adding a price data set with: load set [filepath]" << endl;
    return;
  }
  if(algorithms.size() <= 0)
  {
    cout << "Insufficient algorithms for backtesting." << endl;
    return;
  }
  
  for(auto dataset = dataSets.begin(); dataset != dataSets.end(); dataset++)
  {
    initializeAlgorithms();
    vector<double> *prices = (*dataset)->GetPrices();
    if(prices->size() == 0){
      cout << "No prices found in dataset." << endl;
      continue;
    }
    cout << "Price point count: " <<  prices->size() << endl;
    
    
    std::thread threads[threadCount];
    
    size_t length = algorithms.size() / threadCount;
    size_t remaining = algorithms.size() % threadCount;
    
    
    for(int i = 0; i < threadCount; i++){
      auto begin = algorithms.begin() + i * length;
      auto end = begin + length;
      if(i == threadCount - 1){
        end += remaining;
      }
      threads[i] = std::thread([this, begin, end, prices]{testAlgorithmRange(begin, end, std::ref(prices));});
    }
    
    for(int i = 0; i < threadCount; i++){
      threads[i].join();
    }
    
    for (auto it = algorithms.begin(); it != algorithms.end();  it++){
      (*it)->SetExchange(exchange);
    }
    
    CalculateScore(prices->at(prices->size()-1));
    
    
    if(dataset - dataSets.begin() >= gracePeriod * dataSets.size() && algorithms.size() * (1 - dropoutFactor) > minimumSize){
      sort( algorithms.begin(), algorithms.end(), []( const TradingAlgorithm *lhs, const TradingAlgorithm *rhs )
      {
        return lhs->score < rhs->score;
      });
      for (int i = 0; i < dropoutFactor * algorithms.size(); i++){
        algorithms.erase(algorithms.begin() + i);
      }
    }
    
    ResetBalances(1000,0);
    
    cout << "Sample #" << dataset - dataSets.begin() << " done." << endl;
  }
}

void BacktestEngine::SampleDataSet(int index, int sampleCount, int sampleSize){
  auto samples = DataSet::CreateSamples(dataSets[index], sampleCount, sampleSize);
  dataSets.insert(dataSets.end(), samples.begin(), samples.end());
}

void BacktestEngine::ListDataSets(){
  for(auto it = dataSets.begin(); it != dataSets.end(); it ++){
    cout << "#" << it - dataSets.begin() << ": " << (*it)->GetPrices()->size()<< " price points." << endl;
  }
}

void BacktestEngine::ResetBalances(double fiat, double crypto){
  for (auto it = algorithms.begin(); it != algorithms.end(); it++){
    (*it)->balance.fiat = fiat;
    (*it)->balance.crypto = crypto;
  }
}

void BacktestEngine::CalculateScore(double finalPrice){
  sort( algorithms.begin(), algorithms.end(), [finalPrice]( const TradingAlgorithm *lhs, const TradingAlgorithm *rhs )
  {
    return lhs->balance.GetTotalInFiat(finalPrice) < rhs->balance.GetTotalInFiat(finalPrice);
  });
  
  const auto median_it1 = algorithms.begin() + algorithms.size() / 2 - 1;
  const auto median_it2 = algorithms.begin() + algorithms.size() / 2;
  double median = (algorithms.size() % 2 == 0) ? ((*median_it1)->balance.GetTotalInFiat(finalPrice) + (*median_it2)->balance.GetTotalInFiat(finalPrice)) / 2 : (*median_it2)->balance.GetTotalInFiat(finalPrice);
  
  for (auto it = algorithms.begin(); it != algorithms.end(); it++){
    (*it)->score += (*it)->balance.GetTotalInFiat(finalPrice) / median;
    (*it)->value += (*it)->balance.GetTotalInFiat(finalPrice);
  }
}

void BacktestEngine::DisplayStatistics(){
  sort( algorithms.begin(), algorithms.end(), [=]( const TradingAlgorithm *lhs, const TradingAlgorithm *rhs )
  {
    return lhs->score < rhs->score;
  });
  
  cout << "Name\tID\tScore\tvalue\ttrades" << endl;
  for (auto it = algorithms.begin(); it != algorithms.end(); it++){
    cout << (*it)->name << "\t" << (*it)->id << "\t" << (*it)->score << "\t" << (*it)->value << "\t" << (*it)->balance.trades << "\t";
    (*it)->PrintParameters();
    cout << endl;
  }
}

void BacktestEngine::updateAlgorithms(double price, std::vector<TradingAlgorithm*>::iterator begin,
                                      std::vector<TradingAlgorithm*>::iterator end){
  for (auto it = begin; it != end; it++){
    (*it)->Trade(price);
  }
}

void BacktestEngine::initializeAlgorithms()
{
  for(auto it = algorithms.begin(); it != algorithms.end(); it++)
  {
    (*it)->Initialize();
  }
  
}

int BacktestEngine::loadDataset(string filepath)
{
  DataSet *set = DataSet::LoadFromFile(filepath);
  dataSets.push_back(set);
}

void BacktestEngine::addAlgorithm(TradingAlgorithm &algorithm)
{
  algorithms.push_back(&algorithm);
}

TradingExchange* BacktestEngine::getExchange()
{
  return exchange;
}

void BacktestEngine::RemoveDataSet(int i)
{
  auto delSet = dataSets.at(i);
  delete delSet;
  dataSets.erase(dataSets.begin() + i);
}
