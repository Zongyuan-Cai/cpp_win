#include <iostream>
#include <cassert>
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

    void destroy(BinaryTreeNode<T> *node);
    void creatBinTree(T arr[], BinaryTreeNode<T> *&node);
    void creatBinTree(T arr[], BinaryTreeNode<T> *&node, int &index);
    BinaryTreeNode<T> *Parent(BinaryTreeNode<T> *node, BinaryTreeNode<T> *current) const;
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
    void creatBinTree(T arr[]) { creatBinTree(arr, root); }
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
}

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
    BinaryTreeNode<T> *stack[stackSize];
    int top = -1;

    BinaryTreeNode<T> *p = nullptr;
    int flag = 0;
    int k = 0;

    node = nullptr;

    ch = arr[k++];
    while (ch != '#')
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
