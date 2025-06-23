#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <cstdint>
#include <array>

using namespace std;

#define MAX_TURNS 2

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<uint64_t> horizontal((n - 1) * m);
    for (int i = 0; i < (n - 1) * m; i++)
    {
        cin >> horizontal[i];
    }

    vector<uint64_t> vertical(n * (m - 1));
    for (int i = 0; i < n * (m - 1); i++)
    {
        cin >> vertical[i];
    }

    uint64_t dp[2][n][2][MAX_TURNS + 1];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k <= MAX_TURNS; k++)
            {
                dp[0][i][j][k] = UINT64_MAX;
                dp[1][i][j][k] = UINT64_MAX;
            }
        }
    }

    dp[0][0][0][0] = 0;
    dp[0][0][1][0] = 0;

    for (int w = 0; w < m; w++)
    {
        int curr = w % 2;
        int prev = (w + 1) % 2;

        for (int x = 0; x < n; x++)
        {
            for (int i = 0; i <= MAX_TURNS; i++)
            {
                if (x != 0 || w != 0)
                {
                    dp[curr][x][0][i] = UINT64_MAX;
                    dp[curr][x][1][i] = UINT64_MAX;
                }
            }

            for (int i = 0; i <= MAX_TURNS; i++)
            {
                if (x > 0 && dp[curr][x - 1][0][i] != UINT64_MAX)
                {
                    dp[curr][x][0][i] = std::min(dp[curr][x][0][i], dp[curr][x - 1][0][i] + horizontal[w * (n - 1) + x - 1]);
                }

                if (w > 0 && dp[prev][x][1][i] != UINT64_MAX)
                {
                    dp[curr][x][1][i] = std::min(dp[curr][x][1][i], dp[prev][x][1][i] + vertical[x * (m - 1) + w - 1]);
                }
            }

            // Rotating
            for (int i = 0; i < MAX_TURNS; i++)
            {
                if (x > 0 && dp[curr][x - 1][1][i] != UINT64_MAX)
                {
                    dp[curr][x][0][i + 1] = std::min(dp[curr][x][0][i + 1], dp[curr][x - 1][1][i] + horizontal[w * (n - 1) + x - 1]);
                }

                if (w > 0 && dp[prev][x][0][i] != UINT64_MAX)
                {
                    dp[curr][x][1][i + 1] = std::min(dp[curr][x][1][i + 1], dp[prev][x][0][i] + vertical[x * (m - 1) + w - 1]);
                }
            }
        }
    }

    uint64_t min = UINT64_MAX;
    for (int i = 0; i <= MAX_TURNS; i++)
    {
        min = std::min(min, dp[(m - 1) % 2][n - 1][0][i]);
        min = std::min(min, dp[(m - 1) % 2][n - 1][1][i]);
    }

    cout << min << endl;
    return 0;
}