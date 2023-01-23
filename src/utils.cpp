#include "utils.hpp"

// string utilities
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

std::string utils::string::strip(std::string str)
{
  return strip(str, ' ');
}
std::string utils::string::strip(std::string str, char _char)
{
  if (str.size() == 0) return str;
  std::string result = str;
  while (result[0]==_char||result[result.size()-1]==_char)
  {
    if (result[0]==_char) result.erase(result.begin());
    if (result[result.size()-1]==_char) result.erase(result.begin()+(result.size()-1));
  }
  return result;
}

int utils::string::getDigits(std::string str)
{
  std::string digit;
  for (char c : str)
    if (std::string("1234567890").find(c) != std::string::npos)
      digit.push_back(c);
  return std::stoi(digit);
}

std::string utils::string::removeDublicates(std::string str)
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
std::string utils::string::removeDublicates(std::string str, char dubc)
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

std::string utils::string::remove(std::string str, char _char)
{
  std::string result;
  for (char c : str)
  {
    if (c == _char) continue;
    result += c;
  }
  return result;
}

std::string utils::string::join(std::vector<std::string> strs, char joinChar, bool removeFirst)
{
  std::string result;
  for (std::string str : strs)
  {
    str = utils::string::strip(
            utils::string::removeDublicates(
              utils::string::remove(str, ' '),
              joinChar),
            joinChar
          );
    if(str[0]!=joinChar&&result[result.size()-1]!=joinChar)result+=joinChar;
    result+=str;
    if(str[str.size()-1]!=joinChar)result+=joinChar;
  }
  { // remove first and last characters
    if (removeFirst) result.erase(result.begin());
    result.erase(result.begin() + result.size() - 1);
  }
  return result;
}


// fs (file system) utilities
std::string utils::fs::joinPath(std::vector<std::string> v)
{
  return utils::string::join(v, '/', false);
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


// system utilities
utils::sys::_which utils::sys::which(std::string bin)
{
  utils::sys::_which w;
  for (std::string binPath : binDirs )
  {
    auto x = utils::fs::listDir(binPath);
    if (std::find(x.begin(),x.end(),bin) != x.end())
    {
      w.path = std::string(binPath+"/"+bin);
      w.exists = true;

      return w;
    }
  }
  return w;
}

std::vector<std::string> utils::sys::getOutput(std::string cmd, int cuttedLines)
{
  std::vector<std::string> result = utils::string::split(
    std::string(
      subprocess::Popen(cmd, subprocess::output{subprocess::PIPE}).communicate().first.buf.data()
    ),
    '\n'
  );

  if (cuttedLines > 0) result.erase(result.begin(),result.begin()+cuttedLines);

  return result;
}

std::string utils::sys::getEnv(std::string var)
{
  // get environment variable
  return std::string(std::getenv(var.c_str()));
}


bool utils::regex::match(std::string str, std::string _regex)
{
  return std::regex_match(str.c_str(), std::regex(_regex.c_str()));
}
