#ifndef SHIP_SEGMENT_HPP
#define SHIP_SEGMENT_HPP

#include "Structures.hpp"
#include <memory>

class Ship; 

class ShipSegment {
public:
  enum class SegmentStatus { Intact, Damaged, Destroyed };

  ShipSegment(std::shared_ptr<Ship> parentShip, Coordinate pos = {0, 0});
  SegmentStatus getStatus() const;
  Coordinate getCoord() const;
  void setCoord(Coordinate pos);
  void setStatus(SegmentStatus newStatus);
  bool isDestroyed() const noexcept;
  bool isShipDestroyed() const noexcept;
  void hit() noexcept;

private:
  std::weak_ptr<Ship> ship; 
  Coordinate coord;
  SegmentStatus status = SegmentStatus::Intact;
};
#endif // SHIP_SEGMENT_HPP