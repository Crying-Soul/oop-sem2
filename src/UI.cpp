#include "UI.hpp"

void UI::renderField(const Field &field, bool isEnemyField,
                     bool colorful) const noexcept {
  const uint8_t columns = field.getColumns();
  const uint8_t rows = field.getRows();

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
      Field::CellValue value = field.getValueAt({x, y});

      if (isEnemyField && value == Field::CellValue::ShipPart) {
        value = Field::CellValue::WaterHidden;
      }

      std::string cellColor;
      switch (value) {
      case Field::CellValue::WaterHidden:
      case Field::CellValue::WaterRevealed:
        cellColor = colorful ? colors.cellWaterColor : "";
        break;
      case Field::CellValue::ShipPart:
        cellColor = colorful ? colors.cellShipColor : "";
        break;
      case Field::CellValue::Hit:
        cellColor = colorful ? colors.cellHitColor : "";
        break;
      case Field::CellValue::Destroyed:
        cellColor = colorful ? colors.cellDestroyedColor : "";
        break;
      default:
        cellColor = "";
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

void UI::fieldsRender(const Field &userField, const Field &enemyField,
                      bool colorful) const noexcept {
  std::cout << "User's Field:\n";
  renderField(userField, false, colorful);

  std::cout << "\nEnemy's Field:\n";
  renderField(enemyField, true, colorful);
}

void UI::renderShipState(const std::shared_ptr<Ship> &ship) const noexcept {
  std::cout << colors.headerColor << "============ Ship State ============\n"
            << colors.resetColor;

  const uint8_t shipSize = ship->getSize();

  std::cout << "Size: " << static_cast<int>(shipSize) << "\n"
            << "Orientation: "
            << (ship->isVertical() ? "Vertical" : "Horizontal") << "\n"
            << "------------------------------------\n";

  std::cout << std::setw(9) << "Segment" << std::setw(12) << "Status"
            << std::setw(15) << "Position\n";
  std::cout << "------------------------------------\n";

  for (uint8_t i = 0; i < shipSize; ++i) {
    const ShipSegment &segment = ship->getSegment(i);
    renderSegmentState(segment, i + 1);
  }

  std::cout << colors.resetColor << "====================================\n";
}

void UI::renderSegmentState(const ShipSegment &segment,
                            int index) const noexcept {
  std::ostringstream output;

  output << std::setw(10) << index << std::setw(12);

  switch (segment.getStatus()) {
  case ShipSegment::SegmentStatus::Intact:
    output << colors.cellShipColor << "Intact" << colors.resetColor;
    break;
  case ShipSegment::SegmentStatus::Damaged:
    output << colors.cellHitColor << "Damaged" << colors.resetColor;
    break;
  case ShipSegment::SegmentStatus::Destroyed:
    output << colors.cellDestroyedColor << "Destroyed" << colors.resetColor;
    break;
  }

  output << std::setw(8) << segment.getCoord() << "\n";

  std::cout << output.str();
}

void UI::displayAttackResult(AttackResult result,
                             Coordinate coord) const noexcept {
  switch (result) {
  case AttackResult::Hit:
    std::cout << "Hit at " << coord << "!\n";
    break;
  case AttackResult::Miss:
    std::cout << "Miss at " << coord << "!\n";
    break;
  case AttackResult::SegmentDestroyed:
    std::cout << "Segment destroyed at " << coord << "!\n";
    break;
  case AttackResult::ShipDestroyed:
    std::cout << "Ship destroyed at " << coord << "!\n";
    break;
  }
}

