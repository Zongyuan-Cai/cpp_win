#include <iostream>
#include <cassert>
const int DEFAULT_SIZE = 100;
template <typename T>
class PQueue
{
private:
    T *pqelems;
    int count;
    int maxSize;
    void adjust();

public:
    PQueue(int size = DEFAULT_SIZE);
    ~PQueue();
    bool Insert(const T &elem);
    bool RemoveMin(T &elem);
    bool getMin(T &elem) const;
    bool IsEmpty() const;
    bool IsFull() const;
    int getSize() const;
    void MakeEmpty();
};

template <typename T>
void PQueue<T>::adjust()
{
    int i = (count - 2) / 2;
    int j = 2 * i + 1;
    T temp = pqelems[i];
    while (j < count)
    {
        if (j + 1 < count && pqelems[j + 1] < pqelems[j])
            j++;
        if (temp <= pqelems[j])
            break;
        else
        {
            pqelems[i] = pqelems[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    pqelems[i] = temp;
}

template <typename T>
PQueue<T>::PQueue(int size) : maxSize(size), count(0)
{
    pqelems = new T[maxSize];
    assert(pqelems != nullptr);
}
