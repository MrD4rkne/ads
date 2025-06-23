#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

// Generate a random number in the range [min, max].
uint64_t generateRandom(uint64_t min, uint64_t max)
{
    return min + std::rand() % (max - min + 1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::srand(std::time(nullptr));

    return 0;
}
