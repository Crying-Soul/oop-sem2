#include "ShipManager.hpp"
#include <iostream>

ShipManager::ShipManager() : ships() {}

void ShipManager::addShip(const std::shared_ptr<Ship>& ship){
  ships.push_back(ship);
}

void ShipManager::printAllShips() const {
  for (const auto &ship : ships) {
    ship->printState();
  }
}
