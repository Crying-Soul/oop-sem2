#include "Field.hpp"

Field::Field(uint8_t rowsCount, uint8_t columnsCount) noexcept
    : rows(rowsCount), columns(columnsCount),
      field(rowsCount, std::vector<FieldCell>(columnsCount)), colors() {
  create();
}

Field::Field(const Field &other)
    : rows(other.rows), columns(other.columns), field(other.field), colors() {}

Field &Field::operator=(const Field &other) {
  if (this != &other) {
    rows = other.rows;
    columns = other.columns;
    field = other.field;
  }
  return *this;
}

Field::Field(Field &&other) noexcept
    : rows(other.rows), columns(other.columns), field(std::move(other.field)),
      colors() {
  other.rows = 0;
  other.columns = 0;
  other.field.clear();
}

Field &Field::operator=(Field &&other) noexcept {
  if (this != &other) {
    rows = other.rows;
    columns = other.columns;
    field = std::move(other.field);
    other.rows = 0;
    other.columns = 0;
  }
  return *this;
}

void Field::create() noexcept {
  for (uint8_t y = 0; y < rows; ++y) {
    for (uint8_t x = 0; x < columns; ++x) {
      field[y][x].coord = {x, y};
      field[y][x].value = CellValue::WaterHidden;
      field[y][x].status = CellStatus::Hidden;
    }
  }
}

void Field::display(bool isEnemyField) const noexcept {
  std::cout << colors.headerColor << "    ";
  for (uint8_t x = 0; x < columns; ++x) {
    std::cout << " " << static_cast<char>('A' + x) << " ";
    if (x < columns - 1) {
      std::cout << "|";
    }
  }
  std::cout << colors.resetColor << std::endl;

  std::cout << colors.headerColor << "   +";
  for (uint8_t x = 0; x < columns; ++x) {
    std::cout << "---+";
  }
  std::cout << colors.resetColor << std::endl;

  for (uint8_t y = 0; y < rows; ++y) {
    std::cout << colors.headerColor << std::setw(2) << (y + 1) << " |"
              << colors.resetColor;
    for (uint8_t x = 0; x < columns; ++x) {
      CellValue value = field[y][x].value;
      std::string cellColor;

      if (isEnemyField) {

        if (value == CellValue::ShipPart) {
          value = CellValue::WaterHidden;
        }
      }

      // ќпредел€ем цвет €чейки
      switch (value) {
      case CellValue::WaterHidden:
      case CellValue::WaterRevealed:
        cellColor = colors.cellWaterColor;
        break;
      case CellValue::ShipPart:
        cellColor = colors.cellShipColor;
        break;
      case CellValue::Hit:
        cellColor = colors.cellHitColor;
        break;
      case CellValue::Destroyed:
        cellColor = colors.cellDestroyedColor;
        break;
      }

      std::cout << cellColor << " " << static_cast<char>(value) << " "
                << colors.resetColor << "|";
    }
    std::cout << std::endl;

    std::cout << colors.headerColor << "   +";
    for (uint8_t x = 0; x < columns; ++x) {
      std::cout << "---+";
    }
    std::cout << colors.resetColor << std::endl;
  }
}

void Field::displayStatus() const noexcept {
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

void Field::setValueAt(Coordinate coord, CellValue value) {
  if (!isValidCoordinate(coord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  field[coord.y][coord.x].value = value;
}

CellValue Field::getValueAt(Coordinate coord) const {
  if (!isValidCoordinate(coord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  return field[coord.y][coord.x].value;
}

bool Field::isValidCoordinate(Coordinate coord) const noexcept {
  return coord.y < rows && coord.x < columns;
}

bool Field::placeShipByCoords(const std::shared_ptr<Ship> &ship,
                              Coordinate coord, bool vertical) {
  if (!isPlaceAvailable(ship, coord, vertical)) {
    return false;
  }

  ship->updateOrientation(vertical);
  int size = ship->getSize();

  for (uint8_t i = 0; i < size; ++i) {
    Coordinate newcoord =
        vertical ? Coordinate{coord.x, static_cast<uint8_t>(coord.y + i)}
                 : Coordinate{static_cast<uint8_t>(coord.x + i), coord.y};
    ship->setSegmentCoord(i, newcoord);
    setValueAt(newcoord, CellValue::ShipPart);
  }

  return true;
}

bool Field::isPlaceAvailable(const std::shared_ptr<Ship> &ship,
                             Coordinate coord, bool vertical) const noexcept {
  uint8_t size = ship->getSize();

  uint8_t startX = coord.x > 0 ? coord.x - 1 : 0;
  uint8_t startY = coord.y > 0 ? coord.y - 1 : 0;
  uint8_t endX = vertical ? coord.x + 1 : coord.x + size;
  uint8_t endY = vertical ? coord.y + size : coord.y + 1;

  if (endX >= columns || endY >= rows) {
    return false;
  }

  for (uint8_t y = startY; y <= endY; ++y) {
    for (uint8_t x = startX; x <= endX; ++x) {
      if (!isValidCoordinate({x, y}) ||
          getValueAt({x, y}) != CellValue::WaterHidden) {
        return false;
      }
    }
  }

  return true;
}

void Field::placeShipByRandCoords(const std::shared_ptr<Ship> &ship) {
  if (!ship)
    return;

  Coordinate newcoord;
  bool placed = false;

  static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
  std::uniform_int_distribution<uint8_t> distX(0, columns - 1);
  std::uniform_int_distribution<uint8_t> distY(0, rows - 1);
  std::uniform_int_distribution<int> distVert(0, 1);

  while (!placed) {
    newcoord.x = distX(rng);
    newcoord.y = distY(rng);
    bool vertical = distVert(rng) == 0;

    if (isPlaceAvailable(ship, newcoord, vertical)) {
      placed = placeShipByCoords(ship, newcoord, vertical);
    }
  }
}

void Field::attack(Coordinate coord) {
  if (!isValidCoordinate(coord)) {
    std::cout << "Invalid coordinates!\n";
    return;
  }
  FieldCell &cell = field[coord.y][coord.x];
  switch (cell.value) {
  case CellValue::ShipPart:
    cell.value = CellValue::Hit;
    break;
  case CellValue::Hit:
    cell.value = CellValue::Destroyed;
    break;
  case CellValue::WaterHidden:
    cell.value = CellValue::WaterRevealed;
    cell.status = CellStatus::Revealed;
    std::cout << "Missed!\n";
    break;
  default:
    std::cout << "Already attacked!\n";
    break;
  }
}