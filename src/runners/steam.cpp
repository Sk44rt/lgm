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
    std::string steamAppsPath = this->steamPath + "/steamapps";
    for (std::string file : utils::fs::listDir(steamAppsPath))
    {
      int id;
      bool isDownloaded;
      std::string name;
      if (utils::regex::match(file,"appmanifest_([[:digit:]]+).acf"))
      {
        // this->appIds.push_back(utils::string::toDigit(file));
        nlohmann::json d = nlohmann::json::parse(Acf(utils::fs::readFile(steamAppsPath+"/"+file)).get())["AppState"];
        id = std::stoi(d["appid"].get<std::string>());
        isDownloaded = d["BytesDownloaded"] == d["BytesToDownload"];
        name = d["name"].get<std::string>();
        this->appIds.push_back({id,isDownloaded,name}); // std::pair
      }
    }
  }
}

void Steam::checkSteamSource()
{
  if (utils::sys::which("steam").exists)
  {
    this->steamSource = STEAM_SOURCE_NATIVE;
  }
  else if (utils::sys::which("snap").exists)
  {
    this->steamSource = STEAM_SOURCE_SNAP;
  }
  else if (utils::sys::which("flatpak").exists)
  {
    this->steamSource = STEAM_SOURCE_FLATPAK;
    this->steamPath = "/home/sk4rt/.var/app/com.valvesoftware.Steam/data/Steam";
  }
  else
  {
    this->steamSource = -1;
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
    command += "bash ./scripts/steamrun.sh " + std::to_string(id);

  return subprocess::Popen(command).wait();
}
