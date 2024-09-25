#include "ShipManager.hpp"
#include <iostream>

ShipManager::ShipManager(const std::vector<uint8_t> &sizes) : ships() {
  createFleet(sizes);
}

void ShipManager::createFleet(const std::vector<uint8_t> &sizes) {
  for (const auto &size : sizes) {
    if (size < 1 || size > 4) {
      throw std::invalid_argument("Invalid ship size in list.");
    }
    addShip(std::make_shared<Ship>(size));
  }
}

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


std::vector<std::shared_ptr<Ship>> ShipManager::getAllShips() const noexcept {
  return ships;
}

std::shared_ptr<Ship>
ShipManager::getShipByCoords(Coordinate coord) const noexcept {
  for (const auto &ship : ships) {
    if (ship->occupiesCoordinate(coord)) {
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

bool ShipManager::checkHit(Coordinate coord) const noexcept {
  return getShipByCoords(coord) != nullptr;
}

void ShipManager::setDamage(Coordinate coord) {
  auto ship = getShipByCoords(coord);
  if (!ship) {
    throw std::invalid_argument("Invalid coordinates: no ship at (" +
                                std::to_string(coord.x) + ", " +
                                std::to_string(coord.y) + ")");
  }
  ship->handleAttack(coord);
}

SegmentStatus ShipManager::attack(Coordinate coord) {
    auto ship = getShipByCoords(coord);
    if (!ship) {
        return SegmentStatus::Intact; 
    }
    ship->handleAttack(coord);
    return ship->getSegmentStatusAt(coord);
}