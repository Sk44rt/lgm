#include "runners/steam.hpp"

Steam::Steam()
{
  checkSteamSource();
  checkAppIds();
}

Steam::~Steam()
{

}

void Steam::checkAppIds()
{
  this->appIds = {};
  if (this->steamSource == STEAM_SOURCE_FLATPAK)
  {
    std::string steamAppsPath = utils::fs::joinPath({this->steamPath, "steamapps"});
    for (std::string file : utils::fs::listDir(steamAppsPath))
    {
      int id;
      bool isDownloaded;
      std::string name;
      if (utils::regex::match(file,"appmanifest_([[:digit:]]+).acf"))
      {
        nlohmann::json d = nlohmann::json::parse(Acf (utils::fs::readFile(steamAppsPath+"/"+file)).get())["AppState"];
        
        id = utils::string::getDigits(d["appid"].get<std::string>());
        isDownloaded = d["BytesDownloaded"] == d["BytesToDownload"];
        name = d["name"].get<std::string>();

        this->appIds.push_back({id,isDownloaded,name}); // std::pair
      }
    }
  }
}

void Steam::checkSteamSource()
{
  if (pm::snap::isInstalled() && pm::snap::pkgInstalled("steam"))
  {
    this->steamSource = STEAM_SOURCE_SNAP;
  }
  else if (utils::sys::which("steam").exists)
  {
    this->steamSource = STEAM_SOURCE_NATIVE;
  }
  else if (pm::flatpak::isInstalled() && pm::flatpak::pkgInstalled("com.valvesoftware.Steam"))
  {
    this->steamSource = STEAM_SOURCE_FLATPAK;
    this->steamPath = utils::fs::joinPath({utils::sys::getEnv("HOME"), "/.var/app/com.valvesoftware.Steam/data/Steam"});
  }
  else
  {
    this->steamSource = STEAM_NOT_INSTALLED;
  }
}

std::vector<steamAppManifest> Steam::getAppIds()
{
  return this->appIds;
}

int Steam::getSteamSource()
{
  return this->steamSource;
}

int Steam::run(int id)
{
  std::string command;
  if (this->steamSource == STEAM_SOURCE_FLATPAK)
    command = utils::string::join(std::string("bash") std::string(utils::fs::joinPath({utils::sys::getEnv("HOME"),"code/lgm/scripts/steamrun.sh"})), std::to_string(id)}, ' ');
  printf("%s\n",command.c_str());

  return subprocess::Popen(command).wait();
}
