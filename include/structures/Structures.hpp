#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <cstdint>
#include <ostream>

enum class AttackResult { Hit, Miss, SegmentDestroyed, ShipDestroyed };

struct Coordinate {
  uint8_t x;
  uint8_t y;

  bool operator==(const Coordinate &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Coordinate &other) const { return !(*this == other); }

  friend std::ostream &operator<<(std::ostream &os, const Coordinate &coord) {
    os << "(" << static_cast<int>(coord.x) << ", " << static_cast<int>(coord.y)
       << ")";
    return os;
  }
};
#endif
