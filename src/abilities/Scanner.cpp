#include "abilities/Scanner.hpp"
#include <iostream>

void Scanner::use(Game &game, Coordinate coord) const {

  std::cout << "Scanner activated! Scanning 2x2 area starting at coordinate "
            << coord << " for ship segments.\n";

  const Field &enemyField = game.getEnemyField();

  if (!enemyField.isValidCoordinate(coord)) {
    std::cout << "Invalid coordinate! Please provide valid coordinates within "
                 "the field.\n";
    return;
  }

  if (coord.x + 1 >= enemyField.getColumns() ||
      coord.y + 1 >= enemyField.getRows()) {
    std::cout << "The 2x2 area extends beyond the field boundaries! Please "
                 "choose another starting point.\n";
    return;
  }

  bool foundShip = false;
  for (int dx = 0; dx < 2; ++dx) {
    for (int dy = 0; dy < 2; ++dy) {
      int checkX = coord.x + dx;
      int checkY = coord.y + dy;

      Coordinate checkCoord{checkX, checkY};

      Field::CellValue cellValue = enemyField.getValueAt(checkCoord);

      if (cellValue == Field::CellValue::ShipPart) {
        foundShip = true;
        std::cout << "Found ship segment!!\n";
      }
    }
  }

  if (!foundShip) {
    std::cout << "No ship segments found in the 2x2 area starting at " << coord
              << ".\n";
  }
}

std::string Scanner::getName() const { return "Scanner"; }

Ability::AbilityType Scanner::getType() const { return AbilityType::SCANNER; }