#include <iostream>
#include <set>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    set<int> S = {0, n};   // Stores positions
    multiset<int> G = {n}; // Stores segment sizes

    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;

        auto it = S.lower_bound(x); // Find the first element >= x
        int right = *it;
        int left = *prev(it);

        G.erase(G.find(right - left)); // Remove the old segment
        G.insert(x - left);            // Insert new left segment
        G.insert(right - x);           // Insert new right segment

        S.insert(x); // Add x to the set

        cout << *G.rbegin() << "\n"; // Maximum segment size
    }

    return 0;
}
