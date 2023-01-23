#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "includes.hpp"
#include "subprocess.hpp"

#define MKDIR_PATH_EXISTS -1


/*
  used in utils::sys::which()
  i took this array from whereis util source code
  see: https://github.com/util-linux/util-linux/blob/master/misc-utils/whereis.c
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
    std::string strip(std::string str);
    std::string strip(std::string str, char _char);
    int getDigits(std::string str);
    std::string removeDublicates(std::string str);
    std::string removeDublicates(std::string str, char dubc);
    std::string remove(std::string str, char _char);
    std::string join(std::vector<std::string> strs, char joinChar, bool removeFirst);
  }
  namespace vector
  {
    template <class T> bool exists(std::vector<T> array, T element) { return std::find(array.begin(),array.end(),element) != array.end(); }
  }
  namespace fs
  {
    std::string joinPath(std::vector<std::string> v);
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
    std::vector<std::string> getOutput(std::string cmd, int cuttedLines); // cuttedLines is value for return command output without n first lines
    std::string getEnv(std::string var);
  }
  namespace regex
  {
    bool match(std::string str, std::string _regex);
  }
}

#endif
