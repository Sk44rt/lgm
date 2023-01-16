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

std::string utils::string::rm_dubs(std::string str)
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


std::string utils::string::rm_dubs(std::string str, char dubc)
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


std::vector<std::string> utils::fs::listdir(std::string path)
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

std::string utils::fs::readfile(std::string path)
{
  std::string filecontent;
  std::string buf;
  std::ifstream f (path.c_str());
  while (!f.eof())
  {
    buf = f.get();
    filecontent += buf;
  }
  f.close();

  return filecontent;
}


utils::sys::_which utils::sys::which(std::string bin)
{
  auto status = subprocess::Popen(std::string("which " + bin).c_str(),subprocess::output{subprocess::PIPE});
  if (status.wait() == 0)
  {
    return utils::sys::_which{std::string(status.communicate().first.buf.data()),true};
  } else {
    return utils::sys::_which{"",false};
  }
}


bool utils::regex::match(std::string str, std::string _regex)
{
  return std::regex_match(str.c_str(), std::regex(_regex.c_str()));
}
