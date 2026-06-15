#include <iostream>
#include <random>
using namespace std;
int get_random_num();
int main()
{
    const int N = 1000;
    int arr[N];
    for (int i = 0; i < N; ++i)
    {
        arr[i] = get_random_num();
    }
    for (int i = 0; i < N; ++i)
    {
        cout << arr[i] << " ";
        if ((i + 1) % 20 == 0)
            cout << endl;
    }
    return 0;
}
int get_random_num()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dist(-10, 10);
    return dist(gen);
}