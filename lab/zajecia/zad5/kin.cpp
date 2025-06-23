#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Node
{
public:
    int min;
    int max;
    Node *left;
    Node *right;
    Node *parent;

    vector<uint32_t> values;

    Node(int min, int max, int k) : min(min), max(max), left(nullptr), right(nullptr), parent(nullptr), values(k, 0)
    {
    }

    bool is_leaf()
    {
        return left == nullptr && right == nullptr;
    }
};

static Node *init_node(int left, int right, int k)
{
    Node *root = new Node(left, right, k);

    if (left == right)
    {
        return root;
    }

    int mid = (left + right) / 2;
    if (right - left == 1)
    {
        mid = left;
    }

    root->left = init_node(left, mid, k);
    root->left->parent = root;

    root->right = init_node(mid + 1, right, k);
    root->right->parent = root;

    return root;
}

void destroy_tree(Node *&root)
{
    if (root == nullptr)
    {
        return;
    }

    destroy_tree(root->left);
    destroy_tree(root->right);

    delete root;
    root = nullptr;
}

static Node *init_tree(const int n, const int k)
{
    return init_node(1, n, k);
}

const uint32_t MOD = 1000000000;

uint32_t add(uint32_t a, uint32_t b)
{
    return (a + (b % MOD)) % MOD;
}

static void update(Node *leaf, int value, bool previousLeft, vector<uint32_t> &added)
{
    if (previousLeft)
    {
        Node *right = leaf->right;
        for (int i = 1; i < added.size(); i++)
        {
            added[i] = add(added[i], right->values[i - 1]);
        }
    }

    if (leaf->parent != nullptr)
    {
        update(leaf->parent, value, leaf->parent->left == leaf, added);
    }

    for (int i = 0; i < added.size(); i++)
    {
        leaf->values[i] = add(leaf->values[i], added[i]);
    }
}

static void insert(Node *tree, int value, const int k)
{
    tree->values[0]++;

    if (tree->is_leaf())
    {
        if (tree->parent == nullptr)
        {
            return;
        }

        vector<uint32_t> added(k, 0);
        update(tree, value, false, added);
        return;
    }

    int mid = (tree->min + tree->max) / 2;
    if (value <= mid)
    {
        insert(tree->left, value, k);
    }
    else
    {
        insert(tree->right, value, k);
    }
}

int main()
{
    int n, k;
    cin >> n >> k;

    int pow2 = pow(2, (int)ceil(log2(n)));
    Node *tree = init_tree(pow2, k);

    for (int i = 0; i < n; i++)
    {
        int value;

        cin >> value;
        insert(tree, value, k);
    }

    cout << tree->values[k - 1] << endl;

    destroy_tree(tree);

    return 0;
}