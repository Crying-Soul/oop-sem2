#ifndef FIELD_HPP
#define FIELD_HPP

#include "Ship.hpp"
#include "Structures.hpp"
#include <iomanip>
#include <memory>

class Field {
private:
  uint8_t rows;
  uint8_t columns;
  std::vector<std::vector<FieldCell>> field;

  struct Colors {
    const std::string headerColor = "\033[1;36m";    // Cyan for header
    const std::string cellWaterColor = "\033[1;34m"; // Blue for water
    const std::string cellShipColor = "\033[1;32m";  // Green for ship parts
    const std::string cellHitColor = "\033[1;31m";   // Red for hits
    const std::string cellDestroyedColor =
        "\033[1;35m";                         // Magenta for destroyed
    const std::string resetColor = "\033[0m"; // Reset color
  } colors;

  bool isValidCoordinate(Coordinate cord) const noexcept;
  bool isPlaceAvailable(const std::shared_ptr<Ship> &ship, Coordinate cord,
                        bool vertical) const noexcept;
  CellValue getValueAt(Coordinate cord) const;
  void setValueAt(Coordinate cord, CellValue value);

public:
  Field(uint8_t rowsCount, uint8_t columnsCount) noexcept;
  Field(const Field &other);
  Field &operator=(const Field &other);
  Field(Field &&other) noexcept;
  Field &operator=(Field &&other) noexcept;

  void attack(Coordinate cord);
  bool placeShipByCoords(const std::shared_ptr<Ship> &ship, Coordinate cord,
                         bool vertical = false);
  void placeShipByRandCoords(const std::shared_ptr<Ship> &ship);
  void create() noexcept;
  void display() const noexcept;
  void displayStatus() const noexcept;
};

#endif