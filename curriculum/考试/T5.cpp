#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
int binary_search(int a[], int len, int n)
{
    int left = 0, right = len - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (a[mid] == n)
            return mid;
        else if (a[mid] < n)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
int random_number()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    return dis(gen);
}
int main()
{
    int arr[20];
    for (int i = 0; i < 10; ++i)
    {
        arr[i] = random_number();
    }
    sort(arr, arr + 10);
    for (int i = 0; i < 10; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    int n;
    cin >> n;
    int result = binary_search(arr, 10, n);
    if (result != -1)
    {
        cout << result << endl;
    }
    else
    {
        cout << "No found" << endl;
    }
    return 0;
}
