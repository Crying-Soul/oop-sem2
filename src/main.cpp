#include "Field.hpp"
#include "ShipManager.hpp"

int main() {
  auto GameField = std::make_shared<Field>(10, 10);
  GameField->create();

  ShipManager manager;

  manager.createShipsDefault();

  auto ships = manager.getAllShips();
  auto ship = ships[0];
  GameField->placeShipByCords(ship, {0, 0});

  // for (const auto &ship : ships) {
  //   GameField->placeShipByRandCords(ship);
  // }

  // GameField->display();
  GameField->attack({0, 0});
  manager.attack({0, 0});
  GameField->attack({0, 0});
  manager.attack({0,0});
  // GameField->attack({0, 2});
  // GameField->attack({0, 3});

  GameField->display();

  ship->printState();

  // manager.printAllShips();
  return 0;
}
