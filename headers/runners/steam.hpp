#include <string>
#include <vector>
#include "utils.hpp"
#include "acf.hpp"
#include "json.hpp"

#define STEAM_SOURCE_NATIVE 0
#define STEAM_SOURCE_SNAP 1
#define STEAM_SOURCE_FLATPAK 2

struct steamAppManifest
{
  int id;
  bool isDownloaded;
  std::string name;
};

class Steam
{
public:
  Steam();
  ~Steam();

  std::vector<steamAppManifest> getAppIds();
  std::string getSteamPath();
  int getSteamSource();

  int run(int id);

private:
  std::string steamPath;
  std::vector<steamAppManifest> appIds; // path<id,isDownloaded>
  int steamSource;

  void checkAppIds();
  void checkSteamSource();
};