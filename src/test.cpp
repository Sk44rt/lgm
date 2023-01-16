/*
test.cpp is source file for testing features
*/

#include <stdio.h>
#include <fstream>
#include "utils.hpp"

int main()
{
  auto w = utils::sys::which("zssh");
  if (w.exists)
    printf("%s",w.path.c_str());

  return 0;
}