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

  void addShip(std::shared_ptr<Ship> ship);
  void createShipsDefault(const std::vector<uint8_t> &sizes = {4, 3, 3, 2, 2, 2,
                                                               1, 1, 1, 1});

  std::shared_ptr<Ship> getShipByCoords(Coordinate coord) noexcept;

  std::vector<std::shared_ptr<Ship>> &getAllShips() noexcept;
};

#endif
