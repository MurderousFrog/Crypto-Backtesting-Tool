//
// Created by nisky on 14.11.17.
//

#ifndef BACKTESTING_TOOL_BACKTESTTOOL_H
#define BACKTESTING_TOOL_BACKTESTTOOL_H

#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "BacktestEngine.h"

#define GREETING_STRING "Backtesting-tool started."
#define IO_ERROR "An IO error has occurred, exiting now."
#define EOF_ERROR "EOF received, exiting now."
#define TOOL_STARTED "Backtesting tool started. Enter help for more information."
#define HELP "Type 'quit' to quit.\n'help' to display this message."

using namespace std;

class BacktestTool
{
private:
  BacktestEngine engine;
  bool quit = false;
  size_t selected = 0;
  
  void loadEnvironment();
  void printErr(string &err);
  int readInput(string &input);
  void handleInput(string &input);
  
public:
  BacktestTool(BacktestEngine engine);
  int start();
  vector<string> split(const string &s, char delim);
  
  template<typename Out>
  void split(const string &s, char delim, Out result);
  
  void Initialize();
};


#endif //BACKTESTING_TOOL_BACKTESTTOOL_H
