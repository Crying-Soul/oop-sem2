#include "abilities/DoubleDamage.hpp"

void DoubleDamage::use(Game &game) const {

  std::cout << "Double damage activated!" << std::endl;
  game.activateDoubleDamage();
}

std::string DoubleDamage::getName() const { return "Double Damage"; }

Ability::AbilityType DoubleDamage::getType() const {
  return AbilityType::DOUBLE_DAMAGE;
}
