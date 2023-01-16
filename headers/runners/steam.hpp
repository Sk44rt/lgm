#include <string>
#include <vector>
#include "utils.hpp"

#define STEAM_SOURCE_NATIVE 0
#define STEAM_SOURCE_SNAP 1
#define STEAM_SOURCE_FLATPAK 2

class Steam
{
public:
  Steam();
  ~Steam();

  std::vector<int> getAppIds();
  std::string getSteamPath();
  int getSteamSource();

private:
  std::string steamPath;
  std::vector<int> appIds;
  int steamSource;

  void checkAppIds();
  void checkSteamSource();
};