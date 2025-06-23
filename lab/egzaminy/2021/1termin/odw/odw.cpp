#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct rev
{
    int i;
    bool start;
    int a;
    int b;

    bool operator()(const rev &a, const rev &b)
    {
        if (a.i == b.i)
        {
            return a.start;
        }

        return a.i < b.i;
    }
} rev_t;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string text(n + 1, ' ');
    for (int i = 1; i <= n; i++)
    {
        cin >> text[i];
    }

    vector<rev_t> revs;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        revs.push_back({a, true, a, b});
        revs.push_back({b, false, a, b});
    }

    sort(revs.begin(), revs.end(), rev_t());

    int parity = 0;
    int prev = 0;
    for (auto &r : revs)
    {
        if (r.start)
        {
            prev = ((r.b + r.a) / 2) + 1;
        }

        if (!r.start)
        {
            if (parity == 1)
            {
                for (int j = prev; j <= r.b; j++)
                {
                    int i = r.a + r.b - j;
                    swap(text[j], text[i]);
                }
            }

            prev = r.b + 1;
        }

        parity = (parity + 1) % 2;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << text[i];
    }

    cout << "\n";

    return 0;
}