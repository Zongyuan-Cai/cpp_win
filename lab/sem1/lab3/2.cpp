#include <iostream>
#include <string>
using namespace std;
bool isPalindrome(int num)
{
    string str = to_string(num);
    int left = 0;
    int right = str.length() - 1;
    while (left < right)
    {
        if (str[left] != str[right])
            return false;
        left++;
        right--;
    }
    return true;
}
int main()
{
    int n;
    cin >> n;
    if (isPalindrome(n))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
