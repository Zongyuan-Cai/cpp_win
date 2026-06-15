#include <iostream>
#include <cstring>
using namespace std;
void to_uppercase(char str[])
{
    char *p = str;
    while (*p)
    {
        if (*p >= 'a' && *p <= 'z')
        {
            *p = *p - ('a' - 'A');
        }
        p++;
    }
}
void to_lowercase(char str[])
{
    char *p = str;
    while (*p)
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p = *p + ('a' - 'A');
        }
        p++;
    }
}
int main()
{
    char str1[] = "Hello, World!";
    char str2[] = "Hello, World!";
    to_uppercase(str1);
    to_lowercase(str2);
    cout << "Uppercase: " << str1 << endl;
    cout << "Lowercase: " << str2 << endl;
    return 0;
}