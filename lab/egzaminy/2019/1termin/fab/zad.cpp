#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int FACTORY_TYPES = 10;

typedef struct step step_t;

struct step
{
    int from;
    int prev;
    int factory;
    uint64_t distance;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> factories(n + 1);
    vector<vector<int>> factoriesByType(FACTORY_TYPES + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> factories[i];
        factoriesByType[factories[i]].push_back(i);
    }

    vector<vector<int>> edges(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    uint64_t result = 0;
    for (int i = 1; i <= FACTORY_TYPES; i++)
    {
        result = std::max(result, maximum_closest_factory(factories, factoriesByType, edges, i));
    }

    cout << result << endl;

    return 0;
}