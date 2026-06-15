#include <iostream>
using namespace std;
void show_square(int n);
int main()
{
    int n;
    cin >> n;
    show_square(n);
    return 0;
}
void show_square(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        if (i == 1 || i == n)
        {
            for (int j = 1; j <= n; ++j)
            {
                cout << "*";
            }
            cout << endl;
        }
        else
        {
            cout << "*";
            for (int j = 1; j <= n - 2; ++j)
            {
                cout << " ";
            }
            cout << "*" << endl;
        }
    }
}