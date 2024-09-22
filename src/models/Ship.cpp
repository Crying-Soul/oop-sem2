#include "Ship.hpp"

Ship::Ship(uint8_t shipSize)
    : segments(shipSize), size(shipSize), id(generateId()), vertical(false),
      status(ShipStatus::Intact) {
  if (shipSize < 1 || shipSize > 4) {
    throw std::invalid_argument("Ship size must be between 1 and 4.");
  }

  for (int i = 0; i < shipSize; ++i) {
    segments[i] = {2, {0, 0}, SegmentStatus::Intact};
  }
}

void Ship::printState() const {
  std::cout << "============ Ship State ============\n";

  std::cout << "ID: " << id << " Size: " << (int)size
            << " Vertical: " << (vertical ? "Yes" : "No") << std::endl;

  for (size_t i = 0; i < segments.size(); ++i) {
    std::cout << "Segment " << i + 1 << ": "
              << "HP = " << (int)segments[i].hp << ", "
              << "Position = {" << (int)segments[i].pos.x << ", "
              << (int)segments[i].pos.y << "}\n";
  }

  std::cout << "====================================\n";
}

bool Ship::occupiesCoordinate(Coordinate cord) const {
  for (const auto &segment : segments) {
    if (segment.pos.x == cord.x && segment.pos.y == cord.y) {
      return true;
    }
  }
  return false;
}

void Ship::handleAttack(Coordinate cord) {
  for (auto &segment : segments) {
    if (segment.pos.x == cord.x && segment.pos.y == cord.y) {
      segment.hp -= 1;
      if (segment.hp <= 0) {
        segment.status = SegmentStatus::Destroyed;
        std::cout << "Destroyed Segment at (" << (int)cord.x << ", " << (int)cord.y
                  << ")!\n";
      } else {
        segment.status = SegmentStatus::Damaged;
        std::cout << "Hit segment at (" << (int)cord.x << ", " << (int)cord.y
                  << ")!\n";
      }
    }
  }
}

void Ship::setSegmentCoord(uint8_t segmentId, Coordinate pos) {
  if (segmentId < size) {
    segments[segmentId].pos = pos;
  } else {
    throw std::out_of_range("Invalid segment ID.");
  }
}

bool Ship::isDestroyed() {
  for (const auto &segment : segments) {
    if (segment.status != SegmentStatus::Destroyed) {
      return false;
    }
  }
  status = ShipStatus::Destroyed;
  return true;
}
void Ship::updateOrientation(bool isVertical) { this->vertical = isVertical; }

uint8_t Ship::getSize() const { return size; }

uint32_t Ship::generateId() {
  auto now =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();

  return static_cast<uint32_t>(std::hash<uint8_t>()(size)) ^
         static_cast<uint32_t>(now);
}
uint32_t Ship::getId() const { return id; }
