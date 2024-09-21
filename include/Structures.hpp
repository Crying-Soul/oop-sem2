#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <cstdint>

struct Coordinate {
  uint8_t x;
  uint8_t y;
};

enum class CellStatus { Hidden, Revealed };

enum class CellValue {
  Water = ' ',
  ShipPart = 'S',
  Hit = 'X',
  Destroyed = '0'
};



struct FieldCell {
  Coordinate cord;
  CellStatus status;
  CellValue value;
};

struct ShipSegment {
  int8_t hp;
  Coordinate pos;
};

#endif