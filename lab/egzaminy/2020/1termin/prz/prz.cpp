#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int count_missing(int n, set<int> &a, set<int> &b)
{
    int max = n + 1;
    if (!b.empty())
    {
        max = *b.begin();
    }

    int min = 0;
    if (!a.empty())
    {
        min = *prev(a.end());
    }

    if (min == 0 && max == n + 1)
    {
        return n;
    }

    if (min == n || max == 1)
    {
        return 0;
    }

    if (min == 0)
    {
        return max - 1;
    }

    if (max == n + 1)
    {
        return n - min;
    }

    if (min >= max)
    {
        return 0;
    }

    return max - min - 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int count = 0;

    set<int> a;
    set<int> b;

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;

        int l, r;
        cin >> l >> r;

        if (c == '+')
        {
            if (l == 1)
            {
                a.insert(r);
            }
            else
            {
                b.insert(l);
            }
        }
        else
        {
            if (l == 1)
            {
                a.erase(r);
            }
            else
            {
                b.erase(l);
            }
        }

        cout << count_missing(n, a, b) << endl;
    }
}