#include <iostream>
#include <vector>
using namespace std;
vector<int> countchars(const char *str)
{
    vector<int> counts(5, 0);
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
        {
            counts[0]++;
        }
        if (*str >= 'A' && *str <= 'Z')
        {
            counts[1]++;
        }
        if (*str >= '0' && *str <= '9')
        {
            counts[2]++;
        }
        if (*str == ' ')
        {
            counts[3]++;
        }
        else
        {
            counts[4]++;
        }
        str++;
    }
    return counts;
}
int main()
{
    const char *str = "Hello World! 123";
    vector<int> result = countchars(str);
    cout << "Lowercase letters: " << result[0] << endl;
    cout << "Uppercase letters: " << result[1] << endl;
    cout << "Digits: " << result[2] << endl;
    cout << "Spaces: " << result[3] << endl;
    cout << "Other characters: " << result[4] << endl;
    return 0;
}