#define NO_SEQQUEUE_MAIN
#include <iostream>
#include "SeqQueue.cpp"
template <typename T>
class SeqDeque : public SeqQueue<T>
{
public:
    SeqDeque(int size = DEFAULT_SIZE) : SeqQueue<T>(size) {}
    ~SeqDeque() = default;
    bool isEmpty() const;
    bool isFull() const;
    bool getHead(T &item) const;
    bool getTail(T &item) const;
    bool EnQueueHead(const T &item);
    bool EnQueueTail(const T &item);
    bool DeQueueHead(T &item);
    bool DeQueueTail(T &item);
};

template <typename T>
bool SeqDeque<T>::isEmpty() const
{
    return SeqQueue<T>::isEmpty();
}

template <typename T>
bool SeqDeque<T>::isFull() const
{
    return SeqQueue<T>::isFull();
}

template <typename T>
bool SeqDeque<T>::getHead(T &item) const
{
    return SeqQueue<T>::getFront(item);
}

template <typename T>
bool SeqDeque<T>::getTail(T &item) const
{
    if (this->isEmpty())
    {
        return false;
    }
    int tailIndex = (this->rear - 1 + this->maxSize) % this->maxSize;
    item = this->data[tailIndex];
    return true;
}

template <typename T>
bool SeqDeque<T>::EnQueueHead(const T &item)
{
    if (this->isFull())
    {
        return false;
    }
    this->front = (this->front - 1 + this->maxSize) % this->maxSize;
    this->data[this->front] = item;
    return true;
}

template <typename T>
bool SeqDeque<T>::EnQueueTail(const T &item)
{
    return this->Enqueue(item);
}

template <typename T>
bool SeqDeque<T>::DeQueueHead(T &item)
{
    return this->Dequeue(item);
}

template <typename T>
bool SeqDeque<T>::DeQueueTail(T &item)
{
    if (this->isEmpty())
    {
        return false;
    }
    this->rear = (this->rear - 1 + this->maxSize) % this->maxSize;
    item = this->data[this->rear];
    return true;
}

int main()
{
    SeqDeque<int> deque;
    for (int i = 1; i <= 5; i++)
    {
        deque.EnQueueTail(i);
    }
    std::cout << "Deque after enqueuing 1 to 5 at tail: " << deque << std::endl;

    int item;
    deque.DeQueueHead(item);
    std::cout << "Dequeued item from head: " << item << std::endl;
    std::cout << "Deque after dequeue from head: " << deque << std::endl;

    deque.EnQueueHead(0);
    std::cout << "Deque after enqueuing 0 at head: " << deque << std::endl;

    deque.DeQueueTail(item);
    std::cout << "Dequeued item from tail: " << item << std::endl;
    std::cout << "Deque after dequeue from tail: " << deque << std::endl;

    deque.getHead(item);
    std::cout << "Head item: " << item << std::endl;

    deque.getTail(item);
    std::cout << "Tail item: " << item << std::endl;

    std::cout << "Is deque empty? " << (deque.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Deque size: " << deque.getSize() << std::endl;

    deque.Clear();
    std::cout << "Deque after clearing: " << deque << std::endl;

    return 0;
}