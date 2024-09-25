#ifndef SHIP_HPP
#define SHIP_HPP

#include "Structures.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

class Ship {
private:
  std::vector<ShipSegment> segments;
  uint8_t size;
  uint32_t id;
  bool vertical;
  ShipStatus status;

  uint32_t generateId() noexcept;

public:
  explicit Ship(uint8_t shipSize);

  void printState() const noexcept;
  void setSegmentCoord(uint8_t segmentId, Coordinate coord);
  void updateOrientation(bool isVertical) noexcept;
  bool occupiesCoordinate(Coordinate coord) const noexcept;
  bool handleAttack(Coordinate coord);
  bool isDestroyed() noexcept;
  uint8_t getSize() const noexcept;
  uint32_t getId() const noexcept;
  SegmentStatus getSegmentStatusAt(Coordinate coord) const;
};

#endif