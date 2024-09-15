#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include "Field.hpp"
#include "Ship.hpp"
#include <vector>
#include <memory>

class ShipManager {
private:
    std::vector<std::shared_ptr<Ship>> ships;  
    std::shared_ptr<Field> field;  

public:
    ShipManager(std::shared_ptr<Field> field); 
    bool placeShip(std::shared_ptr<Ship> ship, Coordinate cord, bool vertical);
    void printAllShips() const;

};

#endif