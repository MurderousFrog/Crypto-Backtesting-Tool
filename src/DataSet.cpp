//
// Created by nisky on 14.11.17.
//

#include "DataSet.h"

DataSet* DataSet::LoadFromFile(string filepath)
{
  ifstream infile(filepath);
  string line;
  vector<double> *prices = new vector<double>();
  while(getline(infile, line)){
    prices->push_back(stod(line, 0));
  }
  return new DataSet(*prices);
}

vector<double> *DataSet::GetPrices()
{
  return &prices;
}

vector<DataSet*>
DataSet::CreateSamples(DataSet *set, int sampleCount, int sampleSize)
{
  vector<DataSet*> samples;
  for(int i = 0; i < sampleCount; i++){
    auto begin = set->prices.begin() + (int)DataSet::Random(0, set->prices.size() - sampleSize - 1);
    auto end = begin + sampleSize;
    DataSet *sample = new DataSet(vector<double>(begin, end));
    samples.push_back(sample);
  }
  return samples;
}

double DataSet::Random(double min, double max)
{
  return min + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(max-min)));
}
