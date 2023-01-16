#include "utils.hpp"

std::vector<std::string> utils::string::split(std::string str, char splitc)
{
  std::vector<std::string> result;
  {
    std::string buf;
    for (char c : str)
    {
      if (c == splitc)
      {
        if (buf.size() > 0) result.push_back(buf);
        buf = "";
      } else {
        buf+=c;
      }
    }
    if (buf.size() > 0) result.push_back(buf);
  }
  return result;
}

std::string utils::string::rmDubs(std::string str)
{
  std::string result;
  {
    char buf = '\0';
    for (char c : str)
    {
      if (c != buf)
      {
        result+=c;
        buf = c;
      }
    }
  }
  return result;
}
std::string utils::string::rmDubs(std::string str, char dubc)
{
  std::string result;
    
  {
    int found = 0;
    for (char c : str)    
    {
      if (c == dubc)
        found++;
      else
        found = 0;

      if (found > 1) continue;

      result+=c;
    }    
  }    
    
  return result;    
}


std::vector<std::string> utils::fs::listDir(std::string path)
{
  std::vector<std::string> lst;
    
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(path.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      std::string name = ent->d_name;
      if (name != "." && name != "..")
        lst.push_back(name);
    }
    closedir(dir);
  }

  return lst;
}

std::string utils::fs::readFile(std::string path)
{
  std::string fileContent;
  std::string buf;
  std::ifstream f (path.c_str());
  while (!f.eof())
  {
    buf = f.get();
    fileContent += buf;
  }
  f.close();

  return fileContent;
}


utils::sys::_which utils::sys::which(std::string bin)
{
  utils::sys::_which w;
  for (std::string binPath : binDirs )
  {
    // for (std::string binFile : utils::fs::listDir(binPath))
    // {
    //   if (binFile == bin)
    //   {
    //     w.path = std::string(binPath+'/'+binFile);
    //     w.exists = true;
    //   }
    // }
  }
  return w;
}


bool utils::regex::match(std::string str, std::string _regex)
{
  return std::regex_match(str.c_str(), std::regex(_regex.c_str()));
}
