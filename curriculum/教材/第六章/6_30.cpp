#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void reserve(int num);
int main()
{
    int num;
    cin >> num;
    reserve(num);
    return 0;
}
void reserve(int num)
{
    string str = to_string(num);
    string rev_st1 = string(str.rbegin(), str.rend());
    cout << rev_st1 << endl;
    reverse(str.begin(), str.end());
    cout << str << endl;
}