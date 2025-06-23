#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

void dfs(const vector<unordered_set<int>> &edges, vector<bool> &visited, vector<int> &path, int elem)
{
    path.push_back(elem);
    visited[elem] = true;
    for (int next : edges[elem])
    {
        if (!visited[next])
        {
            dfs(edges, visited, path, next);
        }

        path.push_back(elem);
    }
}

bool fast_dfs(const vector<unordered_set<int>> &edges, vector<bool> &visited, vector<int> &path, int elem)
{
    visited[elem] = true;

    if (elem == edges.size() - 1)
    {
        path.push_back(elem);
        return true;
    }

    for (int next : edges[elem])
    {
        if (!visited[next])
        {
            if (fast_dfs(edges, visited, path, next))
            {
                path.push_back(elem);
                return true;
            }
        }
    }

    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<unordered_set<int>> edges(n + 1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        edges[a].insert(b);
        edges[b].insert(a);
    }

    vector<int> pathStartToFinish;
    pathStartToFinish.reserve(n);
    vector<bool> temp(n + 1, false);
    fast_dfs(edges, temp, pathStartToFinish, 1);

    vector<bool> visited(n + 1, false);
    for (int i = 0; i < pathStartToFinish.size(); i++)
    {
        visited[pathStartToFinish[i]] = true;
    }

    vector<int> path;
    path.reserve(2 * n);

    for (int i = pathStartToFinish.size() - 1; i >= 0; i--)
    {
        dfs(edges, visited, path, pathStartToFinish[i]);
    }

    std::vector<int> nonRepeatedPath;
    nonRepeatedPath.reserve(2 * n);

    nonRepeatedPath.push_back(path[0]);

    for (int i = 1; i < path.size(); i++)
    {
        if (path[i] != path[i - 1])
        {
            nonRepeatedPath.push_back(path[i]);
        }
    }

    std::cout << nonRepeatedPath.size() << std::endl;

    for (int i = 0; i < nonRepeatedPath.size(); i++)
    {
        cout << nonRepeatedPath[i] << " ";
    }

    cout << endl;

    return 0;
}