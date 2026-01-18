#include <iostream>
#include <cassert>
template <typename T>
class DualStack
{
private:
    T *data;
    int top1;
    int top2;
    int maxSize;
    void overflowProcess();

public:
    DualStack(int size = 100);
    DualStack(const DualStack<T> &stack);
    ~DualStack();
    bool isEmpty1() const;
    bool isEmpty2() const;
    bool isFull() const;
    bool Push1(const T &item);
    bool Push2(const T &item);
    bool Pop1(T &item);
    bool Pop2(T &item);
    bool getTop1(T &item) const;
    bool getTop2(T &item) const;
    int getSize1() const;
    int getSize2() const;
    void Clear1();
    void Clear2();
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const DualStack<U> &stack);
};

template <typename T>
void DualStack<T>::overflowProcess()
{
    T *newData = new T[maxSize * 2];
    assert(newData != nullptr);
    for (int i = 0; i <= top1; i++)
    {
        newData[i] = data[i];
    }
    for (int i = maxSize - 1, j = maxSize * 2 - 1; i >= top2; i--, j--)
    {
        newData[j] = data[i];
    }
    delete[] data;
    data = newData;
    top2 += maxSize;
    maxSize *= 2;
}

template <typename T>
DualStack<T>::DualStack(int size) : top1(-1), top2(size), maxSize(size)
{
    data = new T[maxSize];
    assert(data != nullptr);
}

template <typename T>
DualStack<T>::DualStack(const DualStack<T> &stack) : top1(stack.top1), top2(stack.top2), maxSize(stack.maxSize)
{
    data = new T[maxSize];
    assert(data != nullptr);
    for (int i = 0; i <= top1; i++)
    {
        data[i] = stack.data[i];
    }
    for (int i = top2; i < maxSize; i++)
    {
        data[i] = stack.data[i];
    }
}

template <typename T>
DualStack<T>::~DualStack()
{
    delete[] data;
}

template <typename T>
bool DualStack<T>::isEmpty1() const
{
    return top1 == -1;
}

template <typename T>
bool DualStack<T>::isEmpty2() const
{
    return top2 == maxSize;
}

template <typename T>
bool DualStack<T>::isFull() const
{
    return top1 + 1 == top2;
}

template <typename T>
bool DualStack<T>::Push1(const T &item)
{
    if (isFull())
    {
        overflowProcess();
    }
    data[++top1] = item;
    return true;
}

template <typename T>
bool DualStack<T>::Push2(const T &item)
{
    if (isFull())
    {
        overflowProcess();
    }
    data[--top2] = item;
    return true;
}

template <typename T>
bool DualStack<T>::Pop1(T &item)
{
    if (isEmpty1())
    {
        return false;
    }
    item = data[top1--];
    return true;
}

template <typename T>
bool DualStack<T>::Pop2(T &item)
{
    if (isEmpty2())
    {
        return false;
    }
    item = data[top2++];
    return true;
}

template <typename T>
bool DualStack<T>::getTop1(T &item) const
{
    if (isEmpty1())
    {
        return false;
    }
    item = data[top1];
    return true;
}

template <typename T>
bool DualStack<T>::getTop2(T &item) const
{
    if (isEmpty2())
    {
        return false;
    }
    item = data[top2];
    return true;
}

template <typename T>
int DualStack<T>::getSize1() const
{
    return top1 + 1;
}

template <typename T>
int DualStack<T>::getSize2() const
{
    return maxSize - top2;
}

template <typename T>
void DualStack<T>::Clear1()
{
    top1 = -1;
}

template <typename T>
void DualStack<T>::Clear2()
{
    top2 = maxSize;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DualStack<T> &stack)
{
    os << "Stack 1: ";
    if (stack.isEmpty1())
    {
        os << "empty ";
    }
    else
    {
        for (int i = 0; i <= stack.top1; i++)
        {
            os << stack.data[i] << " ";
        }
    }
    os << "\nStack 2: ";
    if (stack.isEmpty2())
    {
        os << "empty ";
    }
    else
    {
        for (int i = stack.maxSize - 1; i >= stack.top2; i--)
        {
            os << stack.data[i] << " ";
        }
    }
    return os;
}

int main()
{
    DualStack<int> stack(5);
    stack.Push1(1);
    stack.Push1(2);
    stack.Push2(10);
    stack.Push2(20);
    std::cout << stack << std::endl;

    int item;
    stack.Pop1(item);
    std::cout << "Popped from Stack 1: " << item << std::endl;
    stack.Pop2(item);
    std::cout << "Popped from Stack 2: " << item << std::endl;

    std::cout << stack << std::endl;
    return 0;
}