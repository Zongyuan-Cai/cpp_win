// Fig. 17.4: Demonstrating stack unwinding.
// Exception thrown and propagated through the call stack.

#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;
using std::runtime_error;

// function3 throws a runtime_error — exception NOT caught here
void function3()
{
    cout << "In function 3" << endl;

    // throw is not enclosed in a try block here
    throw runtime_error("runtime_error in function3");
}

// function2 calls function3 — exception NOT caught here either
void function2()
{
    cout << "function3 is called inside function2" << endl;
    function3();  // exception propagates through function2
}

// function1 calls function2 — exception NOT caught here either
void function1()
{
    cout << "function2 is called inside function1" << endl;
    function2();  // exception propagates through function1
}

int main()
{
    try {
        cout << "function1 is called inside main" << endl;
        function1();  // exception thrown, stack unwinds
    }
    catch (runtime_error &error) {  // catch handler: matched!
        cout << "Exception occurred: " << error.what() << endl;
        cout << "Exception handled in main" << endl;
    }

    // Execution resumes here after catch
    return 0;
}
