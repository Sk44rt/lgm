/*
test.cpp is source file for testing features
*/

#include <stdio.h>
#include <fstream>
#include "runners/steam.hpp"

int main()
{
  Steam *steam = new Steam();
  for (auto app : steam->getAppIds())
    if (app.isDownloaded) printf("%s: %d\n", app.name.c_str(), app.id);
  printf("select your game (write appid): ");
  static char input[10];
  scanf("%s",input);
  // printf("%s\n",input);
  int gameId = utils::string::toDigit(std::string(input));
  int status = steam->run(gameId);
  
  return 0;
}