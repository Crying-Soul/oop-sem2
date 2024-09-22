#include "ShipManager.hpp"
#include <iostream>

ShipManager::ShipManager() : ships() {}

void ShipManager::addShip(const std::shared_ptr<Ship> &ship) {
  ships.push_back(ship);
}

void ShipManager::printAllShips() const {
  for (const auto &ship : ships) {
    ship->printState();
  }
}
void ShipManager::createShipsDefault(const std::vector<uint8_t> &sizes) {
  for (const auto &size : sizes) {
    addShip(std::make_shared<Ship>(size));
  }
}
std::vector<std::shared_ptr<Ship>> ShipManager::getAllShips() const {
  return ships;
}

std::shared_ptr<Ship> ShipManager::getShipByCords(Coordinate cord) const {
  for (const auto &ship : ships) {
    if (ship->occupiesCoordinate(cord)) {
      return ship;
    }
  }
  return nullptr;
}



std::shared_ptr<Ship> ShipManager::getShipById(uint32_t id) const {
  for (const auto &ship : ships) {
    if (ship->getId() == id) {
      return ship;
    }
  }
  return nullptr;
}

  bool ShipManager::checkHit(Coordinate cord){
    return getShipByCords(cord) != nullptr ? true : false;
  };

  void ShipManager::setDamage(Coordinate cord){
    auto ship = getShipByCords(cord);
    if (!ship)
    {
      std::invalid_argument("Invalid coordinates");
      return;
    }

    ship->handleAttack(cord);
    
  };

  bool ShipManager::attack(Coordinate cord){
    if(!checkHit(cord)){
      return false;
    }
    setDamage(cord);
    return true;
  }