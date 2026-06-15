#include <iostream>
using namespace std;
int gcd(int a, int b);
int main()
{
    int a, b;
    cin >> a >> b;
    cout << "GCD: " << gcd(a, b) << endl;
    return 0;
}
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
// int g=std::gcd(48,18);
// int l=std::lcm(48,18);