#include <iostream>
#include <cassert>
template <typename T>
struct Linknode
{
    T data;
    Linknode *next;
    Linknode(const T &item, Linknode *ptr = nullptr) : data(item), next(ptr) {}
};
template <typename T>
class LinkedStack
{
private:
    Linknode<T> *top;

public:
    LinkedStack();
    LinkedStack(const LinkedStack<T> &stack);
    ~LinkedStack();
    bool Push(const T &item);
    bool Pop(T &item);
    bool getTop(T &item) const;
    bool isEmpty() const;
    int getSize() const;
    void Clear();
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const LinkedStack<U> &stack);
};

template <typename T>
LinkedStack<T>::LinkedStack() : top(nullptr) {}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T> &stack) : top(nullptr)
{
    if (stack.top == nullptr)
    {
        return;
    }
    Linknode<T> *p = stack.top;
    Linknode<T> *q = new Linknode<T>(p->data);
    top = q;
    p = p->next;
    while (p != nullptr)
    {
        q->next = new Linknode<T>(p->data);
        q = q->next;
        p = p->next;
    }
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    Clear();
}

template <typename T>
bool LinkedStack<T>::Push(const T &item)
{
    Linknode<T> *newNode = new Linknode<T>(item, top);
    if (newNode == nullptr)
    {
        return false;
    }
    top = newNode;
    return true;
}

template <typename T>
bool LinkedStack<T>::Pop(T &item)
{
    if (isEmpty())
    {
        return false;
    }
    Linknode<T> *p = top;
    item = top->data;
    top = top->next;
    delete p;
    return true;
}

template <typename T>
bool LinkedStack<T>::getTop(T &item) const
{
    if (isEmpty())
    {
        return false;
    }
    item = top->data;
    return true;
}

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
    return top == nullptr;
}

template <typename T>
int LinkedStack<T>::getSize() const
{
    int count = 0;
    Linknode<T> *p = top;
    while (p != nullptr)
    {
        count++;
        p = p->next;
    }
    return count;
}

template <typename T>
void LinkedStack<T>::Clear()
{
    Linknode<T> *p;
    while (top != nullptr)
    {
        p = top;
        top = top->next;
        delete p;
    }
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const LinkedStack<U> &stack)
{
    if (stack.isEmpty())
    {
        os << "Stack is empty";
        return os;
    }
    Linknode<U> *p = stack.top;
    os << "Top -> ";
    while (p != nullptr)
    {
        os << p->data << " -> ";
        p = p->next;
    }
    os << "nullptr";
    return os;
}

int main()
{
    LinkedStack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    std::cout << stack << std::endl;

    int topItem;
    stack.getTop(topItem);
    std::cout << "Top item: " << topItem << std::endl;

    int poppedItem;
    stack.Pop(poppedItem);
    std::cout << "Popped item: " << poppedItem << std::endl;
    std::cout << stack << std::endl;

    std::cout << "Stack size: " << stack.getSize() << std::endl;

    stack.Clear();
    std::cout << "After clearing: " << stack << std::endl;

    return 0;
}