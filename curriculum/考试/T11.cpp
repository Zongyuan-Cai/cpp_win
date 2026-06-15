#include <iostream>
using namespace std;
void selectionSort(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(arr[i], arr[minIndex]);
        }
    }
}
int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int len = sizeof(arr) / sizeof(arr[0]);
    selectionSort(arr, len);
    cout << "Sorted array: ";
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}