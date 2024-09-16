#include "ShipManager.hpp"
#include <iostream>

// ????????????? ???? ????? ?????? ?????????????
ShipManager::ShipManager(std::shared_ptr<Field> gameField)
    : field(std::move(gameField)), ships() {}

// ??????????? ???????????
ShipManager::ShipManager(const ShipManager &other)
    : ships(other.ships), field(other.field) {}

// ???????? ???????????? ???????????
ShipManager &ShipManager::operator=(const ShipManager &other) {
  if (this == &other)
    return *this; // ?????? ?? ????????????????
  ships = other.ships;
  field = other.field;
  return *this;
}

// ??????????? ???????????
ShipManager::ShipManager(ShipManager &&other) noexcept
    : ships(std::move(other.ships)), field(std::move(other.field)) {}

// ???????? ???????????? ???????????
ShipManager &ShipManager::operator=(ShipManager &&other) noexcept {
  if (this == &other)
    return *this;
  ships = std::move(other.ships);
  field = std::move(other.field);
  return *this;
}

bool ShipManager::placeShip(std::shared_ptr<Ship> ship, Coordinate cord,
                            bool vertical) {
  int size = ship->getSize();
  ship->printState();

  if (vertical) {
    for (uint8_t i = 0; i < size; ++i) {
      Coordinate newCord = {cord.x + i, cord.y};
      if (!field->isValidCoordinate(newCord)) {
        std::cerr << "Invalid position for ship placement!" << std::endl;
        return false;
      }
      field->setValueAt(newCord, CellValue::ShipPart);
    }
  } else {
    for (uint8_t i = 0; i < size; ++i) {
      Coordinate newCord = {cord.x, cord.y + i};
      if (!field->isValidCoordinate(newCord)) {
        std::cerr << "Invalid position for ship placement!" << std::endl;
        return false;
      }
      field->setValueAt(newCord, CellValue::ShipPart);
    }
  }

  ships.push_back(ship);
  system("clear");
  field->display();
  return true;
}

void ShipManager::printAllShips() const {
  for (const auto &ship : ships) {
    ship->printState();
  }
}
