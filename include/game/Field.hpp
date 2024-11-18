#ifndef FIELD_HPP
#define FIELD_HPP

#include "exceptions/AttackExceptions.hpp"
#include "exceptions/ShipPlaceExceptions.hpp"
#include "game/Ship.hpp"
#include "random/Random.hpp"
#include "structures/Structures.hpp"
#include <iomanip>
#include <iostream>
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

  bool isPlaceAvailable(const std::shared_ptr<Ship> &ship, Coordinate coord,
                        bool vertical) const;

  bool isValidCoordinate(Coordinate coord) const noexcept;
};

#endif