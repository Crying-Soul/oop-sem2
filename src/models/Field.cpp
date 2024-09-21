#include "Field.hpp"

Field::Field(uint8_t colCount, uint8_t rowCount)
    : rows(rowCount), columns(colCount),
      field(rowCount, std::vector<FieldCell>(colCount)) {
  create();
}

void Field::create() {
  for (uint8_t y = 0; y < rows; ++y) { // y ??????? ???? — ??????
    for (uint8_t x = 0; x < columns; ++x) { // x ?????????? ???? — ???????
      field[y][x].cord = {x, y};
      field[y][x].value = CellValue::Water;
      field[y][x].status = CellStatus::Hidden;
    }
  }
}

void Field::display() const {
  std::cout << "+";
  for (uint8_t x = 0; x < columns; ++x) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  for (uint8_t y = 0; y < rows; ++y) {
    std::cout << "|";
    for (uint8_t x = 0; x < columns; ++x) {
      std::cout << " " << static_cast<char>(field[y][x].value) << " |";
    }
    std::cout << std::endl;
    std::cout << "+";
    for (uint8_t x = 0; x < columns; ++x) {
      std::cout << "---+";
    }
    std::cout << std::endl;
  }
}

void Field::displayStatus() const {
  std::cout << "+";
  for (uint8_t x = 0; x < columns; ++x) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  for (uint8_t y = 0; y < rows; ++y) {
    std::cout << "|";
    for (uint8_t x = 0; x < columns; ++x) {
      std::cout << " " << (field[y][x].status == CellStatus::Hidden ? 'H' : 'R')
                << " |";
    }
    std::cout << std::endl;
    std::cout << "+";
    for (uint8_t x = 0; x < columns; ++x) {
      std::cout << "---+";
    }
    std::cout << std::endl;
  }
}

void Field::setValueAt(Coordinate cord, CellValue value) {
  if (!isValidCoordinate(cord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  field[cord.y][cord.x].value = value; // ??? ?????????
}

CellValue Field::getValueAt(Coordinate cord) const {
  if (!isValidCoordinate(cord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  return field[cord.y][cord.x].value; // ??? ?????????
}

bool Field::isValidCoordinate(Coordinate cord) const {
  return cord.y < rows && cord.x < columns;
}

bool Field::placeShip(std::shared_ptr<Ship> ship, Coordinate cord,
                      bool vertical) {
  if (!isPlaceAvailable(ship, cord, vertical)) {
    return false;
  }

  int size = ship->getSize();

  if (vertical) {
    for (uint8_t i = 0; i < size; ++i) {
      Coordinate newCord = {cord.x, static_cast<uint8_t>(cord.y + i)};
      ship->updateSegmentCoord(i, newCord);
      setValueAt(newCord, CellValue::ShipPart);
    }
  } else {
    for (uint8_t i = 0; i < size; ++i) {
      Coordinate newCord = {static_cast<uint8_t>(cord.x + i), cord.y};
      ship->updateSegmentCoord(i, newCord);
      setValueAt(newCord, CellValue::ShipPart);
    }
  }

  return true;
}

bool Field::isPlaceAvailable(std::shared_ptr<Ship> ship, Coordinate cord,
                             bool vertical) {
  uint8_t size = ship->getSize();

  uint8_t startX = cord.x > 0 ? cord.x - 1 : 0;
  uint8_t startY = cord.y > 0 ? cord.y - 1 : 0;
  uint8_t endX = vertical ? cord.x + 1 : cord.x + size;
  uint8_t endY = vertical ? cord.y + size : cord.y + 1;

  for (uint8_t y = startY; y <= endY && y < rows; ++y) {
    for (uint8_t x = startX; x <= endX && x < columns; ++x) {
      if (getValueAt({x, y}) != CellValue::Water) {
        return false;
      }
    }
  }

  return true;
}
