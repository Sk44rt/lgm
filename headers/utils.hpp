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


/*
  used in utils::sys::which()
  i took this list from whereis util source code
  see: https://github.com/util-linux/util-linux/
  whereis source: https://github.com/util-linux/util-linux/blob/master/misc-utils/whereis.c
*/
const std::vector<std::string> binDirs = {
  "/usr/bin",
  "/usr/sbin",
  "/bin",
  "/sbin",
  "/usr/lib",
  "/usr/lib32",
  "/usr/lib64",
  "/etc",
  "/usr/etc",
  "/lib",
  "/lib32",
  "/lib64",
  "/usr/games",
  "/usr/games/bin",
  "/usr/games/lib",
  "/usr/emacs/etc",
  "/usr/lib/emacs/*/etc",
  "/usr/TeX/bin",
  "/usr/tex/bin",
  "/usr/interviews/bin/LINUX",
  "/usr/X11R6/bin",
  "/usr/X386/bin",
  "/usr/bin/X11",
  "/usr/X11/bin",
  "/usr/X11R5/bin",
  "/usr/local/bin",
  "/usr/local/sbin",
  "/usr/local/etc",
  "/usr/local/lib",
  "/usr/local/games",
  "/usr/local/games/bin",
  "/usr/local/emacs/etc",
  "/usr/local/TeX/bin",
  "/usr/local/tex/bin",
  "/usr/local/bin/X11",
  "/usr/contrib",
  "/usr/hosts",
  "/usr/include",
  "/usr/g++-include",
  "/usr/ucb",
  "/usr/old",
  "/usr/new",
  "/usr/local",
  "/usr/libexec",
  "/usr/share",
};


namespace utils
{
  namespace string
  {
    std::vector<std::string> split(std::string str, char splitc);
    std::string rmDubs(std::string str);
    std::string rmDubs(std::string str, char dubc);
  }
  namespace vector
  {
  }
  namespace fs
  {
    std::vector<std::string> listDir(std::string path);
    std::string readFile(std::string path);
  }
  namespace sys
  {
    struct _which
    {
      std::string path = "";
      bool exists = false;
    };
    utils::sys::_which which(std::string bin);
  }
  namespace regex
  {
    bool match(std::string str, std::string _regex);
  }
}

#endif
