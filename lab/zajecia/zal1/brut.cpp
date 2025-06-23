#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

using bitmask = uint16_t;

long long sum(const vector<vector<long long>> &a, vector<vector<int>> masks)
{
    const int n = a[0].size();
    const int k = a.size();

    long long anwser = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (masks[i][j] == 1)
            {
                anwser += a[j][i] + a[j][i - 1];
            }
            if (masks[i][j] == 2)
            {
                anwser += a[j][i];
            }
        }
    }
    return anwser;
}

bool is_valid(vector<int> &previous, vector<int> &current)
{
    for (size_t i = 0; i < current.size(); i++)
    {
        if (current[i] == 1 && previous[i] != 0)
        {
            return false;
        }
    }

    int currentKStreak = current[0] == 2 ? 1 : 0;
    for (size_t i = 1; i < current.size(); i++)
    {
        if (current[i] == 2)
        {
            currentKStreak++;
            continue;
        }

        if (currentKStreak % 2 != 0)
        {
            return false;
        }

        currentKStreak = 0;
    }

    return true;
}

long long anwser(const vector<vector<long long>> &a, vector<vector<int>> &masks, size_t i)
{
    if (masks.size() == i)
    {
        return sum(a, masks);
    }

    const int k = a.size();

    long long curr = 0;

    for (int ones = 0; ones <= k; ones++)
    {
        for (int twos = 0; twos + ones <= k; twos++)
        {
            if (twos % 2 != 0)
            {
                continue;
            }

            for (int j = 0; j < twos; j++)
            {
                masks[i][k - 1 - j] = 2;
            }

            for (int j = 0; j < ones; j++)
            {
                masks[i][k - 1 - twos - j] = 1;
            }

            do
            {
                if (!is_valid(masks[i - 1], masks[i]))
                {
                    continue;
                }

                int anw = anwser(a, masks, i + 1);
                if (anw > curr)
                {
                    curr = anw;
                }

            } while (next_permutation(masks[i].begin(), masks[i].end()));
            fill(masks[i].begin(), masks[i].end(), 0);
        }
    }

    return curr;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<long long>> a(k, vector<long long>(n));

    for (int row = 0; row < k; row++)
    {
        for (int column = 0; column < n; column++)
        {
            cin >> a[row][column];
        }
    }

    long long ret = 0;

    vector<vector<int>> masks(n, vector<int>(k, 0));

    for (int twos = 0; twos <= k; twos++)
    {
        if (twos % 2 != 0)
        {
            continue;
        }

        for (int j = 0; j < twos; j++)
        {
            masks[0][k - 1 - j] = 2;
        }

        do
        {
            if (!is_valid(masks[0], masks[0]))
            {
                continue;
            }

            ret = max(ret, anwser(a, masks, 1));
        } while (next_permutation(masks[0].begin(), masks[0].end()));
    }

    cout << ret << endl;

    return 0;
}