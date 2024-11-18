#include "random/Random.hpp"
#include <ctime>
#include <random>
#include <stdexcept>

// Constructor initializes random number generator with current time as seed
Random::Random() : rng(static_cast<unsigned int>(std::time(nullptr))) {}

// Template function for generating random values within a specified range
template <typename T>
T Random::getRandomValue(T min, T max) {
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    } else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(rng);
    } else {
        throw std::invalid_argument("Unsupported type for random value generation.");
    }
}

// New function to generate a random boolean value
bool Random::getRandomBool() {
    return getRandomValue<int>(0, 1) == 1; // Randomly returns true (1) or false (0)
}

// Explicit template instantiations for common types
template int Random::getRandomValue<int>(int min, int max);
template uint8_t Random::getRandomValue<uint8_t>(uint8_t min, uint8_t max);  // Corrected: uint8_t for uint8_t
template float Random::getRandomValue<float>(float min, float max);  // Corrected: float for float
template double Random::getRandomValue<double>(double min, double max);  // Added double instantiation for completeness
