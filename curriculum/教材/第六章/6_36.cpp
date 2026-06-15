#include <iostream>
using namespace std;
int pow(int m, int n);
int main()
{
    int m, n;
    cin >> m >> n;
    cout << pow(m, n) << endl;
    return 0;
}
int pow(int m, int n)
{
    if (n == 0)
        return 1;
    else
        return m * pow(m, n - 1);
}