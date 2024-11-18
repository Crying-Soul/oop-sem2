#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <ctime>
#include <random>
#include <stdexcept>
class Random {
public:
  Random();

 
  template <typename T> T getRandomValue(T min, T max);
    bool getRandomBool();
private:
  std::mt19937 rng;
};

#endif // RANDOM_HPP
