#include "abilities/Scanner.hpp"
#include <iostream>

void Scanner::use(Game &game) const {
  std::cout << "Scanner activated! Scanning a 2x2 area for ship segments.\n";
}
std::string Scanner::getName() const { return "Scanner"; }

Ability::AbilityType Scanner::getType() const  {
  return AbilityType::SCANNER;
}