#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int arr[10];
    int i = 0;
    while (i < 10)
    {
        cin >> arr[i];
        i++;
    }
    cout << *max_element(arr, arr + 10) << endl;
    return 0;
}