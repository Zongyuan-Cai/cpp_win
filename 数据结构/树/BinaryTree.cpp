#include <iostream>
#include <algorithm>
const int stackSize = 1024;

template <typename T>
struct BinaryTreeNode
{
    T data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode()
        : data(T()), left(nullptr), right(nullptr) {}
    BinaryTreeNode(const T &value)
        : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree
{
private:
    BinaryTreeNode<T> *root;
    T RefValue;

    void destroy(BinaryTreeNode<T> *node);                                                //
    void createBinTree(const T arr[], BinaryTreeNode<T> *&node);                          //
    void createBinTree(const T arr[], BinaryTreeNode<T> *&node, int &index);              //
    BinaryTreeNode<T> *Parent(BinaryTreeNode<T> *node, BinaryTreeNode<T> *current) const; //
    BinaryTreeNode<T> *Search(BinaryTreeNode<T> *node, const T &value) const;
    int Insert(BinaryTreeNode<T> *&node, const T &value);
    BinaryTreeNode<T> *Copy(BinaryTreeNode<T> *node) const;
    int Height(BinaryTreeNode<T> *node) const;
    int Size(BinaryTreeNode<T> *node) const;
    void printBinTree(BinaryTreeNode<T> *node) const;
    void Traverse(BinaryTreeNode<T> *node, int level) const;
    void PreOrder(BinaryTreeNode<T> *node) const;
    void InOrder(BinaryTreeNode<T> *node) const;
    void PostOrder(BinaryTreeNode<T> *node) const;
    bool Equal(BinaryTreeNode<T> *node1, BinaryTreeNode<T> *node2) const;

public:
    BinaryTree() : root(nullptr), RefValue(T()) {}
    BinaryTree(const T &refValue) : root(nullptr), RefValue(refValue) {}
    BinaryTree(const BinaryTree &other)
        : root(other.root), RefValue(other.RefValue) {}
    ~BinaryTree() { destroy(root); }
    bool isEmpty() const { return root == nullptr; }

    BinaryTreeNode<T> *Parent(BinaryTreeNode<T> *node) const { return Parent(root, node); }
    int Height() const { return Height(root); }
    int Size() const { return Size(root); }
    BinaryTreeNode<T> *getRoot() const { return root; }
    void setRoot(BinaryTreeNode<T> *node) { root = node; }
    BinaryTreeNode<T> *Search(const T &value) const { return Search(root, value); }
    int Insert(const T &value) { return Insert(root, value); }
    void createBinTree(T arr[]) { createBinTree(arr, root); }
    void printBinTree() const { printBinTree(root); }
    void Traverse(int k) const { Traverse(root, k); }
    void PreOrder() const { PreOrder(root); }
    void InOrder() const { InOrder(root); }
    void PostOrder() const { PostOrder(root); }
    bool operator==(const BinaryTree &other) const { return Equal(root, other.root); }
};

template <typename T>
void destroy(BinaryTreeNode<T> *&node)
{
    if (node == nullptr)
        return;

    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
} // post-order

template <typename T>
BinaryTreeNode<T> *BinaryTree<T>::Parent(BinaryTreeNode<T> *node, BinaryTreeNode<T> *current) const
{
    if (node == nullptr || current == nullptr)
        return nullptr;

    if (node->left == current || node->right == current)
        return node;

    BinaryTreeNode<T> *parent = nullptr;

    if (node->left != nullptr)
    {
        parent = Parent(node->left, current);
        if (parent != nullptr)
            return parent;
    }

    if (node->right != nullptr)
        return Parent(node->right, current);

    return nullptr;
}

template <typename T>
void BinaryTree<T>::Traverse(BinaryTreeNode<T> *node, int level) const
{
    if (node == nullptr || level < 1)
        return;

    if (level == 1)
    {
        std::cout << node->data << " ";
        return;
    }

    Traverse(node->left, level - 1);
    Traverse(node->right, level - 1);
}

template <typename T>
void BinaryTree<T>::createBinTree(const T arr[], BinaryTreeNode<T> *&node)
{
    const int stackSize = 100;
    BinaryTreeNode<T> *stack[stackSize];
    int top = -1;

    BinaryTreeNode<T> *p = nullptr;
    int flag = 0;
    int k = 0;
    T ch;

    node = nullptr;

    ch = arr[k++];
    while (ch != '\0')
    {
        switch (ch)
        {
        case '(':
            stack[++top] = p;
            flag = 1;
            break;

        case ')':
            top--;
            break;

        case ',':
            flag = 2;
            break;

        case '#':
            break;

        default:
            p = new BinaryTreeNode<T>(ch);

            if (node == nullptr)
            {
                node = p;
            }
            else
            {
                if (flag == 1)
                    stack[top]->left = p;
                else if (flag == 2)
                    stack[top]->right = p;
            }
            break;
        }

        ch = arr[k++];
    }
}

template <typename T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return;
    InOrder(node->left);
    std::cout << node->data << " ";
    InOrder(node->right);
}

template <typename T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return;
    std::cout << node->data << " ";
    PreOrder(node->left);
    PreOrder(node->right);
}

template <typename T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return;
    PostOrder(node->left);
    PostOrder(node->right);
    std::cout << node->data << " ";
}

template <typename T>
int BinaryTree<T>::Size(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return 0;
    return 1 + Size(node->left) + Size(node->right);
} // post-order

template <typename T>
int BinaryTree<T>::Height(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return 0;
    int leftHeight = Height(node->left);
    int rightHeight = Height(node->right);
    return 1 + max(leftHeight, rightHeight);
} // post-order

template <typename T>
BinaryTreeNode<T> *BinaryTree<T>::Copy(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return nullptr;

    BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(node->data);
    newNode->left = Copy(node->left);
    newNode->right = Copy(node->right);
    return newNode;
} // pre-order

template <typename T>
void BinaryTree<T>::createBinTree(const T arr[], BinaryTreeNode<T> *&node, int &index)
{
    T ch = arr[index++];
    if (ch == '\0')
    {
        node = nullptr;
        return;
    }

    if (ch == '#')
    {
        node = nullptr;
        return;
    }

    node = new BinaryTreeNode<T>(ch);
    createBinTree(arr, node->left, index);
    createBinTree(arr, node->right, index);
} // pre-order

template <typename T>
void BinaryTree<T>::printBinTree(BinaryTreeNode<T> *node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data;

    if (node->left != nullptr || node->right != nullptr)
    {
        std::cout << "(";
        printBinTree(node->left);
        if (node->right != nullptr)
            std::cout << ",";
        printBinTree(node->right);
        std::cout << ")";
    }
}
