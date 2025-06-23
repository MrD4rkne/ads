#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

const int MAX_N = 1000;
const int MAX_K = 10;

int main()
{
    std::srand(std::time(0)); // Initialize random seed

    int n = std::rand() % MAX_N + 1;              // Random n from 1 to MAX_N
    int k = std::rand() % std::min(MAX_K, n) + 1; // Random k from 1 to MAX_K
    std::cout << n << " " << k << "\n";

    std::vector<int> v(n, 0);
    for (int i = 0; i < n; i++)
        v[i] = i + 1;

    std::random_shuffle(v.begin(), v.end());

    for (int i = 0; i < n; i++)
    {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}
