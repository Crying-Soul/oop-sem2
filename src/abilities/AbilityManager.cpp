#include "abilities/AbilityManager.hpp"

AbilityManager::AbilityManager() : abilities() {

  abilities.push(AbilityFactory::createRandomAbility());
}

// AbilityManager::~AbilityManager() {

//   while (!abilities.empty()) {
//     delete abilities.front();
//     abilities.pop();
//   }
// }

Ability::AbilityType AbilityManager::getAbilityType() const {
  if (abilities.empty()) {
    throw AbilityException("No abilities available to determine type.");
  }
  return abilities.front()->getType();
}

void AbilityManager::useAbility(Game &game, Coordinate coord) {
  if (abilities.empty()) {
    throw AbilityException("Empty ability queue");
  }

  Ability *ability = abilities.front();
  ability->use(game, coord);
  abilities.pop();
  delete ability;
}

void AbilityManager::getRandomAbility() {

  abilities.push(AbilityFactory::createRandomAbility());
  std::cout << "You have gained a new random ability!\n";
}

void AbilityManager::printAbilitiesCount() const {
  std::cout << "Abilities available: " << abilities.size() << "\n";
}

void AbilityManager::printAvailible() const {
  if (abilities.empty()) {
    std::cout << "No abilities available.\n";
    return;
  }

  std::queue<Ability *> tempAbilities = abilities;
  int index = 1;
  while (!tempAbilities.empty()) {
    Ability *ability = tempAbilities.front();
    std::cout << index++ << ". " << ability->getName() << "\n";
    tempAbilities.pop();
  }
}
AbilityManager::~AbilityManager() {
    while (!abilities.empty()) {
        if (abilities.front() != nullptr) {
            delete abilities.front();
        }
        abilities.pop();
    }
}
