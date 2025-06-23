#include <bits/stdc++.h>

using namespace std;

class Node
{
private:
    size_t minProgrammersCount;
    vector<Node *> children;
    vector<Node *> parents;
    bool doesDepend;
    bool done;

public:
    Node(size_t programmersCount) : minProgrammersCount(programmersCount), doesDepend(false), done(false) {}

    size_t getMinProgrammersCount() const
    {
        return minProgrammersCount;
    }

    void addChild(Node *child)
    {
        children.push_back(child);
        child->addParent(this);
    }

    void addParent(Node *parent)
    {
        parents.push_back(parent);
        doesDepend = true;
    }

    Node *getChild(size_t index) const
    {
        return children[index];
    }

    size_t getChildrenCount() const
    {
        return children.size();
    }

    bool doesDepenend() const
    {
        return doesDepend;
    }

    void markDone()
    {
        done = true;
    }

    bool isDone() const
    {
        return done;
    }

    bool canBeWorkedOn()
    {
        return all_of(parents.begin(), parents.end(), [](Node *parent)
                      { return parent->isDone(); });
    }

    bool operator()(Node *a, Node *b)
    {
        return a->getMinProgrammersCount() > b->getMinProgrammersCount();
    }
};

struct CompareNode
{
    bool operator()(Node *a, Node *b)
    {
        return a->getMinProgrammersCount() > b->getMinProgrammersCount();
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<Node *> nodes(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        size_t programmersCount;
        cin >> programmersCount;

        nodes[i] = new Node(programmersCount);
    }

    for (size_t i = 0; i < m; i++)
    {
        size_t a, b;
        cin >> a >> b;

        nodes[b]->addChild(nodes[a]);
    }

    priority_queue<Node *, vector<Node *>, CompareNode> q;
    // Add all nodes without parents to the queue.
    for (size_t i = 1; i <= n; i++)
    {
        if (!nodes[i]->doesDepenend())
        {
            q.push(nodes[i]);
        }
    }

    size_t neededProgrammers = 0;
    for (size_t p = 1; p <= k; p++)
    {
        Node *node = q.top();
        q.pop();

        if (node->isDone())
        {
            // Should not happen, as only the last dependency can add it to the queue.
            return 1;
        }

        neededProgrammers = max(neededProgrammers, node->getMinProgrammersCount());
        node->markDone();

        for (size_t i = 0; i < node->getChildrenCount(); i++)
        {
            if (node->getChild(i)->canBeWorkedOn())
            {
                q.push(node->getChild(i));
            }
        }
    }

    cout << neededProgrammers << endl;

    return 0;
}