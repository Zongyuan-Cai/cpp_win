#include <iostream>
#include <string>
using namespace std;
const int N = 5;
void digit(int n);
int main()
{
    int n;
    cin >> n;
    digit(n);
    // to_string
    string s = to_string(n);
    for (const char &c : s)
    {
        cout << c << " ";
    }
    return 0;
}
void digit(int n)
{
    int arr[10];
    int i = 0;
    while (n)
    {
        arr[i] = n % 10;
        i++;
        n /= 10;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << arr[j] << " ";
    }
}