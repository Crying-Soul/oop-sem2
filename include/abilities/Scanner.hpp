#ifndef SCANNER_H
#define SCANNER_H

#include "abilities/Ability.hpp"
#include "game/Game.hpp" 

class Scanner : public Ability {
public:
    void use(Game &game) const override;

    std::string getName() const override;

    Ability::AbilityType getType() const override;
};

#endif // SCANNER_H
