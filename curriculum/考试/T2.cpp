#include <iostream>
#include <algorithm>
using namespace std;
void reverse(int arr[], int len)
{
    int left = 0;
    int right = len - 1;
    while (left < right)
    {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}
int main()
{
    int arr[20];
    int len;
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    reverse(arr, len);
    cout << endl;
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
