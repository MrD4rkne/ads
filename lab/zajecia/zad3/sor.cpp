#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const size_t M = 1E+9;

struct input
{
    int l;
    int r;
    bool wasLeft;

    // Equality operator for comparing two input structs
    bool operator==(const input &other) const
    {
        return l == other.l && r == other.r && wasLeft == other.wasLeft;
    }
};

// Custom hash function for input struct
struct InputHash
{
    std::size_t operator()(const input &in) const
    {
        std::size_t hash = 0;
        // Combine the hash of each member
        hash ^= std::hash<int>{}(in.l) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<int>{}(in.r) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<bool>{}(in.wasLeft) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};

size_t policz(const int tab[], unordered_map<input, size_t, InputHash> &results, int l, int r, bool wasLeft)
{
    input in = {l, r, wasLeft};
    auto it = results.find(in);
    if (it == results.end())
    {
        size_t m = -1;

        if (tab[l] > tab[r])
        {
            m = 0;
        }

        if (m == -1 && l == r)
        {
            m = 1;
        }

        if (m == -1 && r - l == 1)
        {
            if ((wasLeft && tab[l] < tab[l - 1]) || (!wasLeft && tab[r + 1] < tab[r]))
            {
                m = 1;
            }
            else
            {
                m = 2;
            }
        }

        if (m == -1 && wasLeft && tab[l] < tab[l - 1])
        {
            m = policz(tab, results, l, r - 1, false);
        }

        if (m == -1 && !wasLeft && tab[r + 1] < tab[r])
        {
            m = policz(tab, results, l + 1, r, true);
        }

        if (m == -1)
        {
            m = policz(tab, results, l + 1, r, true);
            m += policz(tab, results, l, r - 1, false);
        }

        results[in] = m % M;
    }

    return results[in];
}

int main()
{
    int n;
    cin >> n;

    int tab[n + 1];
    tab[0] = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> tab[i + 1];
    }

    unordered_map<input, size_t, InputHash> results;
    cout << policz(tab, results, 1, n, true) << endl;
}