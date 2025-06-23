#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Funkcja znajdująca minimum w oknie o rozmiarze `2k+1` i sumująca wynik
bool is_possible(const vector<uint64_t> &data, uint64_t goal, uint64_t k)
{
    size_t n = data.size();
    vector<uint64_t> dp(n);
    deque<size_t> dq;

    // Znajdowanie minimum w oknach długości `2k+1`
    for (size_t i = 0; i < n; i++)
    {
        // Usuwanie elementów spoza okna
        while (!dq.empty() && dq.front() + k < i)
            dq.pop_front();

        // Usuwanie większych wartości, bo chcemy minimum
        while (!dq.empty() && data[dq.back()] > data[i])
            dq.pop_back();

        dq.push_back(i);
        dp[i] = data[dq.front()];
    }

    dq.clear();

    // Drugie przetwarzanie od prawej strony, żeby poprawnie wyznaczyć minimalne wartości
    for (ssize_t i = n - 1; i >= 0; i--)
    {
        while (!dq.empty() && dq.front() > i + k)
            dq.pop_front();

        while (!dq.empty() && data[dq.back()] > data[i])
            dq.pop_back();

        dq.push_back(i);
        dp[i] = min(dp[i], data[dq.front()]);
    }

    // Obliczanie sumy
    uint64_t sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum += dp[i];
    }

    return sum <= goal;
}

int main()
{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<uint64_t> data(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> data[i];
    }

    vector<uint64_t> queries(m);
    for (size_t i = 0; i < m; i++)
    {
        cin >> queries[i];
    }

    for (uint64_t query : queries)
    {
        size_t l = 0;
        size_t r = data.size();
        while (l < r)
        {
            uint64_t mid = (l + r) / 2;
            if (is_possible(data, query, mid))
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }

        cout << l << endl;
    }
}