#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct step step_t;

struct step
{
    int length, x;
    bool operator()(const step_t &a, const step_t &b) const
    {
        return a.length > b.length;
    }
};

void shortestPath(const vector<vector<pair<int, int>>> &edges, vector<int> &shortest, int n)
{
    priority_queue<step_t, vector<step_t>, step_t> q;
    q.push({0, n});

    shortest[n] = 0;

    while (!q.empty())
    {
        step_t current = q.top();
        q.pop();

        if (current.length > shortest[current.x])
        {
            continue;
        }

        for (auto &edge : edges[current.x])
        {
            if (current.length + edge.second < shortest[edge.first])
            {
                q.push({current.length + edge.second, edge.first});
                shortest[edge.first] = current.length + edge.second;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> edges(n + 1);
    for (size_t i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        edges[a].push_back({b, w});
        edges[b].push_back({a, w});
    }

    for (size_t i = 1; i <= n; i++)
    {
        sort(edges[i].begin(), edges[i].end());
    }

    vector<int> shortest(n + 1, INT_MAX);

    shortestPath(edges, shortest, n);

    int shortestPath = shortest[1];
    int curr = 1;
    int currL = 0;
    while (curr != n)
    {
        cout << curr << " ";
        for (auto &edge : edges[curr])
        {
            if (currL + shortest[edge.first] + edge.second == shortestPath)
            {
                currL += edge.second;
                curr = edge.first;
                break;
            }
        }
    }

    if (n > 1)
    {
        cout << n;
    }

    cout << endl;

    return 0;
}