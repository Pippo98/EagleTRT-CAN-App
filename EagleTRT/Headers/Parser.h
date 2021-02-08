#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>

#include "Devices.h"

// String stuff
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
class Parser{
public:
  vector<int> splitMessage(double *timestamp, int *id, string message);
  void getTimestamp(double* timestamp, string message);

  int parseChimeraMessage(double timestamp, int id, vector<int> msg, Chimera*);
};
#endif
