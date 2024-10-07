#ifndef FIELD_HPP
#define FIELD_HPP

#include "Ship.hpp"
#include "ShipSegment.hpp"
#include "Structures.hpp"
#include <iomanip>
#include <memory>
#include <random>

class Field {

public:
  enum class CellStatus { Hidden, Revealed };

  enum class CellValue : char {
    WaterHidden = ' ',
    WaterRevealed = '~',
    ShipPart = 'S',
    Hit = 'X',
    Destroyed = '0'
  };

  struct FieldCell {
    Coordinate coord;
    CellStatus status;
    CellValue value;
    ShipSegment *segment;
  };

private:
  uint8_t rows;
  uint8_t columns;

  std::vector<std::vector<FieldCell>> field;

  bool isPlaceAvailable(const std::shared_ptr<Ship> &ship, Coordinate cord,
                        bool vertical) const noexcept;

  bool isValidCoordinate(Coordinate coord) const noexcept;

public:
  Field(uint8_t rowsCount, uint8_t columnsCount) noexcept;
  Field(const Field &other);
  Field &operator=(const Field &other);
  Field(Field &&other) noexcept;
  Field &operator=(Field &&other) noexcept;

  // ?GETTERS
  uint8_t getColumns() const noexcept;
  uint8_t getRows() const noexcept;
  const CellValue &getValueAt(Coordinate cord) const;
  
  // ?SETTERS
  void setValueAt(Coordinate cord, CellValue value);

  bool placeShipByCoords(const std::shared_ptr<Ship> &ship, Coordinate coord,
                         bool vertical);
  void placeShipByRandCoords(const std::shared_ptr<Ship> &ship);
    AttackResult attack(Coordinate coord);


};

#endif