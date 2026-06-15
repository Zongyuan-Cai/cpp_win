// Fig. 17.3: Demonstrating exception rethrowing.
// Rethrow an exception from a catch handler for further processing.

#include <iostream>
#include <exception>
using std::cout;
using std::endl;
using std::exception;

// throw, catch and rethrow exception
void throwException()
{
    // throw exception and catch it immediately
    try {
        cout << "  Function throwException throws an exception\n";
        throw exception();  // generate exception
    }
    catch (exception &) {  // handle exception
        cout << "  Exception handled in function throwException\n";
        cout << "  Function throwException rethrows exception";
        throw;  // rethrow exception for further processing
    }

    cout << "This also should not print\n";  // skipped
}

int main()
{
    // throw exception
    try {
        cout << "main invokes function throwException\n";
        throwException();
        cout << "This should not print\n";  // skipped
    }
    catch (exception &) {  // handle rethrown exception
        cout << "\n\nException handled in main\n";
    }

    cout << "Program control continues after catch in main\n";
    return 0;
}
