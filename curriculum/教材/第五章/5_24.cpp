#include <iostream>
using namespace std;
void draw(int n);
int main()
{
    int n;
    cin >> n;
    draw(n);
    return 0;
}
void draw(int n)
{
    for (int i = 1; i < n / 2 + 1; i++)
    {
        for (int j = 1; j <= n / 2 - i; j++)
        {
            cout << " ";
        }
        for (int k = 1; k <= 2 * i - 1; k++)
        {
            cout << "*";
        }
        cout << endl;
    }
    for (int i = n / 2; i >= 1; i--)
    {
        for (int j = 1; j <= n / 2 - i; j++)
        {
            cout << " ";
        }
        for (int k = 1; k <= 2 * i - 1; k++)
        {
            cout << "*";
        }
        cout << endl;
    }
}