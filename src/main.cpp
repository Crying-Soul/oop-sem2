#include "Field.hpp"
#include "Ship.hpp"
#include "ShipManager.hpp"
#include <memory>

int main() {
  auto field1 = std::make_shared<Field>(10, 15);
  field1->create();

  auto s1 = std::make_shared<Ship>(4);
  auto s2 = std::make_shared<Ship>(3);

  field1->placeShip(s1, {0, 2}, true);
  field1->placeShip(s2, {3, 4}, false);

  field1->display();

  return 0;
}
