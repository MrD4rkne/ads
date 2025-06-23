#include <iostream>
#include <vector>
#include <array>
#include <math.h>

using namespace std;

class Tree;

class Node
{
public:
    /// @brief Left bound of the range.
    int min;

    /// @brief Right bound of the range.
    int max;

    /// @brief Position in the tree's array.
    int pos;

    /// @brief Pointer to the tree.
    Tree *tree;

    /// @brief Length of the inner non-decreasing sequence up to the end of the range.
    int endLength;

    /// @brief Length of the longest inner non-decreasing sequence inside the range.
    int middleLength;

    /// @brief Length of the inner non-decreasing sequence starting from the beginning of the range.
    int startLength;

    /// @brief Relative value of the node (sum of all fertilizations).
    int val;

    /// @brief Relative value of the most left element in the range.
    int low;

    /// @brief Relative value of the most right element in the range.
    int high;

    /// @brief Default constructor for Node.
    Node() : min(0), max(0), pos(0), tree(nullptr), endLength(max - min + 1), startLength(max - min + 1), val(0) {}

    /// @brief Get the left child of the node. Nullptr if the node is a leaf.
    Node *left();

    /// @brief Get the right child of the node. Nullptr if the node is a leaf.
    Node *right();

    /// @brief Get the parent of the node. Nullptr if the node is the root.
    Node *parent();

    /// @brief Check if the node is a leaf.
    /// @return True if the node is a leaf; otherwise, false.
    bool is_leaf()
    {
        return min == max;
    }

    /// @brief Get the size of the range.
    /// @return Size of the range.
    int size()
    {
        return max - min + 1;
    }

    /// @brief Fertilize the range from 'from' to 'to' with 'k'.
    /// @param from Start of the range.
    /// @param to End of the range.
    /// @param k Value to add.
    /// @param add Additional value to propagate.
    void fertilize(int from, int to, int k, int add);

    /// @brief Initialize the node.
    /// @param pos Position in the tree array.
    /// @param min Left bound of the range.
    /// @param max Right bound of the range.
    void init(int pos, int min, int max);

    /// @brief Get the lengths of the inner non-decreasing sequence in the range.
    /// @brief {from start of the range, longest, up to the end of the range}
    /// @param from Start of the range.
    /// @param to End of the range.
    /// @param add Additional value to propagate.
    /// @return Array of {start, middle, end} lengths.
    std::array<int, 3> get_lengths_of_nondecreasing_subsequences(int from, int to, int add = 0)
    {
        if (from > max || to < min)
        {
            // Out of range
            return {0, 0, 0};
        }

        if (from <= min && to >= max)
        {
            // Fully within range
            return {startLength, middleLength, endLength};
        }

        add += val;

        // Query left and right children
        auto leftResult = left()->get_lengths_of_nondecreasing_subsequences(from, to, add);
        auto rightResult = right()->get_lengths_of_nondecreasing_subsequences(from, to, add);

        // Merge results
        int mergedStart = leftResult[0];
        int mergedEnd = rightResult[2];
        int middle = std::max(leftResult[1], rightResult[1]);
        middle = std::max(middle, std::max(leftResult[2], rightResult[0]));

        int leftHigh = left()->high + add;
        int rightLow = right()->low + add;
        if (leftHigh <= rightLow)
        {
            middle = std::max(middle, leftResult[2] + rightResult[0]);

            if (leftResult[0] == left()->size())
            {
                mergedStart += rightResult[0];
            }

            if (rightResult[2] == right()->size())
            {
                mergedEnd += leftResult[2];
            }
        }

        return {mergedStart, middle, mergedEnd};
    }
};

class Tree
{
public:
    /// @brief Constructor for Tree.
    /// @param size Size of the tree.
    Tree(int size) : size(size)
    {
        nodes.resize(size * 2);
        for (int i = 0; i < size * 2; i++)
        {
            nodes[i].tree = this;
        }

        /// @brief Initialize the tree starting from the root.
        get_root()->init(1, 1, size);
    }

    /// @brief Get the root node of the tree.
    /// @return Pointer to the root node.
    Node *get_root()
    {
        return &nodes[1];
    }

    /// @brief Get the node at the given index.
    /// @param index Index of the node.
    /// @return Pointer to the node or nullptr if out of bounds.
    Node *get_node(int index)
    {
        if (index < 1 || index >= size * 2)
        {
            return nullptr;
        }
        return &nodes[index];
    }

    /// @brief Get the length of the longest non-decreasing subsequence in a range.
    /// @param from Start of the range.
    /// @param to End of the range.
    /// @return Length of the longest non-decreasing subsequence.
    int get_length_of_longest_nondecreasing_subsequence(int from, int to)
    {
        auto result = get_root()->get_lengths_of_nondecreasing_subsequences(from, to);
        return std::max(std::max(result[0], result[1]), result[2]);
    }

    /// @brief Get the size of the tree.
    /// @return Size of the tree.
    int get_size()
    {
        return size;
    }

private:
    /// @brief Size of the tree.
    int size;

    /// @brief Nodes of the tree.
    vector<Node> nodes;
};

Node *Node::left()
{
    return tree->get_node(pos * 2);
}

Node *Node::right()
{
    return tree->get_node((pos * 2) + 1);
}

Node *Node::parent()
{
    return tree->get_node(pos / 2);
}

void Node::init(int pos, int min, int max)
{
    this->pos = pos;
    this->min = min;
    this->max = max;
    this->endLength = max - min + 1;
    this->startLength = max - min + 1;
    this->middleLength = max - min + 1;
    this->val = 0;
    this->low = 1;
    this->high = 1;

    if (min == max)
    {
        this->val = 1;
        return;
    }

    int mid = (min + max) / 2;
    left()->init(2 * pos, min, mid);
    right()->init((2 * pos) + 1, mid + 1, max);
}

void Node::fertilize(int from, int to, int k, int add = 0)
{
    if (from > max || to < min)
    {
        return;
    }

    from = std::max(from, min);
    to = std::min(to, max);

    if (from <= min && to >= max)
    {
        val += k;
        low += k;
        high += k;
        return;
    }

    add += val;

    left()->fertilize(from, to, k, add);
    right()->fertilize(from, to, k, add);

    low = left()->low + val;
    high = right()->high + val;

    endLength = right()->endLength;
    startLength = left()->startLength;
    middleLength = std::max(left()->middleLength, right()->middleLength);
    middleLength = std::max(middleLength, std::max(left()->endLength, right()->startLength));

    int leftHigh = left()->high + add;
    int rightLow = right()->low + add;

    if (leftHigh <= rightLow)
    {
        if (right()->endLength == right()->size())
        {
            endLength += left()->endLength;
        }

        if (left()->startLength == left()->size())
        {
            startLength += right()->startLength;
        }

        middleLength = std::max(middleLength, left()->endLength + right()->startLength);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int smallestBiggerThanNPowerOfTwo = pow(2, (int)ceil(log2(n)));
    Tree *tree = new Tree(smallestBiggerThanNPowerOfTwo);

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;
        int l, r;
        cin >> l >> r;

        switch (c)
        {
        case 'N':
        {
            int k;
            cin >> k;
            tree->get_root()->fertilize(l, r, k, 0);
            break;
        }
        case 'C':
            cout << tree->get_length_of_longest_nondecreasing_subsequence(l, r) << endl;
            break;
        default:
            // Wrong action.
            return 1;
        }
    }

    return 0;
}