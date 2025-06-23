#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> points;
    set<pair<int, int>> s;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        s.insert({x, y});
        points.push_back({x, y});
    }

    uint64_t max = 0;
    for (int i = 0; i < n; i++)
    {
        for (int dx = -k; dx <= 0; dx++)
        {
            uint64_t count = 0;
            for (int x = 0; x <= k; x++)
            {
                for (int y = 0; y <= k; y++)
                {
                    int x1 = points[i].first + dx + x;
                    int y1 = points[i].second + y;

                    if (s.find({x1, y1}) != s.end())
                    {
                        count++;
                    }
                }
            }

            max = std::max(max, count);
        }

        for (int dx = -k; dx <= 0; dx++)
        {
            uint64_t count = 0;
            for (int x = 0; x <= k; x++)
            {
                for (int y = 0; y <= k; y++)
                {
                    int x1 = points[i].first + x;
                    int y1 = points[i].second + dx + y;

                    if (s.find({x1, y1}) != s.end())
                    {
                        count++;
                    }
                }
            }

            max = std::max(max, count);
        }
    }

    cout << max << endl;

    return 0;
}