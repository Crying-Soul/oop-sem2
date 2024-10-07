#ifndef GAME_HPP
#define GAME_HPP

#include "Field.hpp"
#include "ShipManager.hpp"
#include "UI.hpp"
#include <memory>
#include <vector>

class Game {
private:
  std::shared_ptr<Field> userField;
  std::shared_ptr<Field> enemyField;
  ShipManager userShipManager;
  ShipManager enemyShipManager;
  UI ui;

public:
  Game(uint8_t rows, uint8_t columns);

  void setupUserFleet(const std::vector<uint8_t> &sizes = {4, 3, 3, 2, 2, 2, 1,
                                                           1, 1, 1});
  void setupEnemyFleet(const std::vector<uint8_t> &sizes = {4, 3, 3, 2, 2, 2, 1,
                                                            1, 1, 1});

  void renderFields() const noexcept;

  const Field &getUserField() const noexcept;
  const Field &getEnemyField() const noexcept;

  // Attack methods
  AttackResult attackEnemyField(Coordinate coord);
  AttackResult attackUserField(Coordinate coord);
};

#endif // GAME_HPP
