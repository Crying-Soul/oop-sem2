#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

#include "abilities/Ability.hpp"
#include "game/Game.hpp" 
#include <iostream>
class DoubleDamage : public Ability {
public:
  void use(Game &game) const override;

  std::string getName() const override;

  Ability::AbilityType getType() const override;
};

#endif // DOUBLEDAMAGE_H
