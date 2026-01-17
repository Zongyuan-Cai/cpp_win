#include <iostream>
#include <initializer_list>
using namespace std;
const int MAXSIZE = 100;
template <typename T>
struct LinkNode
{
    T data;
    int link;
};
template <typename T>
class StaticList
{
private:
    LinkNode<T> r[MAXSIZE];
    int avail;

public:
    StaticList();
    int length() const;
    int search(const T &value) const;
    int locate(int index) const;
    bool append(const T &value);
    bool insert(int index, const T &value);
    bool remove(int index, T &value);
    bool isEmpty() const;
    void output() const;
};

template <typename T>
StaticList<T>::StaticList()
{
    for (int i = 0; i < MAXSIZE - 1; ++i)
    {
        r[i].link = i + 1;
    }
    r[MAXSIZE - 1].link = -1;
    avail = 0;
    r[avail].link = -1; // 初始化为空表
}

template <typename T>
int StaticList<T>::length() const
{
    int len = 0;
    int index = r[MAXSIZE - 1].link;
    while (index != -1)
    {
        ++len;
        index = r[index].link;
    }
    return len;
}

template <typename T>
int StaticList<T>::search(const T &value) const
{
    int index = r[MAXSIZE - 1].link;
    while (index != -1)
    {
        if (r[index].data == value)
        {
            return index;
        }
        index = r[index].link;
    }
    return -1;
}

template <typename T>
int StaticList<T>::locate(int index) const
{
    if (index < 0)
    {
        return -1;
    }
    int current = r[MAXSIZE - 1].link;
    int count = 0;
    while (current != -1)
    {
        if (count == index)
        {
            return current;
        }
        current = r[current].link;
        ++count;
    }
    return -1;
}

template <typename T>
bool StaticList<T>::append(const T &value)
{
    if (avail == -1)
    {
        return false; // 空间已满
    }
    int newIndex = avail;
    avail = r[avail].link;
    r[newIndex].data = value;
    r[newIndex].link = -1;

    if (r[MAXSIZE - 1].link == -1)
    {
        r[MAXSIZE - 1].link = newIndex;
    }
    else
    {
        int tail = r[MAXSIZE - 1].link;
        while (r[tail].link != -1)
        {
            tail = r[tail].link;
        }
        r[tail].link = newIndex;
    }
    return true;
}

template <typename T>
bool StaticList<T>::insert(int index, const T &value)
{
    if (index < 0 || avail == -1)
    {
        return false;
    }
    int prevIndex = locate(index - 1);
    if (prevIndex == -1 && index != 0)
    {
        return false;
    }
    int newIndex = avail;
    avail = r[avail].link;
    r[newIndex].data = value;

    if (index == 0)
    {
        r[newIndex].link = r[MAXSIZE - 1].link;
        r[MAXSIZE - 1].link = newIndex;
    }
    else
    {
        r[newIndex].link = r[prevIndex].link;
        r[prevIndex].link = newIndex;
    }
    return true;
}

template <typename T>
bool StaticList<T>::remove(int index, T &value)
{
    if (index < 0)
    {
        return false;
    }
    int prevIndex = locate(index - 1);
    if (prevIndex == -1 || r[prevIndex].link == -1)
    {
        return false;
    }
    int toDelete = r[prevIndex].link;
    value = r[toDelete].data;
    r[prevIndex].link = r[toDelete].link;

    r[toDelete].link = avail;
    avail = toDelete;
    return true;
}

template <typename T>
bool StaticList<T>::isEmpty() const
{
    return r[MAXSIZE - 1].link == -1;
}

template <typename T>
void StaticList<T>::output() const
{
    if (isEmpty())
    {
        cout << "StaticList is empty!" << endl;
        return;
    }
    cout << "StaticList elements: ";
    int index = r[MAXSIZE - 1].link;
    while (index != -1)
    {
        cout << r[index].data << " ";
        index = r[index].link;
    }
    cout << endl;
}

int main()
{
    StaticList<int> sList;
    cout << "Appending elements 10, 20, 30 to StaticList." << endl;
    sList.append(10);
    sList.append(20);
    sList.append(30);
    sList.output();

    cout << "Inserting element 15 at index 1." << endl;
    sList.insert(1, 15);
    sList.output();

    int removedValue;
    cout << "Removing element at index 2." << endl;
    sList.remove(2, removedValue);
    cout << "Removed value: " << removedValue << endl;
    sList.output();

    cout << "Searching for value 20." << endl;
    int index = sList.search(20);
    if (index != -1)
    {
        cout << "Value 20 found at index: " << index << endl;
    }
    else
    {
        cout << "Value 20 not found." << endl;
    }

    cout << "Length of StaticList: " << sList.length() << endl;

    return 0;
}
