#include "Field.hpp"
#include "Ship.hpp"
#include "ShipManager.hpp"
#include <memory>

int main() {
  auto field1 = std::make_shared<Field>(10, 10);
  field1->create();
  field1->display();

  auto s1 = std::make_shared<Ship>(4);
  // auto s2 = std::make_shared<Ship>(4);

  s1->printState();
  

  // ShipManager s_manager(field1);
  // s_manager.placeShip(s2, {5, 5}, false);
  // s_manager.placeShip(s1, {2, 2}, true);
  // s_manager.placeShip(s1, {6, 3}, false);
  // s_manager.placeShip(s1, {8, 1}, true);

  return 0;
}
