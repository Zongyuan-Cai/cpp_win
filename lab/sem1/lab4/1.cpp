#include <iostream>
#include <vector>
using namespace std;
double average(const vector<int> &vec)
{
    double sum = 0;
    for (int num : vec)
    {
        sum += num;
    }
    return sum / vec.size();
}
int main()
{
    vector<int> vec;
    while (true)
    {
        int n;
        cin >> n;
        if (n == 9999)
            break;
        vec.push_back(n);
    }
    cout << "Average: " << average(vec) << endl;
    return 0;
}