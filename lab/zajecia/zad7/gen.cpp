#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_M = 50;
const int MAX_X = 10;
const int MAX_K = 5;

int main()
{
    std::srand(std::time(0)); // Initialize random seed

    int m = std::rand() % MAX_M + 1; // Random m from 1 to MAX_M
    std::cout << m << "\n";

    for (int i = 0; i < m; i++)
    {
        char op = std::rand() % 2 == 0 ? 'i' : 'g';
        if (i == 0)
            op = 'i';
        std::cout << op << " ";

        int jp = std::rand() % MAX_X + 1; // Random jp from 1 to MAX_X
        std::cout << jp << " ";

        if (op == 'i')
        {
            int x = std::rand() % (MAX_X + 1); // Random x from 1 to MAX_X
            int k = std::rand() % MAX_K + 1;   // Random k from 1 to MAX_K
            std::cout << x << " " << k;
        }

        std::cout << "\n";
    }

    return 0;
}
