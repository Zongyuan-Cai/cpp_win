#include <iostream>
#include <string>
using namespace std;
int main()
{
    string str;
    int n;
    cin >> n;
    str = to_string(n);
    int len = str.length();
    for (const char &c : str)
    {
        cout << c << " ";
    }
    return 0;
}