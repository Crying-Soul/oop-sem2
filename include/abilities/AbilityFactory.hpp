#ifndef ABILITYFACTORY_H
#define ABILITYFACTORY_H

#include "abilities/Ability.hpp"
#include <stdexcept>
class AbilityFactory {
public:
  static Ability *createAbility(Ability::AbilityType type);
  static Ability *createRandomAbility();
};

#endif // ABILITYFACTORY_H
