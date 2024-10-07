#include "Game.hpp"

int main() {
  const uint8_t rows = 10;
  const uint8_t columns = 10;

  Game game(rows, columns);

  game.setupUserFleet();
  game.setupEnemyFleet();

  for (uint8_t x = 0; x < 5; x++) {
    for (uint8_t y = 0; y < 5; y++) {
      game.attackEnemyField({x, y});
      // game.attackEnemyField({x, y});
    }
  }
  for (uint8_t x = 0; x < 5; x++) {
    for (uint8_t y = 0; y < 5; y++) {
      game.attackUserField({x, y});
      game.attackUserField({x, y});
    }
  }

  game.renderFields();

  return 0;
}