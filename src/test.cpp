/*
test.cpp is source file for testing features
*/

#include <stdio.h>
#include <fstream>
#include "runners/steam.hpp"

int main()
{
  // Steam *steam = new Steam();
  // if (steam->getSteamSource() == STEAM_SOURCE_FLATPAK)
  //   printf("FLATPAK\n");
  // printf("%d\n",steam->getSteamSource());
  auto x=utils::sys::which("zsh");
  if (x.exists)
    printf("%s\n",x.path.c_str());

  return 0;
}