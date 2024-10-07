#ifndef UI_HPP
#define UI_HPP

#include "Field.hpp"
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
class UI {
private:
  struct Colors {
    const std::string headerColor = "\033[1;36m";    // Cyan for header
    const std::string cellWaterColor = "\033[1;34m"; // Blue for water
    const std::string cellShipColor = "\033[1;32m";  // Green for ship parts
    const std::string cellHitColor = "\033[1;31m";   // Red for hits
    const std::string cellDestroyedColor =
        "\033[1;35m";                         // Magenta for destroyed
    const std::string resetColor = "\033[0m"; // Reset color
  } colors;

public:
  UI() : colors() {};
  void renderField(const Field &field, bool isEnemyField,
                   bool colorful) const noexcept;
  void fieldsRender(const Field &userField, const Field &enemyField,
                    bool colorful = true) const noexcept;

  void renderShipState(const std::shared_ptr<Ship> &ship) const noexcept;
  void renderSegmentState(const ShipSegment &segment, int index) const noexcept;
  void displayAttackResult(AttackResult result, Coordinate coord) const noexcept;
};

#endif // UI_HPP