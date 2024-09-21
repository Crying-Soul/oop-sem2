#include "Field.hpp"


Field::Field(uint8_t rowCount, uint8_t colCount) 
  : rows(rowCount), columns(colCount), field(rowCount, std::vector<FieldCell>(colCount)) {
    create(); 
}


void Field::create() {
  for (uint8_t x = 0; x < rows; ++x) {
    for (uint8_t y = 0; y < columns; ++y) {
      field[x][y].cord = {x, y};
      field[x][y].value = CellValue::Water;
      field[x][y].status = CellStatus::Hidden;
    }
  }
}

void Field::display() const {
  std::cout << "+";
  for (uint8_t y = 0; y < columns; ++y) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  for (uint8_t x = 0; x < rows; ++x) {
    std::cout << "|";
    for (uint8_t y = 0; y < columns; ++y) {
      std::cout << " " << static_cast<char>(field[x][y].value) << " |";
    }
    std::cout << std::endl;
    std::cout << "+";
    for (uint8_t y = 0; y < columns; ++y) {
      std::cout << "---+";
    }
    std::cout << std::endl;
  }
}

void Field::displayStatus() const {
  std::cout << "+";
  for (uint8_t y = 0; y < columns; ++y) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  for (uint8_t x = 0; x < rows; ++x) {
    std::cout << "|";
    for (uint8_t y = 0; y < columns; ++y) {
      std::cout << " " << (field[x][y].status == CellStatus::Hidden ? 'H' : 'R') << " |";
    }
    std::cout << std::endl;
    std::cout << "+";
    for (uint8_t y = 0; y < columns; ++y) {
      std::cout << "---+";
    }
    std::cout << std::endl;
  }
}

void Field::setValueAt(Coordinate cord, CellValue value) {
  if (!isValidCoordinate(cord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  field[cord.x][cord.y].value = value;
}

CellValue Field::getValueAt(Coordinate cord) const {
  if (!isValidCoordinate(cord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  return field[cord.x][cord.y].value;
}

bool Field::isValidCoordinate(Coordinate cord) const {
  return cord.x < rows && cord.y < columns;
}
