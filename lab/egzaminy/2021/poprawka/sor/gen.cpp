#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

const int MAX_N = 6;
const int MAX_M = 10;

int main()
{
    std::srand(std::time(0)); // Initialize random seed

    int n = std::rand() % (MAX_N - 1) + 2;        // Random n from 1 to MAX_N
    int m = std::rand() % std::min(MAX_M, n) + 1; // Random k from 1 to MAX_K
    std::cout << n << " " << m * (n + 1) << "\n";

    for (int i = 0; i < n; i++)
    {
        std::cout << std::rand() % 2;
    }

    std::cout << std::endl;

    for (int i = 0; i < m; i++)
    {
        int action = std::rand() % 2;
        switch (action)
        {
        case 0:
        case 1:
            char c = std::rand() % 2 == 0 ? '<' : '>';
            int i = std::rand() % n + 1;
            int j = std::rand() % n + 1;
            if (i > j)
            {
                std::swap(i, j);
            }

            if (i == j)
            {
                if (i > 0)
                {
                    i--;
                }
                else
                    j++;
            }

            std::cout << c << " " << i << " " << j << "\n";
        }

        for (int i = 1; i <= n; i++)
        {
            std::cout << "? " << i << "\n";
        }
    }

    return 0;
}
