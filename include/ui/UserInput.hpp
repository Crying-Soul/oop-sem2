#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <iostream>
#include <string>
#include <utility>

class UserInput {
public:
  bool askUser(const std::string &message);

  std::string askString(const std::string &message);

  std::pair<int, int> askTwoInts(const std::string &message);
};

#endif // USER_INPUT_H
