#include <iostream>
#include <string>
using namespace std;
bool is(int n);
int main()
{
    int n;
    cin >> n;
    if (is(n))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
bool is(int n)
{
    string str = to_string(n);
    int len = str.length();
    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - 1 - i])
        {
            return false;
        }
    }
    return true;
}