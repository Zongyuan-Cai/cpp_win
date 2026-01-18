#include <iostream>
#include <cassert>
const int DEFAULT_SIZE = 100;
template <typename T>
class SeqQueue
{
protected:
    T *data;
    int front;
    int rear;
    int maxSize;

public:
    SeqQueue(int size = DEFAULT_SIZE);
    SeqQueue(const SeqQueue<T> &queue);
    ~SeqQueue();
    bool Enqueue(const T &item);
    bool Dequeue(T &item);
    bool getFront(T &item) const;
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    void Clear();
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const SeqQueue<U> &queue);
};

template <typename T>
SeqQueue<T>::SeqQueue(int size) : front(0), rear(0), maxSize(size)
{
    data = new T[maxSize];
    assert(data != nullptr);
}

template <typename T>
SeqQueue<T>::SeqQueue(const SeqQueue<T> &queue) : front(queue.front), rear(queue.rear), maxSize(queue.maxSize)
{
    data = new T[maxSize];
    assert(data != nullptr);
    for (int i = 0; i < maxSize; i++)
    {
        data[i] = queue.data[i];
    }
}

template <typename T>
SeqQueue<T>::~SeqQueue()
{
    delete[] data;
}

template <typename T>
bool SeqQueue<T>::Enqueue(const T &item)
{
    if (isFull())
    {
        return false;
    }
    data[rear] = (item);
    rear = (rear + 1) % maxSize;
    return true;
}

template <typename T>
bool SeqQueue<T>::Dequeue(T &item)
{
    if (isEmpty())
    {
        return false;
    }
    item = data[front];
    front = (front + 1) % maxSize;
    return true;
}

template <typename T>
bool SeqQueue<T>::getFront(T &item) const
{
    if (isEmpty())
    {
        return false;
    }
    item = data[front];
    return true;
}

template <typename T>
bool SeqQueue<T>::isEmpty() const
{
    return front == rear;
}

template <typename T>
bool SeqQueue<T>::isFull() const
{
    return (rear + 1) % maxSize == front;
}

template <typename T>
int SeqQueue<T>::getSize() const
{
    return (rear - front + maxSize) % maxSize;
}

template <typename T>
void SeqQueue<T>::Clear()
{
    front = rear = 0;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const SeqQueue<U> &queue)
{
    if (queue.isEmpty())
    {
        os << "empty ";
        return os;
    }
    else
    {
        int size = queue.getSize();
        for (int i = 0; i < size; i++)
        {
            os << queue.data[(queue.front + i) % queue.maxSize] << " ";
        }
        return os;
    }
}

#ifndef NO_SEQQUEUE_MAIN
int main()
{
    SeqQueue<int> queue;
    for (int i = 1; i <= 5; i++)
    {
        queue.Enqueue(i);
    }
    std::cout << "Queue after enqueuing 1 to 5: " << queue << std::endl;

    int item;
    queue.Dequeue(item);
    std::cout << "Dequeued item: " << item << std::endl;
    std::cout << "Queue after dequeue: " << queue << std::endl;

    queue.getFront(item);
    std::cout << "Front item: " << item << std::endl;

    std::cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Queue size: " << queue.getSize() << std::endl;

    queue.Clear();
    std::cout << "Queue after clearing: " << queue << std::endl;

    return 0;
}
#endif