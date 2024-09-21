#include "Ship.hpp"

Ship::Ship(int shipSize) : size(shipSize) {
  if (shipSize < 1 || shipSize > 4) {
    throw std::invalid_argument("Ship size must be between 1 and 4.");
  }

  segments.resize(shipSize);
  for (int i = 0; i < shipSize; ++i) {
    segments[i] = {2, {0, 0}};
  }
}

void Ship::printState() const {
  std::cout << "Ship state: ";
  for (const auto &segment : segments) {
    std::cout << "(" << static_cast<int>(segment.hp) << " " << "{"
              << static_cast<int>(segment.pos.x) << ","
              << static_cast<int>(segment.pos.y) << "})" << " ";
  }
  std::cout << std::endl;
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

int Ship::getSize() const { return size; }
