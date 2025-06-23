#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_N = 5;
const int MAX_K = 5;

int main()
{
    std::srand(std::time(0)); // Initialize random seed

    int n = std::rand() % MAX_N + 1; // Random n from 1 to MAX_N
    int k = std::rand() % MAX_K + 1; // Random k from 1 to MAX_K
    std::cout << n << " " << k << "\n";

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int num = (std::rand() % 2000001) - 1000000; // Random number from -10^6 to 10^6
                                                         // int num = (std::rand() % 21) - 10;
            std::cout << num;

            if (j != n - 1)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << "\n";
            }
        }
    }

    return 0;
}
