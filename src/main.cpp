#include "Field.hpp"
#include "ShipManager.hpp"
#include "Ship.hpp"
#include <memory>

int main() {
    auto field1 = std::make_shared<Field>(10, 10);  
    field1->create();
    field1->display();  

    auto s1 = std::make_shared<Ship>(4);  

    ShipManager s_manager(field1);  
    s_manager.placeShip(s1, {2, 2}, true);  
    return 0;
}
