#include <iostream>
using namespace std;
void resverse_string(char *str)
{
    if (str == nullptr)
        return;
    char *start = str;
    char *end = str;
    while (*end != '\0')
    {
        end++;
    }
    end--;
    while (start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
int main()
{
    char str[50];
    cin.getline(str, 50);
    resverse_string(str);
    cout << str << endl;
    return 0;
}