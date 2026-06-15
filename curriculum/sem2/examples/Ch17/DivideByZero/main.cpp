// Fig. 17.3-like: Handling an attempt to divide by zero.
// Demonstrates try, throw, catch with user-defined exception class.

#include <iostream>
#include <stdexcept>
using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;

// User-defined exception class inheriting from runtime_error
class DivideByZeroException : public runtime_error
{
public:
    DivideByZeroException()
        : runtime_error("attempted to divide by zero") {}
};

// Perform division and throw exception on divide by zero
double quotient(int numerator, int denominator)
{
    if (denominator == 0)
        throw DivideByZeroException();  // throw the exception object

    return static_cast<double>(numerator) / denominator;
}

int main()
{
    int number1, number2;
    double result;

    cout << "Enter two integers (end-of-file to end): ";

    while (cin >> number1 >> number2) {
        // try block contains code that might throw an exception
        try {
            result = quotient(number1, number2);
            cout << "The quotient is: " << result << endl;
        }
        // catch handler processes the exception
        catch (DivideByZeroException &divideByZeroException) {
            cout << "Exception occurred: "
                 << divideByZeroException.what() << endl;
        }

        cout << "\nEnter two integers (end-of-file to end): ";
    }

    cout << endl;
    return 0;
}
