#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_N = 500000;
const int MAX_M = 50000;
const int RANGE_K = 5;

int main()
{
    std::srand(std::time(0)); // Initialize random seed

    int n = std::rand() % MAX_N + 1; // Random n from 1 to MAX_N
    int m = std::rand() % MAX_M + 1; // Random m from 1 to MAX_M
    std::cout << n << " " << m << "\n";

    for (int i = 0; i < m; ++i)
    {
        char c = std::rand() % 2 == 0 ? 'N' : 'C'; // Random c from 'N' or 'C'
        int l = std::rand() % n + 1;               // Random l from 1 to n
        int r = std::rand() % n + 1;               // Random r from 1 to n
        if (l > r)
        {
            std::swap(l, r);
        }

        if (c == 'N')
        {
            int k = std::rand() % RANGE_K + 1; // Random k from 1 to RANGE_K
            std::cout << c << " " << l << " " << r << " " << k << "\n";
        }
        else
        {
            std::cout << c << " " << l << " " << r << "\n";
        }
    }

    return 0;
}
