#include "ShipManager.hpp"
#include <iostream>

ShipManager::ShipManager(std::shared_ptr<Field> field) {
    this->field = field;
}

bool ShipManager::placeShip(std::shared_ptr<Ship> ship, Coordinate cord, bool vertical) {
    int size = ship->getSize();  
    
    ship->printState();  
        
    if (vertical) {
        for (int i = 0; i < size; ++i) {
            Coordinate newCord = {cord.x + i, cord.y};  
            if (!field->isValidCoordinate(newCord)) {   
                std::cerr << "Invalid position for ship placement!" << std::endl;
                return false;
            }
            field->setValueAt(newCord, 'S');  
        }
    } else {
        for (int i = 0; i < size; ++i) {
            Coordinate newCord = {cord.x, cord.y + i};
            if (!field->isValidCoordinate(newCord)) {
                std::cerr << "Invalid position for ship placement!" << std::endl;
                return false;
            }
            field->setValueAt(newCord, 'S');
        }
    }
    
    ships.push_back(ship);  
    field->display();  
    return true;
}

void ShipManager::printAllShips() const {
    for (const auto& ship : ships) {
        ship->printState();  
    }
}