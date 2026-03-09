#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> arr;
    while (arr.size() < 20)
    {
        int n;
        cin >> n;
        if (n < 10 || n > 100)
        {
            cout << "Input error!" << endl;
            continue;
        }
        if (find(arr.begin(), arr.end(), n) == arr.end())
        {
            arr.push_back(n);
        }
    }
    for (const auto &num : arr)
    {
        cout << num << " ";
    }
    return 0;
}