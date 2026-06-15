#include <iostream>
using namespace std;

void solve(int n, char from, char aux, char to)
{
    if (n == 0)
        return;
    solve(n - 1, from, to, aux);
    cout << from << " -> " << to << '\n';
    solve(n - 1, aux, from, to);
}

void hanoi(int n)
{
    solve(n, 'A', 'B', 'C');
}
int main()
{
    int n;
    cin >> n;
    hanoi(n);
    return 0;
}
