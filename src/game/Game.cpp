#include "game/Game.hpp"
#include "random/Random.hpp"

Game::Game(uint8_t rows, uint8_t columns)
    : userField(Field(rows, columns)), enemyField(Field(rows, columns)),
      userShipManager(), enemyShipManager(), abilityManager(), ui(), random() {}

void Game::AddUserShipManually(uint8_t size, Coordinate coord, bool vertical) {
  auto ship = userShipManager.createShip(size);
  userField.placeShipByCoords(ship, coord, vertical);
}

void Game::setupUserFleet(const std::vector<uint8_t> &shipSizes) {
  userShipManager.createFleet(shipSizes);
  placeShipsRandomly(userField, userShipManager);
}

void Game::setupEnemyFleet(const std::vector<uint8_t> &shipSizes) {
  enemyShipManager.createFleet(shipSizes);
  placeShipsRandomly(enemyField, enemyShipManager);
}

void Game::placeShipsRandomly(Field &field, ShipManager &shipManager) {
  auto fleet = shipManager.getAllShips();

  for (const auto &ship : fleet) {
    if (!ship) {
      continue;
    }

    Coordinate coord;
    bool placed = false;

    while (!placed) {
      coord.x = random.getRandomValue<uint8_t>(0, field.getColumns() - 1);
      coord.y = random.getRandomValue<uint8_t>(0, field.getRows() - 1);
      bool vertical = random.getRandomBool();

      try {
        if (field.isPlaceAvailable(ship, coord, vertical)) {
          placed = field.placeShipByCoords(ship, coord, vertical);
        }
      } catch (const ShipProximityException &e) {

      } catch (const ShipPlacementException &e) {
      }
    }
  }
}

void Game::renderFields() const noexcept {
  ui.fieldsRender(userField, enemyField);
}
void Game::renderUserField() const noexcept {
  ui.renderField(userField, false, true);
}

const Field &Game::getUserField() const noexcept { return userField; }

const Field &Game::getEnemyField() const noexcept { return enemyField; }

AttackResult Game::attackEnemyField(Coordinate coord) {

  AttackResult result = enemyField.attack(coord);

  if (doubleDamage) {

    result = enemyField.attack(coord);
  }

  if (result == AttackResult::ShipDestroyed) {
    getRandomAbility();
  }

  ui.displayAttackResult(result, coord);

  deactivateDoubleDamage();

  return result;
}
AttackResult Game::attackUserField(Coordinate coord) {
  AttackResult result = userField.attack(coord);
  ui.displayAttackResult(result, coord);
  return result;
}

AttackResult Game::enemyAttack() {
  Coordinate coord;

  coord.x = random.getRandomValue<uint8_t>(0, enemyField.getColumns() - 1);
  coord.y = random.getRandomValue<uint8_t>(0, enemyField.getRows() - 1);

  return attackUserField(coord);
}

bool Game::isShipsAlive() {
  auto userShips = userShipManager.getAllShips();
  bool userShipsAlive =
      std::any_of(userShips.begin(), userShips.end(),
                  [](const auto &ship) { return !ship->isShipDestroyed(); });

  if (!userShipsAlive) {
    return false;
  }

  auto enemyShips = enemyShipManager.getAllShips();
  bool enemyShipsAlive =
      std::any_of(enemyShips.begin(), enemyShips.end(),
                  [](const auto &ship) { return !ship->isShipDestroyed(); });

  return enemyShipsAlive;
}

void Game::cleanScreen() const {
  int result = system("clear");
  if (result != 0) {
    std::cerr << "Error clearing the screen!" << std::endl;
  }
}

void Game::useAbility(Coordinate coordinate) {
  abilityManager.useAbility(*this, coordinate);
}

void Game::getRandomAbility() { abilityManager.getRandomAbility(); }

void Game::printAbilitiesCount() const { abilityManager.printAbilitiesCount(); }

void Game::printAvailibleAbilities() const { abilityManager.printAvailible(); }

Ability::AbilityType Game::getAbilityType() const {
  return abilityManager.getAbilityType();
}

void Game::displayGameStatus() const {
  std::cout << "------ Game Status ------" << std::endl;

  std::cout << "Abilities queue: " << std::endl;
  printAvailibleAbilities();
  std::cout << "--------------------------" << std::endl;
}

const ShipManager &Game::getUserShipManager() const noexcept {
  return userShipManager;
}

const ShipManager &Game::getEnemyShipManager() const noexcept {
  return enemyShipManager;
}

const AbilityManager &Game::getAbilityManager() const noexcept {
  return abilityManager;
}

const UI &Game::getUI() const noexcept { return ui; }

const Random &Game::getRandom() const noexcept { return random; }

bool Game::isDoubleDamage() const noexcept { return doubleDamage; }

void Game::placeShipsManually(const std::vector<uint8_t> &ships,
                              CLIParser &input) {
  for (auto size : ships) {
    bool placementSuccess = false;
    uint8_t x, y;
    bool isVertical;

    while (!placementSuccess) {

      renderUserField();
      std::tie(x, y) =
          input.askTwoInts("Enter coordinates for " + std::to_string(size) +
                           " sized ship (x y): ");

      isVertical = input.askUser("Is the ship vertical? (yes/no)");
      cleanScreen();
      uint8_t adjustedX = static_cast<uint8_t>(x - 1);
      uint8_t adjustedY = static_cast<uint8_t>(y - 1);

      try {
        AddUserShipManually(size, {adjustedX, adjustedY}, isVertical);
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
}

void Game::runGameLoop(CLIParser &input) {
  while (isShipsAlive()) {
    displayGameStatus();

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

        cleanScreen();
        std::cout << "---------- Logs ----------" << std::endl;

        attackEnemyField({adjustedX, adjustedY});
      } else if (action == 2) {
        Coordinate abilityCoord;

        uint8_t abilityCoordX = 0, abilityCoordY = 0;
        try {
          if (getAbilityType() == Ability::AbilityType::SCANNER) {
            std::tie(abilityCoordX, abilityCoordY) =
                input.askTwoInts("Enter coordinates for scan (x y): ");
          }

          abilityCoord.x = abilityCoordY - 1;
          abilityCoord.y = abilityCoordX - 1;
          cleanScreen();

          useAbility(abilityCoord);
          renderFields();
          std::cout << "Special ability used!" << std::endl;
        } catch (const AbilityException &e) {
          std::cout << "Error in ability usage: " << e.what() << std::endl;
        }

        continue;
      } else {
        std::cout << "Invalid action! Please choose 1 or 2.\n";
        continue;
      }
    } catch (const AttackException &e) {
      std::cout << "Error in attack coordinates: " << e.what() << std::endl;
      continue;
    } catch (const std::exception &e) {
      std::cout << "An unexpected error occurred: " << e.what() << std::endl;
      continue;
    }

    std::cout << "Enemy attack!" << std::endl;
    enemyAttack();
    std::cout << "--------------------------" << std::endl;

    renderFields();
  }

  std::cout << "Game Over! All ships have been destroyed!" << std::endl;
}