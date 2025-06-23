#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    Node(int x, int y) : x(x), y(y), visited(false) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void addEdge(Node *node, int weight)
    {
        edges.push_back({node, weight});
    }

    const vector<pair<Node *, int>> &getEdges() const { return edges; }

    bool isVisited() const { return visited; }

    void markVisited() { visited = true; }

private:
    int x, y;
    vector<pair<Node *, int>> edges;
    bool visited;
};

inline int calculateDistance(Node *a, Node *b)
{
    return min(abs(a->getX() - b->getX()), abs(a->getY() - b->getY()));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Node *> islands(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        islands[i] = new Node(x, y);
    }

    Node *first = islands[0];
    Node *last = islands[n - 1];

    // Create edges by sorting based on x and y coordinates
    auto addEdges = [&islands](auto comparator)
    {
        sort(islands.begin(), islands.end(), comparator);
        for (int i = 1; i < islands.size(); i++)
        {
            int distance = calculateDistance(islands[i - 1], islands[i]);
            islands[i - 1]->addEdge(islands[i], distance);
            islands[i]->addEdge(islands[i - 1], distance);
        }
    };

    // Sort by x-coordinate and add edges
    addEdges([](Node *a, Node *b)
             { return a->getX() < b->getX(); });
    // Sort by y-coordinate and add edges
    addEdges([](Node *a, Node *b)
             { return a->getY() < b->getY(); });

    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<>> pq;

    int minDistance = INT_MAX;
    pq.push({0, first});
    while (!pq.empty())
    {
        auto [distance, node] = pq.top();
        pq.pop();

        if (node == last)
        {
            minDistance = distance;
            break;
        }

        if (node->isVisited())
            continue;

        node->markVisited();

        for (auto child : node->getEdges())
        {
            auto [next, weight] = child;
            if (!next->isVisited())
            {
                pq.push({distance + weight, next});
            }
        }
    }

    cout << minDistance << endl;

    for (Node *node : islands)
    {
        delete node;
    }

    return 0;
}
