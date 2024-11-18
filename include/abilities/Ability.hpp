#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <string>

class Coordinate;
class Game; // Forward declaration

class Ability {
public:
  enum class AbilityType { DOUBLE_DAMAGE, SCANNER, RANDOM_STRIKE };

  virtual ~Ability() = default;

//   virtual void use(Game &game) const = 0;
  virtual void use(Game &game,Coordinate coord) const = 0;
  virtual std::string getName() const = 0;
  virtual AbilityType getType() const = 0;
};

#endif // ABILITY_HPP
