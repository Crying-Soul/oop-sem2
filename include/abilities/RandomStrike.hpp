#ifndef RANDOMSTRIKE_H
#define RANDOMSTRIKE_H

#include "abilities/Ability.hpp"
#include "game/Game.hpp" 
#include "random/Random.hpp"


class RandomStrike : public Ability {
public:
    void use(Game &game) const override;


    std::string getName() const override;

    Ability::AbilityType getType() const override ;
};

#endif // RANDOMSTRIKE_H
