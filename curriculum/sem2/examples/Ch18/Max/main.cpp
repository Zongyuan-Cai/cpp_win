// Function template max demonstration.
// Compiler infers type T from function call arguments.

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// Function template maxValue — returns the larger of two values
// (Note: renamed to avoid conflict with std::max)
template <typename T>
T maxValue(T v1, T v2)
{
    return (v1 > v2) ? v1 : v2;
}

int main()
{
    // T is int
    cout << "maxValue(1, 0) = " << maxValue(1, 0) << endl;

    // T is double
    cout << "maxValue(1.0, 0.0) = " << maxValue(1.0, 0.0) << endl;
    cout << "maxValue(3.14, 2.72) = " << maxValue(3.14, 2.72) << endl;

    // T is string
    string s1 = "hi", s2 = "world";
    cout << "maxValue(\"hi\", \"world\") = " << maxValue(s1, s2) << endl;

    // T is char
    cout << "maxValue('A', 'B') = " << maxValue('A', 'B') << endl;

    return 0;
}
