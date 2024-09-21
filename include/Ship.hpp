#ifndef SHIP_HPP
#define SHIP_HPP

#include "Structures.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

class Ship {
private:
  std::vector<ShipSegment> segments;
  int size;

public:
  explicit Ship(int shipSize);

  void printState() const;
  void updateSegmentHp(uint8_t segmentId, int8_t value);
  void updateSegmentCoord(uint8_t segmentId, Coordinate pos);
  bool isDestroyed() const;
  int getSize() const;
};

#endif
