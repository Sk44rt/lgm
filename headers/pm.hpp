/*
  Package manager's utils (flatpak, snap)
*/
#include "utils.hpp"


namespace pm
{
  namespace snap
  {
    bool isInstalled();
    std::vector<std::string> pkgList();
    bool pkgInstalled(std::string pkgName);
  }
  namespace flatpak
  {
    bool isInstalled();
    std::vector<std::string> pkgList();
    bool pkgInstalled(std::string pkgName);
  }
}