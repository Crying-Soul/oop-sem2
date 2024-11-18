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
      continue; // Skip if the ship is invalid
    }

    Coordinate coord;
    bool placed = false;

    while (!placed) { // limit attempts to avoid infinite loop
      coord.x = random.getRandomValue<uint8_t>(0, field.getColumns() - 1);
      coord.y = random.getRandomValue<uint8_t>(0, field.getRows() - 1);
      bool vertical =
          random.getRandomBool(); // Randomly choose vertical placement

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
    AttackResult result = enemyField.attack(coord);
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

void Game::useAbility() { abilityManager.useAbility(*this); }

void Game::getRandomAbility() { abilityManager.getRandomAbility(); }

void Game::printAbilitiesCount() const { abilityManager.printAbilitiesCount(); }

void Game::printAvailibleAbilities() const { abilityManager.printAvailible(); }

Ability::AbilityType Game::getAbilityType() const {
  return abilityManager.getAbilityType();
}

void Game::displayGameStatus() const {
  std::cout << "------ Game Status ------" << std::endl;

  // auto &userShips = userShipManager.getAllShips();
  // std::cout << "User's Ships: " << std::endl;
  // if (userShips.empty()) {
  //   std::cout << "No ships in the fleet!" << std::endl;
  // } else {
  //   for (const auto &ship : userShips) {
  //     std::cout << "- Ship of size " << ship->getSize() << " is "
  //               << (ship->isShipDestroyed() ? "destroyed" : "alive")
  //               << std::endl;
  //   }
  // }

  // auto &enemyShips = enemyShipManager.getAllShips();
  // std::cout << "Enemy's Ships: " << std::endl;
  // if (enemyShips.empty()) {
  //   std::cout << "No ships in the enemy fleet!" << std::endl;
  // } else {
  //   for (const auto &ship : enemyShips) {
  //     std::cout << "- Ship of size " << ship->getSize() << " is "
  //               << (ship->isShipDestroyed() ? "destroyed" : "alive")
  //               << std::endl;
  //   }
  // }

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
