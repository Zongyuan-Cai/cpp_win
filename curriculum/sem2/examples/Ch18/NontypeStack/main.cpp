// Fig. 18.5: Nontype parameter Stack class template.
// Demonstrating class template with nontype template parameter.

#include <iostream>
using std::cout;
using std::endl;

// Class template with nontype parameter "elements"
template <typename T, int elements>
class Stack
{
public:
    Stack() : top(-1)
    {
        // Initialize all elements to 0
        for (int i = 0; i < elements; i++)
            stackPtr[i] = 0;
    }

    bool push(const T &pushValue)
    {
        if (!isFull()) {
            stackPtr[++top] = pushValue;
            return true;
        }
        return false;
    }

    bool pop(T &popValue)
    {
        if (!isEmpty()) {
            popValue = stackPtr[top--];
            return true;
        }
        return false;
    }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == elements - 1; }

private:
    int top;
    T stackPtr[elements];  // fixed-size array, no need for "size" member
};

int main()
{
    // Stack of 100 ints
    Stack<int, 100> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    int value;
    while (intStack.pop(value))
        cout << value << ' ';
    cout << endl;

    // Stack of 200 doubles
    Stack<double, 200> doubleStack;
    doubleStack.push(1.1);
    doubleStack.push(2.2);
    doubleStack.push(3.3);

    double dValue;
    while (doubleStack.pop(dValue))
        cout << dValue << ' ';
    cout << endl;

    // Using default value: elements = 5
    // (This variant is shown in the textbook notes)
    cout << "\nNontype parameters must be compile-time constants." << endl;
    cout << "e.g., Stack<int, 100> is valid; int n = 100; Stack<int, n> is not." << endl;

    return 0;
}
