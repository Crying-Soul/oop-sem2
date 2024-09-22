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

void Field::display() const noexcept {
  std::cout << colors.headerColor << "    ";
  for (uint8_t x = 0; x < columns; ++x) {
    std::cout << " " << static_cast<char>('A' + x) << " ";
    if (x < columns - 1) {
      std::cout << "|"; // ???????????? ???????????
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
                << colors.resetColor << "|"; // ????????? ???????
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

void Field::setValueAt(Coordinate cord, CellValue value) {
  if (!isValidCoordinate(cord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  field[cord.y][cord.x].value = value;
}

CellValue Field::getValueAt(Coordinate cord) const {
  if (!isValidCoordinate(cord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  return field[cord.y][cord.x].value;
}

bool Field::isValidCoordinate(Coordinate cord) const noexcept {
  return cord.y < rows && cord.x < columns;
}

bool Field::placeShipByCords(const std::shared_ptr<Ship> &ship, Coordinate cord,
                             bool vertical) {
  if (!isPlaceAvailable(ship, cord, vertical)) {
    return false;
  }

  ship->updateOrientation(vertical);
  int size = ship->getSize();

  for (uint8_t i = 0; i < size; ++i) {
    Coordinate newCord =
        vertical ? Coordinate{cord.x, static_cast<uint8_t>(cord.y + i)}
                 : Coordinate{static_cast<uint8_t>(cord.x + i), cord.y};
    ship->setSegmentCoord(i, newCord);
    setValueAt(newCord, CellValue::ShipPart);
  }

  return true;
}

bool Field::isPlaceAvailable(const std::shared_ptr<Ship> &ship, Coordinate cord,
                             bool vertical) const noexcept {
  uint8_t size = ship->getSize();

  uint8_t startX = cord.x > 0 ? cord.x - 1 : 0;
  uint8_t startY = cord.y > 0 ? cord.y - 1 : 0;
  uint8_t endX = vertical ? cord.x + 1 : cord.x + size;
  uint8_t endY = vertical ? cord.y + size : cord.y + 1;

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

void Field::placeShipByRandCords(const std::shared_ptr<Ship> &ship) {
  if (!ship)
    return;

  Coordinate newCord;
  bool placed = false;

  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  while (!placed) {
    newCord.x = static_cast<uint8_t>(std::rand() % columns);
    newCord.y = static_cast<uint8_t>(std::rand() % rows);
    bool vertical = std::rand() % 2 == 0;

    if (isPlaceAvailable(ship, newCord, vertical)) {
      placed = placeShipByCords(ship, newCord, vertical);
    }
  }
}

void Field::attack(Coordinate cord) {
  if (!isValidCoordinate(cord)) {
    std::cout << "Invalid coordinates!\n";
    return;
  }
  FieldCell &cell = field[cord.y][cord.x];
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