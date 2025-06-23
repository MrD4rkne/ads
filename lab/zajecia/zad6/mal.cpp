#include <iostream>
#include <math.h>

using namespace std;

enum class Action
{
    PAINTING,
    ROLLING,
    NONE
};

class Node
{
public:
    int min;
    int max;
    Node *left;
    Node *right;
    Node *parent;

    int sum;

    Node(int min, int max) : min(min), max(max), left(nullptr), right(nullptr), parent(nullptr), sum(0)
    {
    }

    bool is_leaf()
    {
        return left == nullptr && right == nullptr;
    }

    int size()
    {
        return max - min + 1;
    }

    bool is_fully_same()
    {
        return sum == size() || sum == 0;
    }

    int apply(Action action)
    {
        if (action == Action::NONE)
        {
            throw "Invalid action";
        }

        if (action == Action::PAINTING)
        {
            int ret = size() - sum;
            sum = size();
            return ret;
        }

        int ret = -sum;
        sum = 0;
        return ret;
    }
};

int midpoint(int left, int right)
{
    if (right - left == 1)
    {
        return left;
    }

    return (left + right) / 2;
}

static Node *init_node(int left, int right)
{
    Node *root = new Node(left, right);

    if (left == right)
    {
        return root;
    }

    int mid = midpoint(left, right);

    root->left = init_node(left, mid);
    root->left->parent = root;

    root->right = init_node(mid + 1, right);
    root->right->parent = root;

    return root;
}

void apply(Node *node, int left, int right, Action action, Action curr)
{
    left = max(left, node->min);
    right = min(right, node->max);

    if (curr == Action::NONE && node->is_fully_same())
    {
        curr = (node->sum == 0) ? Action::ROLLING : Action::PAINTING;
    }

    if (curr != Action::NONE)
    {
        node->apply(curr);
    }

    if (node->min == left && node->max == right)
    {
        int difference = node->apply(action);

        if (!node->is_leaf())
        {
            node->left->apply(action);
            node->right->apply(action);
        }

        Node *parent = node->parent;
        Node *child = node;
        while (parent != nullptr)
        {
            if (parent->is_fully_same())
            {
                Action parentAction = (parent->sum == 0) ? Action::ROLLING : Action::PAINTING;
                Node *otherChild = parent->left == child ? parent->right : parent->left;
                otherChild->apply(parentAction);
            }

            parent->sum += difference;

            child = parent;
            parent = child->parent;
        }

        return;
    }

    if (node->left->max >= left)
    {
        apply(node->left, left, right, action, curr);
    }

    if (node->right->min <= right)
    {
        apply(node->right, left, right, action, curr);
    }
}

int main()
{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int smallestBiggerThanNPowerOfTwo = pow(2, (int)ceil(log2(n)));
    Node *tree = init_node(1, smallestBiggerThanNPowerOfTwo);

    for (int event = 0; event < m; event++)
    {
        int a, b;
        cin >> a >> b;

        char action;
        cin >> action;

        Action actionType = action == 'B' ? Action::PAINTING : Action::ROLLING;
        apply(tree, a, b, actionType, Action::NONE);

        cout << tree->sum << endl;
    }

    return 0;
}