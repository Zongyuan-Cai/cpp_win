#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int to_int(string s)
{
    int res = 0;
    int len = s.length();
    bool start = false;
    for (int i = 0; i < len; i++)
    {
        if (!start && s[i] == '0')
        {
            continue;
        }
        else
        {
            start = true;
            res = res + pow(2, len - i - 1) * (s[i] - '0');
        }
    }
    return res;
}
int main()
{
    string s;
    cin >> s;
    cout << to_int(s) << endl;
    return 0;
}