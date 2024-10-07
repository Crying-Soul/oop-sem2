#include "ShipSegment.hpp"
#include "Ship.hpp"
#include <iostream>

ShipSegment::ShipSegment(std::shared_ptr<Ship> parentShip, Coordinate pos)
    : ship(parentShip), coord(pos) {}

ShipSegment::SegmentStatus ShipSegment::getStatus() const { return status; }

Coordinate ShipSegment::getCoord() const { return coord; }

void ShipSegment::setCoord(Coordinate pos) { coord = pos; }

void ShipSegment::setStatus(SegmentStatus newStatus) { status = newStatus; }

bool ShipSegment::isDestroyed() const noexcept {
  return status == SegmentStatus::Destroyed;
}

bool ShipSegment::isShipDestroyed() const noexcept {
  if (auto spt = ship.lock()) {
    return spt->isShipDestroyed();
  }
  return false;
}

void ShipSegment::hit() noexcept {
  switch (status) {
  case SegmentStatus::Intact:
    status = SegmentStatus::Damaged;
    break;
  case SegmentStatus::Damaged:
    status = SegmentStatus::Destroyed;
    break;
  case SegmentStatus::Destroyed:
  default:
    break;
  }
}
