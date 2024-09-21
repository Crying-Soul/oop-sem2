#ifndef FIELD_HPP
#define FIELD_HPP

#include "Ship.hpp"
#include "Structures.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class Field {
private:
  uint8_t rows;
  uint8_t columns;
  std::vector<std::vector<FieldCell>> field;

public:
  Field(uint8_t rowsCount, uint8_t columnsCount);

  ~Field() = default;
  bool placeShip(std::shared_ptr<Ship> ship, Coordinate cord,
                        bool vertical);
  bool isValidCoordinate(Coordinate cord) const;
  bool isPlaceAvailable(std::shared_ptr<Ship> ship, Coordinate cord,
                        bool vertical);

  void create();
  void display() const;
  void displayStatus() const;

  CellValue getValueAt(Coordinate cord) const;
  void setValueAt(Coordinate cord, CellValue value);
};

#endif
