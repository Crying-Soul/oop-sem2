#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Field.hpp"
#include "Ship.hpp"

class ShipManager {
private:
  std::vector<std::shared_ptr<Ship>> ships;

public:
  ShipManager();

  void addShip(const std::shared_ptr<Ship> &ship);

  void printAllShips() const;

  void createShipsDefault(const std::vector<uint8_t> &sizes = {4, 3, 3, 2, 2, 2,
                                                               1, 1, 1, 1});

  bool checkHit(Coordinate cord);

  void setDamage(Coordinate cord);

  bool attack(Coordinate cord);

  std::shared_ptr<Ship> getShipByCords(Coordinate cord) const;
  std::shared_ptr<Ship> getShipById(uint32_t id) const;

  std::vector<std::shared_ptr<Ship>> getAllShips() const;
};

#endif
