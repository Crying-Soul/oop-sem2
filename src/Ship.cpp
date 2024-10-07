#include "Ship.hpp"
#include <stdexcept>
#include <iostream>
#include <memory>

Ship::Ship(uint8_t shipSize) : size(shipSize), segments(), vertical(false) {
    if (shipSize < 1 || shipSize > 4) {
        throw std::invalid_argument("Ship size must be between 1 and 4.");
    }
}

void Ship::initializeSegments() {
    for (uint8_t i = 0; i < size; ++i) {
        segments.push_back(std::make_shared<ShipSegment>(shared_from_this(), Coordinate{0, 0}));
    }
}

uint8_t Ship::getSize() const noexcept { return size; }

ShipSegment& Ship::getSegment(uint8_t index) {
    if (index >= segments.size()) {
        throw std::out_of_range("Index out of range");
    }
    return *segments.at(index);
}

bool Ship::isVertical() const noexcept { return vertical; }

void Ship::setOrientation(bool isVertical) noexcept { vertical = isVertical; }

bool Ship::occupiesCoordinate(Coordinate coord) const noexcept {
    for (const auto& segment : segments) {
        if (segment->getCoord() == coord) {
            return true;
        }
    }
    return false;
}

bool Ship::isShipDestroyed() const noexcept {
    for (const auto& segment : segments) {
        if (!segment->isDestroyed()) {
            return false;
        }
    }
    return true;
}
