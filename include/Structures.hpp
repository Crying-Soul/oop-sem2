#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <cstdint>

enum class CellStatus { Hidden, Revealed };

enum class SegmentStatus { Intact, Damaged, Destroyed };

enum class ShipStatus { Intact, Damaged, Destroyed };

struct Coordinate {
  uint8_t x;
  uint8_t y;

  bool operator==(const Coordinate &other) const {
    return x == other.x && y == other.y;
  }
};

enum class CellValue : char {
  WaterHidden = ' ',
  WaterRevealed = '~',
  ShipPart = 'S',
  Hit = 'X',
  Destroyed = '0'
};

struct FieldCell {
  Coordinate coord;
  CellStatus status;
  CellValue value;
};

struct ShipSegment {
  int8_t hp;
  Coordinate coord;
  SegmentStatus status;
  ShipSegment() : hp(2), coord({0, 0}), status(SegmentStatus::Intact) {}
};

#endif
