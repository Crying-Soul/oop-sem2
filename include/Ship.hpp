#ifndef SHIP_HPP
#define SHIP_HPP

#include "Structures.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

class Ship {
private:
  std::vector<ShipSegment> segments;
  uint8_t size;
  uint32_t id;
  bool vertical;
  ShipStatus status;

public:
  explicit Ship(uint8_t shipSize);

  void printState() const;
  void setSegmentCoord(uint8_t segmentId, Coordinate pos);
  void updateOrientation(bool isVertical);
  bool occupiesCoordinate(Coordinate cord) const;
  uint32_t generateId();
  uint32_t getId() const;

  void handleAttack(Coordinate cord);
  bool isDestroyed();
  uint8_t getSize() const;
  
};

#endif