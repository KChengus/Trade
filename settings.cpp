#include <random>
#include <unistd.h>
#ifndef SETTINGS
#define SETTINGS
std::random_device dev;
std::mt19937 rng(dev());

double generateRandomNum(int range) {
    // range is in percentage
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, range*2);
    return (static_cast<double>(dist(rng)) - range) / 1000;
}

#endif