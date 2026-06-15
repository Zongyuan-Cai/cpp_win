#include <iostream>
using namespace std;
void swapElement(int *arr, int i, int j)
{
    int *p1 = arr + i;
    int *p2 = arr + j;
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    swapElement(arr, 1, 3);
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}