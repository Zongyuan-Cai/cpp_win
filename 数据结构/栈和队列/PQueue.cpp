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
    T temp = pqelems[count - 1];
    for (int j = count - 2; j >= 0; j--)
    {
        if (pqelems[j] <= temp)
        {
            break;
        }
        else
        {
            pqelems[j + 1] = pqelems[j];
        }
    }
    pqelems[0] = temp;
}

template <typename T>
PQueue<T>::PQueue(int size) : count(0), maxSize(size)
{
    pqelems = new T[maxSize];
    assert(pqelems != nullptr);
}

template <typename T>
PQueue<T>::~PQueue()
{
    delete[] pqelems;
}

template <typename T>
bool PQueue<T>::Insert(const T &elem)
{
    if (IsFull())
    {
        return false;
    }
    pqelems[count] = elem;
    count++;
    adjust();
    return true;
}

template <typename T>
bool PQueue<T>::RemoveMin(T &elem)
{
    if (IsEmpty())
    {
        return false;
    }
    elem = pqelems[count - 1];
    count--;
    return true;
}

template <typename T>
bool PQueue<T>::getMin(T &elem) const
{
    if (IsEmpty())
    {
        return false;
    }
    elem = pqelems[count - 1];
    return true;
}

template <typename T>
bool PQueue<T>::IsEmpty() const
{
    return count == 0;
}

template <typename T>
bool PQueue<T>::IsFull() const
{
    return count == maxSize;
}

template <typename T>
int PQueue<T>::getSize() const
{
    return count;
}

template <typename T>
void PQueue<T>::MakeEmpty()
{
    count = 0;
}

int main()
{
    PQueue<int> pq(10);
    pq.Insert(5);
    pq.Insert(3);
    pq.Insert(8);
    int minElem;
    pq.getMin(minElem);
    std::cout << "Minimum element: " << minElem << std::endl; // Output: 3
    pq.RemoveMin(minElem);
    std::cout << "Removed minimum element: " << minElem << std::endl; // Output: 3
    pq.getMin(minElem);
    std::cout << "New minimum element: " << minElem << std::endl; // Output: 5
    return 0;
}