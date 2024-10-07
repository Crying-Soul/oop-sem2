#include "ShipManager.hpp"
#include <iostream>

void ShipManager::addShip(std::shared_ptr<Ship> ship) {
  if (ship) {
    ships.push_back(ship);
  } else {
    throw std::invalid_argument("Cannot add a null ship.");
  }
}

std::vector<std::shared_ptr<Ship>> &ShipManager::getAllShips() noexcept {
  return ships;
}

void ShipManager::createShipsDefault(const std::vector<uint8_t> &sizes) {
  for (const auto &size : sizes) {
    if (size < 1 || size > 4) {
      throw std::invalid_argument("Invalid ship size in list.");
    }
    auto ship = std::make_shared<Ship>(size);
    ship->initializeSegments();
    addShip(ship);
  }
}

std::shared_ptr<Ship> ShipManager::getShipByCoords(Coordinate coord) noexcept {
  for (const auto &ship : ships) {
    if (ship->occupiesCoordinate(coord)) {
      return ship;
    }
  }
  return nullptr;
}