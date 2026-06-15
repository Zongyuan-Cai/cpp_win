// Stack.h — Stack class template.
// Fig. 18.2: Class template Stack with type parameter T.
#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack
{
public:
    Stack(int = 10);  // default constructor (Stack size 10)

    ~Stack()
    {
        delete[] stackPtr;  // deallocate internal space for Stack
    }

    bool push(const T &);  // push an element onto the Stack
    bool pop(T &);          // pop an element off the Stack

    bool isEmpty() const
    {
        return top == -1;
    }

    bool isFull() const
    {
        return top == size - 1;
    }

private:
    int size;
    int top;
    T *stackPtr;  // pointer to a T array
};

// Constructor template
template <typename T>
Stack<T>::Stack(int s)
    : size(s > 0 ? s : 10),  // validate size
      top(-1),                // Stack initially empty
      stackPtr(new T[size])   // allocate memory dynamically for elements
{
    // empty body
}

// Push element onto Stack
template <typename T>
bool Stack<T>::push(const T &pushValue)
{
    if (!isFull()) {
        stackPtr[++top] = pushValue;  // first +1, then set item
        return true;
    }

    return false;
}

// Pop element off Stack
template <typename T>
bool Stack<T>::pop(T &popValue)
{
    if (!isEmpty()) {
        popValue = stackPtr[top--];  // first get item, then -1
        return true;
    }

    return false;  // if Stack is empty, cannot pop
}

#endif
