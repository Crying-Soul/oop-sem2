#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Ship.hpp"
#include <memory>
#include <vector>

class ShipManager {
private:
  std::vector<std::shared_ptr<Ship>> ships;

public:
  ShipManager() : ships() {};

  void addShip(const std::shared_ptr<Ship> &ship);
  void printAllShips() const noexcept;
  void createShipsDefault(const std::vector<uint8_t> &sizes = {4, 3, 3, 2, 2, 2,
                                                               1, 1, 1, 1});

  bool checkHit(Coordinate coord) const noexcept;
  void setDamage(Coordinate coord);
  bool attack(Coordinate coord);

  std::shared_ptr<Ship> getShipByCoords(Coordinate coord) const noexcept;
  std::shared_ptr<Ship> getShipById(uint32_t id) const noexcept;

  std::vector<std::shared_ptr<Ship>> getAllShips() const noexcept;
};

#endif