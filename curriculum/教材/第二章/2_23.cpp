#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5;
int main()
{
    int arr[N];
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < N; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
    // c++17
    vector<int> vec;
    for (int i = 0; i < N; ++i)
    {
        int n;
        cin >> n;
        vec.push_back(n);
    }
    auto [m_min, m_max] = minmax_element(vec.begin(), vec.end());
    cout << "Max: " << *m_max << endl;
    cout << "Min: " << *m_min << endl;
    return 0;
}