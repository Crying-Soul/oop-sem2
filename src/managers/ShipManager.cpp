#include "ShipManager.hpp"
#include <iostream>

void ShipManager::addShip(const std::shared_ptr<Ship> &ship) {
  if (ship) {
    ships.push_back(ship);
  } else {
    throw std::invalid_argument("Cannot add a null ship.");
  }
}

void ShipManager::printAllShips() const noexcept {
  for (const auto &ship : ships) {
    ship->printState();
  }
}

void ShipManager::createShipsDefault(const std::vector<uint8_t> &sizes) {
  for (const auto &size : sizes) {
    if (size < 1 || size > 4) {
      throw std::invalid_argument("Invalid ship size in list.");
    }
    addShip(std::make_shared<Ship>(size));
  }
}

std::vector<std::shared_ptr<Ship>> ShipManager::getAllShips() const noexcept {
  return ships;
}

std::shared_ptr<Ship>
ShipManager::getShipByCords(Coordinate cord) const noexcept {
  for (const auto &ship : ships) {
    if (ship->occupiesCoordinate(cord)) {
      return ship;
    }
  }
  return nullptr;
}

std::shared_ptr<Ship> ShipManager::getShipById(uint32_t id) const noexcept {
  for (const auto &ship : ships) {
    if (ship->getId() == id) {
      return ship;
    }
  }
  return nullptr;
}

bool ShipManager::checkHit(Coordinate cord) const noexcept {
  return getShipByCords(cord) != nullptr;
}

void ShipManager::setDamage(Coordinate cord) {
  auto ship = getShipByCords(cord);
  if (!ship) {
    throw std::invalid_argument("Invalid coordinates: no ship at (" +
                                std::to_string(cord.x) + ", " +
                                std::to_string(cord.y) + ")");
  }
  ship->handleAttack(cord);
}

bool ShipManager::attack(Coordinate cord) {
  if (!checkHit(cord)) {
    return false;
  }
  setDamage(cord);
  return true;
}