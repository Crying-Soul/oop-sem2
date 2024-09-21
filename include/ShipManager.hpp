#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Field.hpp"
#include "Ship.hpp"
#include <algorithm>
#include <vector>

class ShipManager {
private:
  std::vector<std::shared_ptr<Ship>> ships;

public:
  ShipManager();

  ~ShipManager() = default;

  void printAllShips() const;
};

#endif
