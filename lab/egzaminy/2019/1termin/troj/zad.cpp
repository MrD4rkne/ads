#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int RANGE = 10;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> tab(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tab[i];
    }

    uint64_t result = 0;

    vector<uint64_t> cnt(RANGE + 1, 0);
    for (int i = 0; i < n; i++)
    {
        for (int a = 1; a < tab[i]; a++)
        {
            if (a + a == tab[i])
            {
                result += cnt[a] * (cnt[a] - 1);
            }
            else
            {
                result += cnt[a] * cnt[tab[i] - a];
            }
        }

        cnt[tab[i]]++;
    }

    cout << result / 2 << endl;

    return 0;
}