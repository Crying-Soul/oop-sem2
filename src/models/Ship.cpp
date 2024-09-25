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
            << "ID: " << id << "\n"
            << "Size: " << static_cast<int>(size) << "\n"
            << "Orientation: " << (vertical ? "Vertical" : "Horizontal") << "\n"
            << "Status: "
            << (status == ShipStatus::Intact
                    ? "Intact"
                    : (status == ShipStatus::Destroyed ? "Destroyed"
                                                       : "Damaged"))
            << "\n------------------------------------\n";

  std::cout << std::setw(7) << "Segment" << std::setw(10) << "Status"
            << std::setw(6) << "HP" << std::setw(13) << "Position\n";
  std::cout << "------------------------------------\n";

  for (size_t i = 0; i < segments.size(); ++i) {
    std::string segmentStatus =
        (segments[i].status == SegmentStatus::Intact
             ? "Intact"
             : (segments[i].status == SegmentStatus::Destroyed ? "Destroyed"
                                                               : "Damaged"));

    std::cout << std::setw(7) << (i + 1) << std::setw(10) << segmentStatus
              << std::setw(5) << static_cast<int>(segments[i].hp)
              << std::setw(7) << "{" << static_cast<int>(segments[i].coord.x)
              << ", " << static_cast<int>(segments[i].coord.y) << "}\n";
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

bool Ship::handleAttack(Coordinate coord) {
  for (auto &segment : segments) {
    if (segment.coord == coord) {
      segment.hp--;
      if (segment.hp <= 0) {
        segment.status = SegmentStatus::Destroyed;
        return true;
        // std::cout << "Destroyed segment at (" << static_cast<int>(coord.x)
        //           << ", " << static_cast<int>(coord.y) << ")!\n";
      }
      segment.status = SegmentStatus::Damaged;
      status = ShipStatus::Damaged;
      // std::cout << "Hit segment at (" << static_cast<int>(coord.x) << ", "
      //           << static_cast<int>(coord.y) << ")!\n";

      if (isDestroyed()) {
        status = ShipStatus::Destroyed;
        // std::cout << "Ship destroyed!\n";
      }

      return true;
    }
  }
  return false;
}
SegmentStatus Ship::getSegmentStatusAt(Coordinate coord) const {
    for (const auto &segment : segments) {
        if (segment.coord == coord) {
            return segment.status;
        }
    }
    throw std::out_of_range("No segment found at the given coordinate.");
}


void Ship::setSegmentCoord(uint8_t segmentId, Coordinate coord) {
  if (segmentId < size) {
    segments[segmentId].coord = coord;
  } else {
    throw std::out_of_range("Invalid segment ID: " + std::to_string(segmentId));
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

uint8_t Ship::getSize() const noexcept { return size; }

uint32_t Ship::generateId() noexcept {
  auto now =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  return static_cast<uint32_t>(std::hash<uint8_t>()(size)) ^
         static_cast<uint32_t>(now);
}

uint32_t Ship::getId() const noexcept { return id; }