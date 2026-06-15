#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int num(char str[]);
int main()
{
    char str[100];
    cin.getline(str, 100);
    cout << num(str) << endl;
    return 0;
}
int num(char str[])
{
    int count = 0;
    int sum = 0;
    int len = strlen(str);
    for (int i = len - 1; i >= 0; --i)
    {
        int num = static_cast<int>(str[i] - '0');
        sum += (num * pow(2, count));
        count++;
    }
    return sum;
}