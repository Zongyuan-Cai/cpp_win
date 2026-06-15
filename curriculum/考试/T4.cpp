#include <iostream>
#include <random>
using namespace std;
int random_number()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    return dis(gen);
}
void bubble_sort(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
int main()
{
    int arr[20];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = random_number();
    }
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    bubble_sort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}