#include "Field.hpp"
#include "ShipManager.hpp"
#include <memory>

int main() {
  auto field1 = std::make_shared<Field>(10, 10);
  field1->create();

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

  for (const auto &ship : ships) {
    field1->setRandom(ship);
  }

  field1->display();

  return 0;
}
