#include "Ship.hpp"

Ship::Ship(uint8_t shipSize) : segments(shipSize), size(shipSize) {
  if (shipSize < 1 || shipSize > 4) {
    throw std::invalid_argument("Ship size must be between 1 and 4.");
  }

  for (int i = 0; i < shipSize; ++i) {
    segments[i] = {2, {0, 0}};
  }
}

void Ship::printState() const {
  std::cout << "=== Ship State ===\n";

  for (size_t i = 0; i < segments.size(); ++i) {
    std::cout << "Segment " << i + 1 << ": "
              << "HP = " << static_cast<int>(segments[i].hp) << ", "
              << "Position = {" << static_cast<int>(segments[i].pos.x) << ", "
              << static_cast<int>(segments[i].pos.y) << "}\n";
  }

  std::cout << "===================\n";
}

void Ship::updateSegmentHp(uint8_t segmentId, int8_t value) {
  if (segmentId < size) {
    segments[segmentId].hp += value;

  } else {
    throw std::out_of_range("Invalid segment ID.");
  }
}

void Ship::updateSegmentCoord(uint8_t segmentId, Coordinate pos) {
  if (segmentId < size) {
    segments[segmentId].pos = pos;
  } else {
    throw std::out_of_range("Invalid segment ID.");
  }
}

bool Ship::isDestroyed() const {
  for (const auto &segment : segments) {
    if (segment.hp > 0) {
      return false;
    }
  }
  return true;
}

uint8_t Ship::getSize() const { return size; }
