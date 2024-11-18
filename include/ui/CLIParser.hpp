#ifndef USER_INPUT_H
#define USER_INPUT_H


#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <limits>

class CLIParser {
public:
 
  bool askUser(const std::string &message) const;

  std::string askString(const std::string &message) const;

  std::pair<int, int> askTwoInts(const std::string &message) const;

  std::vector<uint8_t> askShipSizes() const;

  int askSingleInt(const std::string &prompt) const;
};

#endif // USER_INPUT_H
