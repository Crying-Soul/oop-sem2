#ifndef GAME_HPP
#define GAME_HPP
#include "Field.hpp"
#include "ShipManager.hpp"
class Game {
private:
  ShipManager userManager;
  ShipManager enemyManager;

  Field userField;
  Field enemyField;

public:
  Game();
  void createMap(uint8_t rowsCount, uint8_t columnsCount) noexcept;
  void createFleet(const std::vector<uint8_t> &sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1,
                                                   1});
    void display() const noexcept;
    void update() const noexcept;
    void userAttack(Coordinate coords);
    void enemyAttack(Coordinate coords);
};

#endif
