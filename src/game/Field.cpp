#include "game/Field.hpp"

Field::Field(uint8_t rowsCount, uint8_t columnsCount) noexcept
    : rows(rowsCount), columns(columnsCount),
      field(rowsCount, std::vector<FieldCell>(columnsCount)) {
  for (uint8_t y = 0; y < rows; ++y) {
    for (uint8_t x = 0; x < columns; ++x) {
      field[y][x].coord = {x, y};
      field[y][x].value = CellValue::WaterHidden;
      field[y][x].status = CellStatus::Hidden;
      field[y][x].segment = nullptr;
    }
  }
}

Field::Field(const Field &other)
    : rows(other.rows), columns(other.columns), field(other.field) {}

Field &Field::operator=(const Field &other) {
  if (this != &other) {
    rows = other.rows;
    columns = other.columns;
    field = other.field;
  }
  return *this;
}

Field::Field(Field &&other) noexcept
    : rows(other.rows), columns(other.columns), field(std::move(other.field)) {
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

uint8_t Field::getColumns() const noexcept { return columns; };
uint8_t Field::getRows() const noexcept { return rows; };

void Field::setValueAt(Coordinate coord, CellValue value) {
  if (!isValidCoordinate(coord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  field[coord.y][coord.x].value =
      value; // Access using [y][x] for rows and columns
}

const Field::CellValue &Field::getValueAt(Coordinate coord) const {
  if (!isValidCoordinate(coord)) {
    throw std::out_of_range("Coordinate out of range");
  }
  return field[coord.y][coord.x]
      .value; // Access using [y][x] for rows and columns
}

bool Field::isValidCoordinate(Coordinate coord) const noexcept {
  return coord.y < rows && coord.x < columns;
}

bool Field::isPlaceAvailable(const std::shared_ptr<Ship> &ship,
                             Coordinate coord, bool vertical) const {
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

bool Field::placeShipByCoords(const std::shared_ptr<Ship> &ship,
                              Coordinate coord, bool vertical) {
  if (!isPlaceAvailable(ship, coord, vertical)) {
    return false;
  }

  ship->setOrientation(vertical);
  const int size = ship->getSize();

  for (uint8_t i = 0; i < size; ++i) {
    const uint8_t x = vertical ? coord.x : static_cast<uint8_t>(coord.x + i);
    const uint8_t y = vertical ? static_cast<uint8_t>(coord.y + i) : coord.y;

    Coordinate newCoord{x, y};

    ShipSegment &segment = ship->getSegment(i);
    segment.setCoord(newCoord);

    field[y][x].segment = &segment;
    setValueAt(newCoord, CellValue::ShipPart);
  }

  return true;
}

AttackResult Field::attack(Coordinate coord) {
  if (!isValidCoordinate(coord)) {
    throw AttackException("Attack out of bounds.");
  }

  FieldCell &cell = field[coord.y][coord.x];
  cell.status = CellStatus::Revealed;

  if (cell.segment != nullptr) {
    cell.value = CellValue::Hit;
    cell.segment->hit();

    if (cell.segment->isDestroyed()) {
      cell.value = CellValue::Destroyed;

      if (cell.segment->isShipDestroyed()) {
        // ???? ???? ??????? ?????????, ???????? ???????
        for (auto segment : cell.segment->getShip()->getSegments()) {
          Coordinate segmentCoord = segment->getCoord();

          for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
              if (dx == 0 && dy == 0)
                continue;

              Coordinate surroundingCoord = {
                  static_cast<uint8_t>(segmentCoord.x + dx),
                  static_cast<uint8_t>(segmentCoord.y + dy)};

              // ?????????, ??? ?????????? ????????? ? ???????? ????
              if (isValidCoordinate(surroundingCoord)) {
                FieldCell &surroundingCell =
                    field[surroundingCoord.y][surroundingCoord.x];
                surroundingCell.status = CellStatus::Revealed;

                // ???? ?????? ??????? ???? ????, ???????? ?? ??? ?????????
                if (surroundingCell.value == CellValue::WaterHidden) {
                  surroundingCell.value = CellValue::WaterRevealed;
                }
              }
            }
          }
        }
        return AttackResult::ShipDestroyed; // ?????????? ????????? ? ??????
                                            // ??????????? ???????
      } else {
        return AttackResult::SegmentDestroyed; // ?????????? ????????? ?
                                               // ?????????? ????????
      }
    }
    return AttackResult::Hit; // ???? ??????? ??? ?? ?????????
  } else {
    cell.value = CellValue::WaterRevealed;
    return AttackResult::Miss; // ???? ?????? ? ?????? ????? (????)
  }
}
