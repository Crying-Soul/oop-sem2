#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <string>

class Game;  // Forward declaration

class Ability {
public:
    enum class AbilityType { DOUBLE_DAMAGE, SCANNER, RANDOM_STRIKE };

    virtual ~Ability() = default;

    virtual void use(Game &game) const = 0;  // Use const Game& to match derived class

    virtual std::string getName() const = 0;
    virtual AbilityType getType() const = 0;
};

#endif // ABILITY_HPP
