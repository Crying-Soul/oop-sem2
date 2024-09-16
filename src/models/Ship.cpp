#include "Ship.hpp"

Ship::Ship(int shipSize) : segments(shipSize, 2), size(shipSize) {
  if (shipSize < 1 || shipSize > 4) {
    throw std::invalid_argument("Ship size must be between 1 and 4.");
  }
}

// ??????????? ???????????
Ship::Ship(const Ship& other) : segments(other.segments), size(other.size) {}

// ???????? ???????????? ???????????
Ship& Ship::operator=(const Ship& other) {
  if (this == &other) return *this;  // ?????? ?? ????????????????
  segments = other.segments;
  size = other.size;
  return *this;
}

// ??????????? ???????????
Ship::Ship(Ship&& other) noexcept : segments(std::move(other.segments)), size(other.size) {
  other.size = 0;
}

// ???????? ???????????? ???????????
Ship& Ship::operator=(Ship&& other) noexcept {
  if (this == &other) return *this;
  segments = std::move(other.segments);
  size = other.size;
  other.size = 0;
  return *this;
}

void Ship::printState() const {
  std::cout << "Ship state: ";
  for (const auto& segment : segments) {
    std::cout << segment << " ";
  }
  std::cout << std::endl;
}

void Ship::updateSegment(int segmentId, int value) {
  if (segmentId >= 0 && segmentId < size) {
    segments[segmentId] += value;
  } else {
    throw std::out_of_range("Invalid segment ID.");
  }
}

bool Ship::isDestroyed() const {
  for (const auto& segment : segments) {
    if (segment > 0) {
      return false;
    }
  }
  return true;
}

int Ship::getSize() const {
  return size;
}

int Ship::getSegment(int segmentId) const {
  if (segmentId >= 0 && segmentId < size) {
    return segments[segmentId];
  } else {
    throw std::out_of_range("Invalid segment ID.");
  }
}
