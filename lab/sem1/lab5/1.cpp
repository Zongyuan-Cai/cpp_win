#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
bool perfect(int n)
{
    vector<int> factors;
    for (int i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            factors.push_back(i);
            if (i != 1 && i != n / i)
                factors.push_back(n / i);
        }
    }
    int sum = 0;
    for (auto factor : factors)
        sum += factor;
    return sum == n;
}
int main()
{
    int n;
    cin >> n;
    if (perfect(n))
        cout << n << " is a perfect number." << endl;
    else
        cout << n << " is not a perfect number." << endl;
    return 0;
}