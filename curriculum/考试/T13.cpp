#include <iostream>
using namespace std;
const int ROWS = 4;
const int COLS = 3;
void transpose(int src[ROWS][COLS], int dest[COLS][ROWS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            dest[j][i] = src[i][j];
        }
    }
}
int main()
{
    int source[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}};
    int destination[COLS][ROWS] = {0};
    transpose(source, destination);
    cout << "Transposed Matrix:" << endl;
    for (int i = 0; i < COLS; ++i)
    {
        for (int j = 0; j < ROWS; ++j)
        {
            cout << destination[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}