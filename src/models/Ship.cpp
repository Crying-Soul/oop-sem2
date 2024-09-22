#include "Ship.hpp"

Ship::Ship(uint8_t shipSize)
    : segments(shipSize), size(shipSize), id(generateId()), vertical(false),
      status(ShipStatus::Intact) {
  if (shipSize < 1 || shipSize > 4) {
    throw std::invalid_argument("Ship size must be between 1 and 4.");
  }

}

void Ship::printState() const noexcept {
  std::cout << "============ Ship State ============\n"
            << "ID: " << id << " Size: " << static_cast<int>(size)
            << " Vertical: " << (vertical ? "Yes" : "No") << std::endl;

  for (size_t i = 0; i < segments.size(); ++i) {
    std::cout << "Segment " << (i + 1) << ": "
              << "HP = " << static_cast<int>(segments[i].hp) << ", "
              << "Position = {" << static_cast<int>(segments[i].coord.x) << ", "
              << static_cast<int>(segments[i].coord.y) << "}\n";
  }

  std::cout << "====================================\n";
}

bool Ship::occupiesCoordinate(Coordinate coord) const noexcept {
  for (const auto &segment : segments) {
    if (segment.coord == coord) {
      return true;
    }
  }
  return false;
}

void Ship::handleAttack(Coordinate coord) {
  for (auto &segment : segments) {
    if (segment.coord == coord) {
      segment.hp--;
      if (segment.hp <= 0) {
        segment.status = SegmentStatus::Destroyed;
        std::cout << "Destroyed Segment at (" << static_cast<int>(coord.x) 
                  << ", " << static_cast<int>(coord.y) << ")!\n";
      } else {
        segment.status = SegmentStatus::Damaged;
        std::cout << "Hit segment at (" << static_cast<int>(coord.x) 
                  << ", " << static_cast<int>(coord.y) << ")!\n";
      }
      break; // Stop checking after hitting a segment
    }
  }
}

void Ship::setSegmentCoord(uint8_t segmentId, Coordinate coord) {
  if (segmentId < size) {
    segments[segmentId].coord = coord;
  } else {
    throw std::out_of_range("Invalid segment ID.");
  }
}

bool Ship::isDestroyed() noexcept {
  for (const auto &segment : segments) {
    if (segment.status != SegmentStatus::Destroyed) {
      return false;
    }
  }
  status = ShipStatus::Destroyed;
  return true;
}

void Ship::updateOrientation(bool isVertical) noexcept { 
  vertical = isVertical; 
}

uint8_t Ship::getSize() const noexcept { 
  return size; 
}

uint32_t Ship::generateId() noexcept {
  auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  return static_cast<uint32_t>(std::hash<uint8_t>()(size)) ^ static_cast<uint32_t>(now);
}

uint32_t Ship::getId() const noexcept { 
  return id; 
}