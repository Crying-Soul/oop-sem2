#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Field.hpp"
#include "Ship.hpp"
#include <memory>
#include <vector>

class ShipManager {
private:
  std::vector<std::shared_ptr<Ship>> ships;
  std::shared_ptr<Field> field;

public:
  
  explicit ShipManager(std::shared_ptr<Field> field);

  
  ShipManager(const ShipManager& other);

  
  ShipManager& operator=(const ShipManager& other);

  
  ShipManager(ShipManager&& other) noexcept;

  
  ShipManager& operator=(ShipManager&& other) noexcept;

  
  ~ShipManager() = default;

  bool placeShip(std::shared_ptr<Ship> ship, Coordinate cord, bool vertical);
  void printAllShips() const;
};

#endif
