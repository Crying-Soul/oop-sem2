#ifndef SHIP_HPP
#define SHIP_HPP

#include "Structures.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

class Ship {
private:
  std::vector<ShipSegment> segments;
  uint8_t size;

public:
  explicit Ship(uint8_t shipSize);

  void printState() const;
  void updateSegmentHp(uint8_t segmentId, int8_t value);
  void updateSegmentCoord(uint8_t segmentId, Coordinate pos);
  bool isDestroyed() const;
  uint8_t getSize() const;
};

#endif
