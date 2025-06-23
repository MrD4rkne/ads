#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef struct node
{
    int min;
    int max;
    int index;
    int sort;
    int ile0;
} node_t;

int init_nodes(vector<node_t> &tree, const vector<int> &tab, int i, int min, int max)
{
    tree[i].min = min;
    tree[i].max = max;
    tree[i].sort = 0;
    tree[i].index = i;
    if (min == max)
    {
        if (min <= tab.size())
        {
            tree[i].ile0 = tab[min] == 0 ? 1 : 0;
        }
        else
        {
            tree[i].ile0 = 1;
        }
    }
    else
    {
        int mid = (min + max) / 2;
        tree[i].ile0 = init_nodes(tree, tab, 2 * i, min, mid);
        tree[i].ile0 += init_nodes(tree, tab, 2 * i + 1, mid + 1, max);
    }

    return tree[i].ile0;
}

void init(vector<node_t> &tree, const vector<int> &tab)
{
    int n = tab.size() - 1;
    int closestPowerOfTwo = pow(2, ceil(log2(n)));
    init_nodes(tree, tab, 1, 1, closestPowerOfTwo);
}

void apply(vector<node_t> &tree, int i)
{
    if (i >= tree.size())
        return;

    if (tree[i].sort == 0)
        return;

    if (tree[i].min == tree[i].max)
    {
        return;
    }

    if (tree[i].sort == 1)
    {
        tree[2 * i].sort = 1;
        tree[2 * i].ile0 = std::min(tree[i].ile0, tree[2 * i].max - tree[2 * i].min + 1);

        tree[2 * i + 1].sort = 1;
        tree[2 * i + 1].ile0 = tree[i].ile0 - tree[2 * i].ile0;
    }
    else
    {
        tree[2 * i].sort = -1;
        tree[2 * i + 1].sort = -1;
        tree[2 * i + 1].ile0 = std::min(tree[i].ile0, tree[2 * i].max - tree[2 * i].min + 1);
        tree[2 * i].ile0 = tree[i].ile0 - tree[2 * i + 1].ile0;
    }

    tree[i].sort = 0;
}

int count_zeros(vector<node_t> &tree, int i, int a, int b)
{
    apply(tree, i);

    if (tree[i].min > b || tree[i].max < a)
        return 0;

    if (tree[i].min >= a && tree[i].max <= b)
        return tree[i].ile0;

    return count_zeros(tree, 2 * i, a, b) + count_zeros(tree, 2 * i + 1, a, b);
}

void sort(vector<node_t> &tree, int k, int i, int j, bool nonIncreasing, int zerosCount)
{
    apply(tree, k);

    if (k >= tree.size())
        return;

    if (tree[k].min > j || tree[k].max < i)
        return;

    if (tree[k].min >= i && tree[k].max <= j)
    {

        if (nonIncreasing)
        {
            tree[k].sort = 1;
            tree[k].ile0 = std::min(std::max(zerosCount - (tree[k].min - i), 0), tree[k].max - tree[k].min + 1);
        }
        else
        {
            tree[k].sort = -1;
            tree[k].ile0 = std::min(std::max(zerosCount - (j - tree[k].max), 0), tree[k].max - tree[k].min + 1);
        }

        apply(tree, k);
        return;
    }

    if (tree[k].min == tree[k].max)
        return;

    sort(tree, 2 * k, i, j, nonIncreasing, zerosCount);
    sort(tree, 2 * k + 1, i, j, nonIncreasing, zerosCount);

    tree[k].ile0 = tree[2 * k].ile0 + tree[2 * k + 1].ile0;
}

int get(vector<node_t> &tree, int currI, int i)
{
    apply(tree, currI);

    if (tree[currI].min == tree[currI].max)
        return tree[currI].ile0 == 1 ? 0 : 1;

    int mid = (tree[currI].min + tree[currI].max) / 2;
    if (i <= mid)
        return get(tree, 2 * currI, i);
    else
        return get(tree, 2 * currI + 1, i);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        arr[i] = c - '0';
    }

    vector<node_t> tree(5 * n);
    init(tree, arr);

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;

        switch (c)
        {
        case '?':
        {
            int i;
            cin >> i;
            cout << get(tree, 1, i) << endl;
            break;
        }
        case '>':
        case '<':
        {
            int a, b;
            cin >> a >> b;

            int allZeros = count_zeros(tree, 1, a, b);
            sort(tree, 1, a, b, c == '<', allZeros);
            break;
        }
        }
    }

    return 0;
}