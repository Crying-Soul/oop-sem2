#include "Game.hpp"

Game::Game(uint8_t rows, uint8_t columns)
    : userField(Field(rows, columns)),
      enemyField(Field(rows, columns)), userShipManager(),
      enemyShipManager(), ui() {}

void Game::setupUserFleet(const std::vector<uint8_t> &shipSizes) {
  userShipManager.createShipsDefault(shipSizes);
  auto fleet = userShipManager.getAllShips();

  for (const auto &ship : fleet) {
    userField.placeShipByRandCoords(ship);
  }
}

void Game::setupEnemyFleet(const std::vector<uint8_t> &shipSizes) {
  enemyShipManager.createShipsDefault(shipSizes);
  auto fleet = enemyShipManager.getAllShips();

  for (const auto &ship : fleet) {
    enemyField.placeShipByRandCoords(ship);
  }
}

void Game::renderFields() const noexcept {
  ui.fieldsRender(userField, enemyField);
}

const Field &Game::getUserField() const noexcept { return userField; }

const Field &Game::getEnemyField() const noexcept { return enemyField; }

void Game::attackEnemyField(Coordinate coord) {
    AttackResult result = enemyField.attack(coord);
   
    ui.displayAttackResult(result, coord); 
}

void Game::attackUserField(Coordinate coord) {
    AttackResult result = userField.attack(coord);
    
    ui.displayAttackResult(result, coord); 

}