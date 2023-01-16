#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <vector>
#include <dirent.h>
#include <regex>
#include <fstream>
#include <sys/stat.h>

#include "subprocess.hpp"

#define MKDIR_PATH_EXISTS -1

namespace utils
{
  namespace string
  {
    std::vector<std::string> split(std::string str, char splitc);
    std::string rm_dubs(std::string str);
    std::string rm_dubs(std::string str, char dubc);
  }
  namespace fs
  {
    std::vector<std::string> listdir(std::string path);
    std::string readfile(std::string path);
  }
  namespace sys
  {
    struct _which
    {
      std::string path;
      bool exists;
    };
    utils::sys::_which which(std::string bin);
  }
  namespace regex
  {
    bool match(std::string str, std::string _regex);
  }
}

#endif
