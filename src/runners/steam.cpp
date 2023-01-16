#include "runners/steam.hpp"

Steam::Steam()
{

}

Steam::~Steam()
{

}

void Steam::checkSteamSource()
{
  if (utils::sys::which("steam").exists)
    this->steamSource = STEAM_SOURCE_NATIVE;
  else if (utils::sys::which("snap").exists)
    this->steamSource = STEAM_SOURCE_SNAP;
  else if (utils::sys::which("flatpak").exists)
    this->steamSource = STEAM_SOURCE_FLATPAK;
}

int Steam::getSteamSource()
{
  return this->steamSource;
}