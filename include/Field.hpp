#ifndef FIELD_HPP
#define FIELD_HPP

#include "Structures.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

class Field {
private:
  uint8_t rows;
  uint8_t columns;
  std::vector<std::vector<FieldCell>> field;

public:
  Field(uint8_t rowsCount, uint8_t columnsCount);

  Field(const Field &other);

  Field &operator=(const Field &other);

  Field(Field &&other) noexcept;

  Field &operator=(Field &&other) noexcept;

  ~Field() = default;

  bool isValidCoordinate(Coordinate cord) const;

  void create();
  void display() const;
  void displayStatus() const;

  CellValue getValueAt(Coordinate cord) const;
  void setValueAt(Coordinate cord, CellValue value);
};

#endif
