#include <random>
#include <ctime>

class Random {
public:
    Random() : rng(static_cast<unsigned int>(std::time(nullptr))) {}

    template <typename T>
    T getRandomValue(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    }

private:
    std::mt19937 rng;
};
