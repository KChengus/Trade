#include <cstdlib>
#include <random>
#include <unistd.h>
#ifndef SETTINGS
#define SETTINGS
std::random_device dev;
std::mt19937 rng(dev());

double generateRandVola(int lower, int higher) {
    // range is in percentage
    lower = abs(lower); // lowerBound is <= 0
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, lower+higher);
    double toProcent = (static_cast<double>(dist(rng)) - lower) / 100; 
    return toProcent / 100;
}

int genRandInt(int lower, int higher) {
    lower = abs(lower); // lowerBound is <= 0
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, lower+higher);
    return dist(rng) - lower;
}

#endif