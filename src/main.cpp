#include "Field.hpp"
#include "ShipManager.hpp"

int main() {
  Field gameField(10, 10);

  ShipManager manager;

  manager.createShipsDefault();

  auto fleet = manager.getAllShips();

  for (const auto &ship : fleet) {
    gameField.placeShipByRandCoords(ship);
  }

  gameField.display();

  return 0;
}
