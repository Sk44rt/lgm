#include "pm.hpp"

bool pm::flatpak::isInstalled()
{
  return utils::sys::which("flatpak").exists;
}

std::vector<std::string> pm::flatpak::pkgList()
{
  if (!isInstalled()) return std::vector<std::string>{};
  printf("checking flatpak\n");
  return utils::sys::getOutput("flatpak list --columns=application",0);
}

bool pm::flatpak::pkgInstalled(std::string pkgName)
{
  if (!isInstalled()) return false;

  return utils::vector::exists(pm::flatpak::pkgList(), pkgName);
}