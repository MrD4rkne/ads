#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <climits>

#define LEN 3
#define MAX_DIFF 3

using namespace std;

int count(string &a, int start, int middle, int end)
{
    int c = 0;
    for (int i = 0; i < LEN && end - i >= middle; i++)
    {
        if (a[end - i] != 'G')
            continue;
        for (int j = 1; j <= LEN && end - i - j >= start; j++)
        {
            if (a[end - i - j] == 'G')
            {
                ++c;
            }
        }
    }

    return c;
}

void replace(const vector<int> &matches, char v[][2][LEN], string &text, int i, bool replace)
{
    char *word = v[matches[i]][replace ? 1 : 0];
    for (int j = 0; j < LEN; j++)
    {
        text[i - j] = word[LEN - 1 - j];
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    string s(n, ' ');

    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    char v[m][2][LEN];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int c = 0; c < LEN; c++)
            {
                cin >> v[i][j][c];
            }
        }
    }

    // Which sequence from left ends at i index (-1 if none).
    vector<int> matches(n, -1);

    for (int i = LEN - 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool match = true;
            for (int k = 0; k < LEN; k++)
            {
                if (s[i - k] != v[j][0][LEN - 1 - k])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                matches[i] = j;
                break;
            }
        }
    }

    vector<vector<int>> dp(n, vector<int>(2, INT_MAX));
    dp[0][0] = 0;
    dp[0][1] = INT_MAX;

    for (int i = 1; i < n; i++)
    {
        int prev = std::max(i - LEN, 0);
        if (i < LEN)
        {
            int c = 0;
            for (int j = 1; j <= i; j++)
            {
                for (int k = 0; k < j; k++)
                {
                    if (s[j] == 'G' && s[k] == 'G')
                    {
                        c++;
                    }
                }
            }
            dp[i][0] = std::min(dp[i][0], count(s, 0, 0, i));
        }
        else
        {
            int c = 0;
            for (int j = 1; j <= i; j++)
            {
                for (int k = 0; k < j; k++)
                {
                    if (s[j] == 'G' && s[k] == 'G')
                    {
                        c++;
                    }
                }
            }
            dp[i][0] = std::min(dp[i][0], dp[prev][0] + count(s, std::max(0, prev - LEN + 1), prev + 1, i));
        }

        for (int j = 1; j <= LEN && i - j >= 0; j++)
        {
            int index = i - j;
            if (matches[index] != -1)
            {
                replace(matches, v, s, index, true);
                dp[i][0] = std::min(dp[i][0], dp[index][1] + count(s, std::max(0, index - LEN + 1), index + 1, i));
                replace(matches, v, s, index, false);
            }
        }

        if (matches[i] != -1)
        {
            replace(matches, v, s, i, true);
            dp[i][1] = std::min(dp[i][1], dp[prev][0] + count(s, std::max(0, prev - LEN + 1), i - LEN + 1, i));

            if (matches[prev] != -1)
            {
                replace(matches, v, s, prev, true);
                dp[i][1] = std::min(dp[i][1], dp[prev][1] + count(s, std::max(0, prev - LEN + 1), i - LEN + 1, i));
                replace(matches, v, s, prev, false);
            }
            replace(matches, v, s, i, false);
        }
    }

    cout << std::min(dp[n - 1][0], dp[n - 1][1]) << endl;
}