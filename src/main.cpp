#include "game/Game.hpp"
#include "ui/CLIParser.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void placeShip(Game &game, uint8_t size, const CLIParser &input) {
  bool placementSuccess = false;
  uint8_t x, y;
  bool isVertical;

  while (!placementSuccess) {
    game.renderUserField();
    std::tie(x, y) =
        input.askTwoInts("Enter coordinates for " + std::to_string(size) +
                         " sized ship (x y): ");
    isVertical = input.askUser("Is the ship vertical? (yes/no)");

    uint8_t adjustedX = static_cast<uint8_t>(x - 1);
    uint8_t adjustedY = static_cast<uint8_t>(y - 1);

    try {
      game.AddUserShipManually(size, {adjustedX, adjustedY}, isVertical);
      placementSuccess = true;
    } catch (const ShipProximityException &e) {
      std::cout << "Error placing ship due to proximity: " << e.what()
                << "\nPlease try again." << std::endl;
    } catch (const ShipPlacementException &e) {
      std::cout << "Error placing ship: " << e.what() << "\nPlease try again."
                << std::endl;
    }
  }
}

void configureGameSettings(CLIParser &input, uint8_t &rows, uint8_t &columns,
                           std::vector<uint8_t> &ships) {
  bool useDefaultPreset = input.askUser("Use default game settings?");
  if (useDefaultPreset) {
    rows = columns = 10;
    ships = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

  } else {
    std::tie(rows, columns) =
        input.askTwoInts("Enter field size (width height): ");
    ships = input.askShipSizes();
  }
}

void handleGameLoop(Game &game, CLIParser &input) {
  while (game.isShipsAlive()) {

    game.displayGameStatus();

    // game.renderFields();
    std::cout << "Choose an action: \n";
    std::cout << "1. Attack the enemy\n";
    std::cout << "2. Use special ability\n";

    uint8_t action = input.askSingleInt("Enter action (1 or 2): ");

    try {
      if (action == 1) {
        uint8_t x, y;
        std::tie(x, y) =
            input.askTwoInts("Enter coordinates for attack (x y): ");

        uint8_t adjustedX = static_cast<uint8_t>(x - 1);
        uint8_t adjustedY = static_cast<uint8_t>(y - 1);
        game.cleanScreen();
        std::cout << "---------- Logs ----------" << std::endl;
        game.attackEnemyField({adjustedX, adjustedY});

      } else if (action == 2) {
        // game.cleanScreen();

        switch (game.getAbilityType()) {
        case Ability::AbilityType::SCANNER:
          uint8_t ability_x, ability_y;
          std::tie(ability_x, ability_y) =
              input.askTwoInts("Enter coordinates for scan (x y): ");

          break;
        
        case Ability::AbilityType::RANDOM_STRIKE:
          /* code */
          break;

        default:
          break;
        }

        game.useAbility();
        std::cout << "Special ability used!" << std::endl;
        continue;

      } else {
        std::cout << "Invalid action! Please choose 1 or 2.\n";
        continue;
      }
    } catch (const AttackException &e) {
      std::cout << "Error in attack coordinates: " << e.what() << std::endl;
      continue;
    }

    std::cout << "Enemy attack!" << std::endl;
    game.enemyAttack(); // ????????? ????? ?????
    std::cout << "--------------------------" << std::endl;

    
    game.renderFields();
  }

  std::cout << "Game End! All ships have been destroyed!" << std::endl;
}

int main() {
  uint8_t rows;
  uint8_t columns;
  std::vector<uint8_t> ships;

  CLIParser input;
  configureGameSettings(input, rows, columns, ships);

  Game game(rows, columns);
  game.renderUserField();

  bool isRandomShips = input.askUser("Do you want to place ships randomly?");
  game.cleanScreen();

  if (!isRandomShips) {
    for (auto size : ships) {
      placeShip(game, size, input);
    }
  }

  game.setupUserFleet(ships);
  game.setupEnemyFleet(ships);
  game.renderFields();

  handleGameLoop(game, input);

  return 0;
}
