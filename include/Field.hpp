#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdint>

enum class CellStatus {
  Hidden, 
  Revealed 
};


enum class CellValue {
  Water = ' ',
  ShipPart = 'S',
  Hit = 'X',
  Destroyed = '0'
};

struct Coordinate {
  uint8_t x;
  uint8_t y;
};

struct FieldCell {
  Coordinate cord;
  CellStatus status;
  CellValue value;
};

class Field {
private:
  uint8_t rows;
  uint8_t columns;
  std::vector<std::vector<FieldCell>> field;

public:
  
  Field(uint8_t rowsCount, uint8_t columnsCount);

  
  Field(const Field& other);

  
  Field& operator=(const Field& other);

  
  Field(Field&& other) noexcept;

  
  Field& operator=(Field&& other) noexcept;

  
  ~Field() = default;

  bool isValidCoordinate(Coordinate cord) const;

  void create();
  void display() const;
  void statusDisplay() const;

  CellValue getValueAt(Coordinate cord) const;
  void setValueAt(Coordinate cord, CellValue value);

};

#endif
