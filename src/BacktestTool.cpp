//
// Created by nisky on 14.11.17.
//

#include <iostream>
#include "BacktestTool.h"
#include "Algorithms/EdgeRunner.h"
#include "Algorithms/BladeRunner.h"
#include "Algorithms/RunningTurtle.h"

class Out;

void BacktestTool::printErr(string &err)
{
  cout << "[ERR] " << err << endl;
}

int BacktestTool::readInput(string &input)
{
  cout << "> ";
  if(getline(cin, input)){
    return 1;
  }else{
    return 0;
  }
}

void BacktestTool::handleInput(string &input)
{
  vector<string> args = split(input, ' ');
  if(args[0] == "quit")
  {
    quit = true;
    cout << "Bye." << endl;
    exit(EXIT_SUCCESS);
  }
  else if (args[0] == "help")
  {
    cout << HELP << endl;
  }
  else if (args[0] == "rm" || args[0] == "remove")
  {
    if(args[1] == "sample" ||args[1] == "s"){
      engine.RemoveDataSet(stoi(args[2]));
    }
  }
  else if (args[0] == "ls" || args[0] == "list")
  {
    if(args[1] == "sample" ||args[1] == "s"){
      engine.ListDataSets();
    }
  }
  else if (args[0] == "test")
  {
    //loadEnvironment();
  }
  else if (args[0] == "run")
  {
    for(int i = 0; i < stoi(args[1]); i++){
      AccountBalance *balance = new AccountBalance(1000, 0);
      
      EdgeRunner *er = new EdgeRunner("EdgeRunner", i, engine.getExchange(),*(balance)
        ,TradingAlgorithm::Random(1,2), TradingAlgorithm::Random(0, 1), TradingAlgorithm::Random(0, 1));
      engine.addAlgorithm(*er);
       
      
      BladeRunner *br = new BladeRunner("BladeRunner", i,
                                        engine.getExchange(),
                                        *(balance),
                                        TradingAlgorithm::Random(0,0.5),
                                        TradingAlgorithm::Random(0,0.5));
      
      engine.addAlgorithm(*br);
      
      double lock = TradingAlgorithm::Random(0,0.5);
      double backOff = TradingAlgorithm::Random(0,0.5);
      
      RunningTurtle *rt = new RunningTurtle("RunningTurtle", i,
                                            engine.getExchange(),
                                            *(balance),
                                            lock,
                                            TradingAlgorithm::Random(-lock, lock),
                                            backOff,
                                            TradingAlgorithm::Random(-backOff, backOff));
      engine.addAlgorithm(*rt);
    }
    engine.runTests(0.1, 0.15, 1000);
    engine.DisplayStatistics();
  }
  else if (args[0] == "stats")
  {
    engine.DisplayStatistics();
  }
  else if (args[0] == "sample")
  {
    engine.SampleDataSet(stoi(args[1]), stoi(args[2]), stoi(args[3]));
  }
  else if (args[0] == "load")
  {
    if(args[1] == "set")
    {
      engine.loadDataset(args[2]);
    }
    if(args[1] == "default"){
      engine.loadDataset("../data/full_history.txt");
      engine.SampleDataSet(0, 100, 40000);
      engine.RemoveDataSet(0);
    }
  }
}

template<typename Out>
void BacktestTool::split(const string &s, char delim, Out result){
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> BacktestTool::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

void BacktestTool::loadEnvironment()
{
  /*
  //TODO:
  //later we will do setting file loads here
  //for now just initializing some defaults
  TradingExchange exchange(0.0025, 0.02);
  BacktestEngine *bte = new BacktestEngine(&exchange);
  for(int i = 0; i < 1000; i++){
    AccountBalance *balance = new AccountBalance(0, 5);
    /*EdgeRunner *er = new EdgeRunner("EdgeRunner", i, *exchange,*(balance)
      ,TradingAlgorithm::Random(1,2), TradingAlgorithm::Random(0, 1), TradingAlgorithm::Random(0, 1));
    
    BladeRunner *br = new BladeRunner("BladeRunner", i, &exchange, *(balance), TradingAlgorithm::Random(0,0.25), TradingAlgorithm::Random(0,0.25),(int)TradingAlgorithm::Random(1,100));
     
     bte->addAlgorithm(*br);
  }
  //testEngines.push_back(bte);
  bte->loadDataset("../data/full_history.txt");
  */
}

int BacktestTool::start()
{
  string input;
  
  cout << TOOL_STARTED << endl;
  
  while(readInput(input))
  {
    handleInput(input);
  }
  if(cin.bad())
  {
    cout << IO_ERROR << endl;
    return EXIT_FAILURE;
  }
  else if (cin.eof())
  {
    cout << EOF_ERROR << endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_FAILURE;
}

void BacktestTool::Initialize(){
  
}

BacktestTool::BacktestTool(BacktestEngine engine) : engine(engine)
{
  srand (static_cast <unsigned> (1337));
  cout.precision(4);
  std::cout.setf(std::ios::fixed);
}


