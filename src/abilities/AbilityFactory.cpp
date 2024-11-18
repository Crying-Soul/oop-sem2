#include "abilities/AbilityFactory.hpp"
#include "abilities/DoubleDamage.hpp"
#include "abilities/Scanner.hpp"
#include "abilities/RandomStrike.hpp"
#include "random/Random.hpp"
#include <cstdlib>

Ability* AbilityFactory::createAbility(Ability::AbilityType type) {
    switch (type) {
        case Ability::AbilityType::DOUBLE_DAMAGE:
            return new DoubleDamage();
        case Ability::AbilityType::SCANNER:
            return new Scanner();
        case Ability::AbilityType::RANDOM_STRIKE:
            return new RandomStrike();
        default:
            throw std::invalid_argument("Unknown ability type");
    }
}

Ability* AbilityFactory::createRandomAbility() {
    Random rnd;
    int random = rnd.getRandomValue(0,2);
    return createAbility(static_cast<Ability::AbilityType>(random));
}
