#include <iostream>
#include <cassert>
const int maxStack = 100;
const int stackIncrement = 10;
template <typename T>
class SeqStack
{
private:
    T *data;
    int top;
    int maxSize;
    void overflowProcess();

public:
    SeqStack(int size = maxStack);
    SeqStack(const SeqStack<T> &stack);
    ~SeqStack();
    bool isEmpty() const;
    bool isFull() const;
    bool Push(const T &item);
    bool Pop(T &item);
    bool getTop(T &item) const;
    int getSize() const;
    void Clear();
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const SeqStack<U> &stack);
};

template <typename T>
void SeqStack<T>::overflowProcess()
{
    T *newData = new T[maxSize + stackIncrement];
    assert(newData != nullptr);
    for (int i = 0; i <= top; i++)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    maxSize += stackIncrement;
}

template <typename T>
SeqStack<T>::SeqStack(int size) : top(-1), maxSize(size)
{
    data = new T[maxSize];
    assert(data != nullptr);
}

template <typename T>
SeqStack<T>::SeqStack(const SeqStack<T> &stack) : top(stack.top), maxSize(stack.maxSize)
{
    data = new T[maxSize];
    assert(data != nullptr);
    for (int i = 0; i <= top; i++)
    {
        data[i] = stack.data[i];
    }
}

template <typename T>
SeqStack<T>::~SeqStack()
{
    delete[] data;
}

template <typename T>
bool SeqStack<T>::isEmpty() const
{
    return top == -1;
}

template <typename T>
bool SeqStack<T>::isFull() const
{
    return top == maxSize - 1;
}

template <typename T>
bool SeqStack<T>::Push(const T &item)
{
    if (isFull())
    {
        overflowProcess();
    }
    data[++top] = item;
    return true;
}

template <typename T>
bool SeqStack<T>::Pop(T &item)
{
    if (isEmpty())
    {
        return false;
    }
    item = data[top--];
    return true;
}

template <typename T>
bool SeqStack<T>::getTop(T &item) const
{
    if (isEmpty())
    {
        return false;
    }
    item = data[top];
    return true;
}

template <typename T>
int SeqStack<T>::getSize() const
{
    return top + 1;
}

template <typename T>
void SeqStack<T>::Clear()
{
    top = -1;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SeqStack<T> &stack)
{
    if (stack.isEmpty())
    {
        os << "Stack is empty.";
        return os;
    }
    for (int i = 0; i <= stack.top; i++)
    {
        os << stack.data[i] << " ";
    }
    return os;
}

int main()
{
    SeqStack<int> stack;
    for (int i = 1; i <= 15; i++)
    {
        stack.Push(i);
    }
    std::cout << "Stack after pushing 15 elements: " << stack << std::endl;

    int topElement;
    stack.getTop(topElement);
    std::cout << "Top element: " << topElement << std::endl;

    int poppedElement;
    stack.Pop(poppedElement);
    std::cout << "Popped element: " << poppedElement << std::endl;
    std::cout << "Stack after popping an element: " << stack << std::endl;

    std::cout << "Current stack size: " << stack.getSize() << std::endl;

    stack.Clear();
    std::cout << "Stack after clearing: " << stack << std::endl;

    return 0;
}