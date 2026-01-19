#include <iostream>
#include <cstring>
using namespace std;

void getNext(const char P[], int next[])
{
    int m = strlen(P);
    next[0] = 0;
    int j = 0;
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && P[i] != P[j])
        {
            j = next[j - 1];
        }
        if (P[i] == P[j])
        {
            j++;
        }
        next[i] = j;
    }
}

int KMP(const char S[], const char P[])
{
    int n = strlen(S);
    int m = strlen(P);

    if (m == 0)
        return 0;

    int next[1000];
    getNext(P, next);

    int j = 0;

    for (int i = 0; i < n; i++)
    {
        while (j > 0 && S[i] != P[j])
        {
            j = next[j - 1];
        }
        if (S[i] == P[j])
        {
            j++;
        }
        if (j == m)
        {
            return i - m + 1;
        }
    }
    return -1;
}

int main()
{
    system("chcp 65001");
    char S[] = "abababc";
    char P[] = "ababc";

    int pos = KMP(S, P);

    if (pos != -1)
    {
        cout << "匹配成功，起始下标为：" << pos << endl;
    }
    else
    {
        cout << "匹配失败" << endl;
    }

    return 0;
}
