#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>
#include <memory>
#include "Structures.hpp"
#include "ShipSegment.hpp"

class Ship : public std::enable_shared_from_this<Ship> { // Ensure shared_from_this can be used
public:
    Ship(uint8_t shipSize);
    void initializeSegments();  // Separate segment initialization step
    uint8_t getSize() const noexcept;
    ShipSegment& getSegment(uint8_t index);
    bool isVertical() const noexcept;
    void setOrientation(bool isVertical) noexcept;
    bool occupiesCoordinate(Coordinate coord) const noexcept;
    bool isShipDestroyed() const noexcept;

private:
    uint8_t size;
    std::vector<std::shared_ptr<ShipSegment>> segments;
    bool vertical;
};

#endif // SHIP_HPP
