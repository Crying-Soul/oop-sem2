#ifndef GAME_HPP
#define GAME_HPP

#include "abilities/AbilityManager.hpp"
#include "game/Field.hpp"
#include "game/ShipManager.hpp"
#include "random/Random.hpp"
#include "ui/UI.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class Game {
private:
  bool gameEnd = false;
  Field userField;
  Field enemyField;
  ShipManager userShipManager;
  ShipManager enemyShipManager;
  AbilityManager abilityManager; // AbilityManager instance
  UI ui;
  Random random;
  bool doubleDamage = false;

public:
  Game(uint8_t rows, uint8_t columns);

  // User Ship Management
  void AddUserShipManually(uint8_t size, Coordinate coord, bool vertical);
  void setupUserFleet(const std::vector<uint8_t> &sizes);
  void setupEnemyFleet(const std::vector<uint8_t> &sizes);

  // Game Logic
  bool isShipsAlive();
  AttackResult enemyAttack();
  void cleanScreen() const;

  void activateDoubleDamage() { doubleDamage = true; }
  void deactivateDoubleDamage() { doubleDamage = false; }

  // Field Rendering
  void displayGameStatus() const;
  void renderUserField() const noexcept;
  void renderFields() const noexcept;

  // Field Accessor
  const Field &getUserField() const noexcept;
  const Field &getEnemyField() const noexcept;

  // Getter method signatures
  const ShipManager &getUserShipManager() const noexcept;
  const ShipManager &getEnemyShipManager() const noexcept;
  const AbilityManager &getAbilityManager() const noexcept;
  const UI &getUI() const noexcept;
  const Random &getRandom() const noexcept;
  bool isDoubleDamage() const noexcept;

  // Attack methods
  AttackResult attackEnemyField(Coordinate coord);
  AttackResult attackUserField(Coordinate coord);

  // Ability Management Methods
  void useAbility();                // Use an available ability
  void getRandomAbility();          // Gain a random ability
  void printAbilitiesCount() const; // Print the count of abilities available
  void printAvailibleAbilities() const; // Print all available abilities

  Ability::AbilityType getAbilityType() const;

  void placeShipsRandomly(Field &field, ShipManager &shipManager);

};

#endif // GAME_HPP
