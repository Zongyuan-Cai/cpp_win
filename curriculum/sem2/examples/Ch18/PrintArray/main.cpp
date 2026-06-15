// Fig. 18.1: Function template printArray.
// Demonstrating function-template specializations for different types.

#include <iostream>
using std::cout;
using std::endl;

// Function template printArray
template <typename T>
void printArray(const T *array, int count)
{
    for (int i = 0; i < count; i++)
        cout << array[i] << " ";

    cout << endl;
}

int main()
{
    const int ACOUNT = 5;  // size of array a
    const int BCOUNT = 7;  // size of array b
    const int CCOUNT = 6;  // size of array c (5 + null)

    int a[ACOUNT] = {1, 2, 3, 4, 5};
    double b[BCOUNT] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    char c[CCOUNT] = "HELLO";  // 6th position for null

    cout << "Array a contains:" << endl;
    printArray(a, ACOUNT);  // Creates function-template specialization
                             // printArray where T is int

    cout << "Array b contains:" << endl;
    printArray(b, BCOUNT);  // Creates specialization where T is double

    cout << "Array c contains:" << endl;
    printArray(c, CCOUNT);  // Creates specialization where T is char

    return 0;
}
