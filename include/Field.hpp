#ifndef FIELD_HPP
#define FIELD_HPP

#include "Ship.hpp"
#include "Structures.hpp"
#include <cstdlib> // ??? rand() ? srand()
#include <ctime>   // ??? time()
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class Field {
private:
  uint8_t rows;
  uint8_t columns;
  std::vector<std::vector<FieldCell>> field;

  struct Colors {
    const std::string headerColor = "\033[1;34m";        // Blue
    const std::string cellWaterColor = "\033[1;37m";     // White for Water
    const std::string cellShipColor = "\033[1;32m";      // Green for ShipPart
    const std::string cellHitColor = "\033[1;31m";       // Red for Hit
    const std::string cellDestroyedColor = "\033[1;33m"; // Yellow for Destroyed
    const std::string resetColor = "\033[0m";            // Reset
  } colors;

  bool isValidCoordinate(Coordinate cord) const;
  bool isPlaceAvailable(std::shared_ptr<Ship> ship, Coordinate cord,
                        bool vertical);
  CellValue getValueAt(Coordinate cord) const;
  void setValueAt(Coordinate cord, CellValue value);

public:
  Field(uint8_t rowsCount, uint8_t columnsCount);
  bool placeShip(std::shared_ptr<Ship> ship, Coordinate cord, bool vertical);
  void setRandom(std::shared_ptr<Ship> ship);
  void create();
  void display() const;
  void displayStatus() const;
};

#endif
