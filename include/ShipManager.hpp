#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Field.hpp"
#include "Ship.hpp"


class ShipManager {
private:
  std::vector<std::shared_ptr<Ship>> ships;

public:
  ShipManager();

  void addShip(const std::shared_ptr<Ship>& ship);

  void printAllShips() const;
};

#endif
