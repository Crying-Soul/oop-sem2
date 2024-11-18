#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "game/Ship.hpp"
#include <memory>
#include <vector>

class ShipManager {
private:
  std::vector<std::shared_ptr<Ship>> ships;

public:
  ShipManager() : ships() {};

  void addShip(std::shared_ptr<Ship> ship);
  std::shared_ptr<Ship> createShip(uint8_t size);
  void createFleet(const std::vector<uint8_t> &sizes );

  std::shared_ptr<Ship> getShipByCoords(Coordinate coord) noexcept;

  std::vector<std::shared_ptr<Ship>> &getAllShips() noexcept;
};

#endif
