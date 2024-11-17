#include "game/Game.hpp"
#include "ui/UserInput.hpp"

int main() {

  // UserInput input;
  // std::string playerName = input.getPlayerName();
  // std::cout << "Welcome, " << playerName << "!\n";

  // bool useDeafultPreset = input.askUser("Use default game settings?");

  // if (useDeafultPreset) {
  //   Game game(10, 10);
  //   game.setupUserFleet();
  //   game.setupEnemyFleet();
  //    game.renderFields();
  // }
  // else
  // {
  //   //ask settings
  // }
  
  
  
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

  // game.renderFields();

  return 0;
}