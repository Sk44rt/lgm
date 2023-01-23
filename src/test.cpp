/*
test.cpp is source file for testing features
*/

#include <stdio.h>
#include <fstream>
#include "runners/steam.hpp"

int main()
{
  printf("%s\n", utils::string::remove(" 123   4 56  7    8 9    ", ' ').c_str());

  return 0;
}
