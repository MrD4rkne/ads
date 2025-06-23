#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

const int MAX_N = 100;
const int MAX_M = 100;

int main()
{
    std::srand(std::time(0)); // Initialize random seed

    int n = std::rand() % MAX_N + 1;
    std::cout << n << " " << "\n";

    for (int i = 0; i < n; i++)
    {
        int n = std::rand() % MAX_N + 1;
        if (n % 2 != 0)
        {
            n++;
        }

        std::cout << n << " ";
    }

    std::cout << "\n";

    return 0;
}
