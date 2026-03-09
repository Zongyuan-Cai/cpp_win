#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    cout << "sum=" << a + b + c << endl;
    cout << "average=" << (a + b + c) / 3.0 << endl;
    cout << "product=" << a * b * c << endl;
    cout << "smallest" << min({a, b, c}) << endl;
    cout << "largest" << max({a, b, c}) << endl;
    return 0;
}
