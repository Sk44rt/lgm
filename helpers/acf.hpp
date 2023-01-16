#ifndef ACF_PARSER_HPP_
#define ACF_PARSER_HPP_

#include <fstream>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Acf {
  string data;

public:
  Acf(string data): data(data) {
    cropData();
    toJsonRaw();
    toJson();
  }

  void cropData() {
    std::size_t found = -1;
    string delims = "{}";
    int opened = 0;
    int indexOpen = -1, indexClose = -1;
    while((found = data.find_first_of(delims, found + 1)) != std::string::npos && indexClose == -1)
    {
      char c = data.at(found);

      if (c == '{') {
        opened++;

        if (indexOpen == -1)
          indexOpen = found;
      } else if (c == '}') {
        opened--;

        if (opened == 0) {
          indexClose = found + 1;
        }
      }
    }

    // Get key for table
    found = data.find_last_of("\"", indexOpen);
    found = data.find_last_of("\"", found - 1);
    indexOpen = found;

    data = data.substr(indexOpen, indexClose - indexOpen);
  }

  void toJsonRaw() {
    int indexQuote = 0;
    int index[4];
    int insertCommaNext = -1;
    string delims = "\"{}";
    std::size_t found = data.find_first_of(delims);
    while(found != std::string::npos)
    {
      int inc = 1;
      char c = data.at(found);

      if (c != '"') {
        if (c == '}')
          insertCommaNext = found + 1;
        else if (c == '{') {
          data.insert(index[1] + 1, ":");
          inc++;
        }

        indexQuote = 0;
      } else {
        if (insertCommaNext != -1) {
          data.insert(insertCommaNext, ",");
          inc++;
          insertCommaNext = -1;
        }

        if (indexQuote == 2) { // Join 'key: value'
          data.replace(index[1] + 1, 1, ":");
        } else if (indexQuote == 4) {
          indexQuote = 0;
          data.insert(index[3] + 1, ",");
          inc++;
        }

        index[indexQuote] = found;

        indexQuote++;
      }

      found = data.find_first_of(delims, found + inc);
    }

    data = "{" + data + "}";
  }

  void toJson() {
    json j;
    /*std::string err = json::parse(json, data);
    if (!err.empty())
      std::cerr << err << std::endl;*/
    j = json::parse(data);

    data = j.dump();
  }

  string get() {
    return data;
  }
};

#endif
