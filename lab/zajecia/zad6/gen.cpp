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

    int n = std::rand() % MAX_N + 1; // Random n from 1 to MAX_N
    int m = std::rand() % MAX_M + 1; // Random k from 1 to MAX_K
    std::cout << n << " " << m << "\n";

    for (int i = 0; i < m; i++)
    {
        int a = std::rand() % n + 1;
        int b = std::rand() % n + 1;
        if (a > b)
        {
            std::swap(a, b);
        }

        char action = std::rand() % 2 == 0 ? 'B' : 'C';
        std::cout << a << " " << b << " " << action << "\n";
    }

    std::cout << std::endl;

    return 0;
}
