#include "Field.hpp"
#include "ShipManager.hpp"


int main() {
  auto GameField = std::make_shared<Field>(10, 10);
  GameField->create();

  auto ships = {
      std::make_shared<Ship>(4), 
      std::make_shared<Ship>(3), 
      std::make_shared<Ship>(3), 
      std::make_shared<Ship>(2),
      std::make_shared<Ship>(2),
      std::make_shared<Ship>(2),
      std::make_shared<Ship>(1),
      std::make_shared<Ship>(1),
      std::make_shared<Ship>(1), 
      std::make_shared<Ship>(1) 
  };

  ShipManager manager;

  for (const auto &ship : ships) {
    manager.addShip(ship);
    GameField->placeShipByRandCords(ship);
  }

  GameField->display();
  manager.printAllShips();
  return 0;
}
