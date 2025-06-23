#include <iostream>
#include <vector>

using namespace std;

const uint32_t MOD = 1000000000;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<uint32_t> values(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    vector<vector<uint32_t>> dp(n, vector<uint32_t>(k, 0));

    dp[0][0] = 1;

    for (int i = 1; i < n; i++)
    {
        dp[i][0] = 1;
        for (int length = 1; length < k; length++)
        {
            for (int j = 0; j < i; j++)
            {
                if (values[j] < values[i])
                {
                    continue;
                }

                dp[i][length] = (dp[i][length] + dp[j][length - 1]) % MOD;
            }
        }
    }

    uint32_t result = 0;
    for (int i = 0; i < n; i++)
    {
        result = (result + dp[i][k - 1]) % MOD;
    }

    cout << result << endl;

    return 0;
}