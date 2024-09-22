#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <cstdint>

enum class CellStatus { Hidden, Revealed };
enum class SegmentStatus { Intact, Damaged, Destroyed };
enum class ShipStatus { Intact, Damaged, Destroyed };

struct Coordinate {
  uint8_t x;
  uint8_t y;
};

enum class CellValue {
  WaterHiden = ' ',
  WaterRevealed = '~',
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
  SegmentStatus status;
};

#endif