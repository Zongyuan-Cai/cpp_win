const int TableLength = 256;
const int StackSize = 1024;
#include<iostream>
#include<cassert>

template <typename T>
struct GenlistNode
{
    int utype;// 0: int, 1: T, 2: sublist
    GenlistNode *next;
    union
    {
        int ref;
        T value;
        GenlistNode *sublist;
    };
    GenlistNode() : utype(0), next(nullptr), ref(0) {}
    GenlistNode(const GenlistNode &other)
        : utype(other.utype), next(other.next)
    {
        switch (utype)
        {
        case 0:
            ref = other.ref;
            break;
        case 1:
            new (&value) T(other.value);
            break;
        case 2:
            sublist = other.sublist;
            break;
        }
    }
};

template <typename T>
class Genlist{
private:
    GenlistNode<T> *head;
};