#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "abilities/Ability.hpp"        // Include Ability before anything else
#include "abilities/AbilityFactory.hpp"
#include "exceptions/AbilityExceptions.hpp"
#include <queue>
#include <iostream>

class AbilityManager {
private:
  std::queue<Ability *> abilities;

public:
  AbilityManager();
  ~AbilityManager();
  void useAbility(Game &game);
  void getRandomAbility();
  void printAbilitiesCount() const;
  void printAvailible() const;
  Ability::AbilityType getAbilityType() const;
};

#endif // ABILITYMANAGER_H
