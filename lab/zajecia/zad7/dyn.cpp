#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
    size_t getTotalSize() const
    {
        return count + childrenCount;
    }

    Node(T key, size_t count) : Node(key, count, nullptr) {}

    Node(T key, size_t count, Node<T> *parent) : key(key), count(count), childrenCount(0), leftChild(nullptr), rightChild(nullptr), parent(parent) {}

    Node *getParent() const
    {
        return parent;
    }

    void setParent(Node *parent)
    {
        this->parent = parent;
    }

    Node<T> *getRightChild() const
    {
        return rightChild;
    }

    Node<T> *getLeftChild() const
    {
        return leftChild;
    }

    bool hasLeftChild() const
    {
        return leftChild != nullptr;
    }

    bool hasRightChild() const
    {
        return rightChild != nullptr;
    }

    bool isRoot() const
    {
        return parent == nullptr;
    }

    void setRightChild(Node<T> *rightChild)
    {
        this->rightChild = rightChild;

        if (rightChild != nullptr)
        {
            rightChild->setParent(this);
        }
    }

    void setLeftChild(Node<T> *leftChild)
    {
        this->leftChild = leftChild;

        if (leftChild != nullptr)
        {
            leftChild->setParent(this);
        }
    }

    void switchChild(Node<T> *oldChild, Node<T> *newChild)
    {
        if (leftChild == oldChild)
        {
            setLeftChild(newChild);
        }
        else if (rightChild == oldChild)
        {
            setRightChild(newChild);
        }
    }

    T getKey() const
    {
        return key;
    }

    size_t getCount() const
    {
        return count;
    }

    void updateChildrenCount()
    {
        childrenCount = 0;
        if (leftChild != nullptr)
        {
            childrenCount += leftChild->getTotalSize();
        }
        if (rightChild != nullptr)
        {
            childrenCount += rightChild->getTotalSize();
        }
    }

private:
    Node<T> *parent;
    Node<T> *leftChild;
    Node<T> *rightChild;
    size_t childrenCount;

    T key;
    size_t count;
};

template <typename T>
Node<T> *rotateRight(Node<T> *node)
{
    Node<T> *newRoot = node->getLeftChild();
    if (newRoot == nullptr)
    {
        return node;
    }

    Node<T> *tmp = node->getParent();

    node->setLeftChild(newRoot->getRightChild());
    newRoot->setRightChild(node);
    newRoot->setParent(tmp);

    node->updateChildrenCount();
    newRoot->updateChildrenCount();

    if (!newRoot->isRoot())
    {
        newRoot->getParent()->switchChild(node, newRoot);
        newRoot->getParent()->updateChildrenCount();
    }

    return newRoot;
}

template <typename T>
Node<T> *rotateLeft(Node<T> *node)
{
    Node<T> *newRoot = node->getRightChild();
    if (newRoot == nullptr)
    {
        return node;
    }

    Node<T> *tmp = node->getParent();

    node->setRightChild(newRoot->getLeftChild());
    newRoot->setLeftChild(node);
    newRoot->setParent(tmp);

    node->updateChildrenCount();
    newRoot->updateChildrenCount();

    if (newRoot->getParent() != nullptr)
    {
        if (newRoot->getParent()->getLeftChild() == node)
        {
            newRoot->getParent()->setLeftChild(newRoot);
        }
        else
        {
            newRoot->getParent()->setRightChild(newRoot);
        }
    }

    return newRoot;
}

template <typename T>
void splay(Node<T> *node)
{
    while (node->getParent() != nullptr)
    {
        if (node->getParent()->getParent() == nullptr)
        {
            if (node->getParent()->getLeftChild() == node)
            {
                rotateRight(node->getParent());
            }
            else
            {
                rotateLeft(node->getParent());
            }
            continue;
        }

        Node<T> *parent = node->getParent();
        Node<T> *grandParent = parent->getParent();

        if (grandParent->getLeftChild() == parent && parent->getLeftChild() == node)
        {
            rotateRight(grandParent);
            rotateRight(parent);
            continue;
        }

        if (grandParent->getRightChild() == parent && parent->getRightChild() == node)
        {
            rotateLeft(grandParent);
            rotateLeft(parent);
            continue;
        }

        if (grandParent->getLeftChild() == parent && parent->getRightChild() == node)
        {
            rotateLeft(parent);
            rotateRight(grandParent);
            continue;
        }

        rotateRight(parent);
        rotateLeft(grandParent);
    }
}

