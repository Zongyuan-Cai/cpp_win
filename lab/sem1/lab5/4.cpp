#include <iostream>
#include <random>
using namespace std;
int flip()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    return dis(gen);
}
int main()
{
    int arr[2] = {0};
    for (int i = 0; i < 10000; i++)
    {
        arr[flip()]++;
    }
    cout << 1.0 * arr[0] / 10000 << endl;
    cout << 1.0 * arr[1] / 10000 << endl;
    return 0;
}