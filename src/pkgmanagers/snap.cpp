#include "pm.hpp"

bool pm::snap::isInstalled()
{
  return utils::sys::which("snapd").exists;
}

std::vector<std::string> pm::snap::pkgList()
{
  if (!isInstalled()) return std::vector<std::string>{};
  printf("checking snap\n");
  return utils::sys::getOutput("snap list | cut -d' ' -f1",0);
}

bool pm::snap::pkgInstalled(std::string pkgName)
{
  if (!isInstalled()) return false;

  return utils::vector::exists(pm::snap::pkgList(), pkgName);
}