template <typename T>
Node<T> *find(Node<T> *root, size_t *pos)
{
    Node<T> *node = root;
    while (true)
    {
        if (node->getLeftChild() != nullptr && *pos < node->getLeftChild()->getTotalSize())
        {
            node = node->getLeftChild();
            continue;
        }

        *pos -= node->getLeftChild() != nullptr ? node->getLeftChild()->getTotalSize() : 0;
        if (*pos < node->getCount())
        {
            return node;
        }

        *pos -= node->getCount();

        if (node->getRightChild() == nullptr)
        {
            return node;
        }

        node = node->getRightChild();
    }
}

template <typename T>
Node<T> *insert(Node<T> *root, size_t pos, T key, size_t count)
{
    if (root == nullptr)
    {
        return new Node<T>(key, count); // Create the root if the tree is empty
    }

    size_t temp = pos;
    size_t size = root->getTotalSize();

    Node<T> *node = find(root, &pos); // Find the node or position

    if (temp == 0)
    {
        // Insert as a new left child
        Node<T> *newNode = new Node<T>(key, count);
        node->setLeftChild(newNode); // Disconnect previous left links
        node->updateChildrenCount();

        splay(newNode);
        return newNode;
    }

    if (temp >= size)
    {
        // Insert as a new right child
        Node<T> *newNode = new Node<T>(key, count);
        node->setRightChild(newNode); // Disconnect previous right links
        node->updateChildrenCount();

        splay(newNode);
        return newNode;
    }

    Node<T> *leftSplit = nullptr;
    if (pos > 0)
    {
        leftSplit = new Node<T>(node->getKey(), pos);
    }

    Node<T> *rightSplit = nullptr;
    if (pos < node->getCount())
    {
        rightSplit = new Node<T>(node->getKey(), node->getCount() - pos);
    }

    Node<T> *newNode = new Node<T>(key, count);

    if (leftSplit)
    {
        leftSplit->setLeftChild(node->getLeftChild());
        leftSplit->updateChildrenCount();
        newNode->setLeftChild(leftSplit);
    }
    else
    {
        newNode->setLeftChild(node->getLeftChild());
    }

    if (rightSplit)
    {
        rightSplit->setRightChild(node->getRightChild());
        rightSplit->updateChildrenCount();
        newNode->setRightChild(rightSplit);
    }
    else
    {
        newNode->setRightChild(node->getRightChild());
    }

    newNode->updateChildrenCount();

    if (node->getParent() != nullptr)
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(newNode);
        }
        else
        {
            node->getParent()->setRightChild(newNode);
        }

        node->getParent()->updateChildrenCount();
    }

    delete node;

    splay(newNode);
    return newNode;
}

void deleteTree(Node<size_t> *root)
{
    if (root == nullptr)
    {
        return;
    }

    deleteTree(root->getLeftChild());
    deleteTree(root->getRightChild());
    delete root;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    cin >> m;

    size_t n = 0;
    size_t w = 0;

    Node<size_t> *root = nullptr;
    for (int i = 0; i < m; i++)
    {
        char op;
        cin >> op;

        size_t jp, x, k;
        cin >> jp;
        if (op == 'i')
        {
            cin >> x >> k;
            n += 1;
        }

        size_t j = (jp + w) % n;

        if (op == 'i')
        {
            root = insert(root, j, x, k);
            n = root->getTotalSize();
        }
        else
        {
            Node<size_t> *node = find(root, &j);
            splay(node);
            root = node;

            w = root->getKey();
            cout << w << "\n";
        }
    }

    deleteTree(root);
    return 0;
}