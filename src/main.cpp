#include "game/Game.hpp"
#include "ui/CLIParser.hpp"

int main() {
  CLIParser input;

  uint8_t rows, columns;
  std::vector<uint8_t> ships;

  bool useDefaultPreset = input.askUser("Use default game settings?");

  if (useDefaultPreset) {
    rows = columns = 10;
    ships = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
  } else {
    std::tie(rows, columns) =
        input.askTwoInts("Enter field size (width height): ");
    ships = input.askShipSizes();
  }

  Game game(rows, columns);
  game.renderUserField();
  bool isRandomShips = input.askUser("Do you want to place ships randomly?");
  game.cleanScreen();

  if (!isRandomShips) {
    game.placeShipsManually(ships, input);
  }
  game.setupUserFleet(ships);
  game.setupEnemyFleet(ships);

  game.renderFields();
  game.runGameLoop(input);

  return 0;
}
