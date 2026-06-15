// Fig. 18.3: Stack class template test program.
// Testing class template Stack with double and int types.

#include <iostream>
#include "Stack.h"
using std::cout;
using std::endl;

int main()
{
    Stack<double> doubleStack(5);  // double type Stack with size 5
    double doubleValue = 1.1;

    cout << "Pushing elements onto doubleStack\n";

    // Push until Stack is full
    while (doubleStack.push(doubleValue)) {
        cout << doubleValue << ' ';
        doubleValue += 1.1;
    }

    cout << "\nStack is full. Cannot push " << doubleValue
         << "\n\nPopping elements from doubleStack\n";

    // Pop until Stack is empty
    while (doubleStack.pop(doubleValue))
        cout << doubleValue << ' ';

    cout << "\nStack is empty. Cannot pop\n";

    Stack<int> intStack;  // default size 10
    int intValue = 1;

    cout << "\nPushing elements onto intStack\n";

    // Push 10 integers onto intStack
    while (intStack.push(intValue)) {
        cout << intValue << ' ';
        intValue++;
    }

    cout << "\nStack is full. Cannot push " << intValue
         << "\n\nPopping elements from intStack\n";

    // Pop elements from intStack
    while (intStack.pop(intValue))
        cout << intValue << ' ';

    cout << "\nStack is empty. Cannot pop" << endl;

    return 0;
}
