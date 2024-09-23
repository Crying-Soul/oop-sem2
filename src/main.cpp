#include "Field.hpp"
#include "ShipManager.hpp"

int main() {
  Field userField(10, 10);
  Field enemyField{userField};

  ShipManager userManager;
  ShipManager enemyManager;
  userManager.createShipsDefault();

  auto userFleet = userManager.getAllShips();

  for (const auto &ship : userFleet) {
    userField.placeShipByRandCoords(ship);
  }
  enemyManager.createShipsDefault();
  auto enemyFleet = enemyManager.getAllShips();
  for (const auto &ship : enemyFleet) {
    enemyField.placeShipByRandCoords(ship);
  }

  userField.display();
  enemyField.display(false);


  return 0;
}
