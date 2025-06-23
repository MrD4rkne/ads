#include <iostream>
#include <vector>

using namespace std;

int64_t min_koszt(const vector<int> &a)
{
    const size_t n = a.size();
    vector<vector<int64_t>> dp(n, vector<int64_t>(n + 1, 0));
    vector<vector<int64_t>> sum(n, vector<int64_t>(n + 1, 0));

    for (size_t i = 0; i < n; ++i)
    {
        sum[i][i] = a[i];
        for (size_t j = i + 1; j < n; ++j)
        {
            sum[i][j] = sum[i][j - 1] + a[j];
        }
    }

    for (size_t len = 2; len < n; ++len)
    {
        for (size_t i = 0; i < n - len; ++i)
        {
            const size_t j = i + len;
            int64_t min_cost = INT64_MAX;
            for (int k = i; k < j; ++k)
            {
                min_cost = min(min_cost, dp[i][k] + dp[k + 1][j]);
            }

            dp[i][j] = min_cost + sum[i][j];
        }
    }