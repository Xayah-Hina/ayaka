#ifndef AYAKAPATHTRACER_RANDOM_H
#define AYAKAPATHTRACER_RANDOM_H

#include <cstdlib>

struct Random
{
    static float random_f(float low_bound, float high_bound);
};

float Random::random_f(float low_bound, float high_bound)
{
    return low_bound + (high_bound - low_bound) * (float(std::rand()) / (RAND_MAX + 1.0));
}

#endif //AYAKAPATHTRACER_RANDOM_H
