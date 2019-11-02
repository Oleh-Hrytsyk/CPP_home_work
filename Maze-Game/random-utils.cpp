
#include "random-utils.h"

#include <random>
#include <vector>

int generateRandomNumber(int min, int max)
{
    static std::random_device randomDevice;
    static std::mt19937 engine{randomDevice()};
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}

std::vector<int> generateRandomSequence(int min, int max, int count)
{
    std::vector<int> rRandomSequence;
        for (int i = 0; i < count; ++i)
        {
            rRandomSequence.push_back(generateRandomNumber(min, max));
        }
        return rRandomSequence;
}