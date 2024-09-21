#include "ShipManager.hpp"
#include <iostream>

ShipManager::ShipManager() : ships() {}

void ShipManager::printAllShips() const {
  for (const auto &ship : ships) {
    ship->printState();
  }
}
