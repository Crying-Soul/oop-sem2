#include "Field.hpp"
#include "ShipManager.hpp"

int main() {
  Field gameField(10, 10);

  gameField.create();

  ShipManager manager;

  manager.createShipsDefault();

  auto fleet = manager.getAllShips();
 

  for (const auto &ship : fleet) {
    gameField.placeShipByRandCords(ship);
  }

  gameField.display();


  return 0;
}
