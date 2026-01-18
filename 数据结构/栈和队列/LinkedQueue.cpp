#include <iostream>
#include <cassert>
template <typename T>
struct LinkedNode
{
    T data;
    LinkedNode *next;
    LinkedNode(const T &item, LinkedNode *ptr = nullptr) : data(item), next(ptr) {}
};
template <typename T>
class LinkedQueue
{
private:
    LinkedNode<T> *front;
    LinkedNode<T> *rear;

public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<T> &queue);
    ~LinkedQueue();
    bool isEmpty() const;
    bool EnQueue(const T &item);
    bool DeQueue(T &item);
    bool getFront(T &item) const;
    void Clear();
    int getSize() const;
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const LinkedQueue<U> &queue);
};

template <typename T>
LinkedQueue<T>::LinkedQueue() : front(nullptr), rear(nullptr) {}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &queue) : front(nullptr), rear(nullptr)
{
    if (queue.front == nullptr)
    {
        return;
    }
    LinkedNode<T> *p = queue.front;
    LinkedNode<T> *q = new LinkedNode<T>(p->data);
    front = q;
    rear = q;
    p = p->next;
    while (p != nullptr)
    {
        q->next = new LinkedNode<T>(p->data);
        q = q->next;
        rear = q;
        p = p->next;
    }
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    Clear();
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return front == nullptr;
}

template <typename T>
bool LinkedQueue<T>::EnQueue(const T &item)
{
    LinkedNode<T> *newNode = new LinkedNode<T>(item);
    if (newNode == nullptr)
    {
        return false;
    }
    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    return true;
}

template <typename T>
bool LinkedQueue<T>::DeQueue(T &item)
{
    if (isEmpty())
    {
        return false;
    }
    LinkedNode<T> *p = front;
    item = front->data;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete p;
    return true;
}

template <typename T>
bool LinkedQueue<T>::getFront(T &item) const
{
    if (isEmpty())
    {
        return false;
    }
    item = front->data;
    return true;
}

template <typename T>
void LinkedQueue<T>::Clear()
{
    LinkedNode<T> *p;
    while (front != nullptr)
    {
        p = front;
        front = front->next;
        delete p;
    }
    rear = nullptr;
}

template <typename T>
int LinkedQueue<T>::getSize() const
{
    int count = 0;
    LinkedNode<T> *p = front;
    while (p != nullptr)
    {
        count++;
        p = p->next;
    }
    return count;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const LinkedQueue<U> &queue)
{
    if (queue.isEmpty())
    {
        os << "Queue is empty.";
        return os;
    }
    LinkedNode<U> *p = queue.front;
    os << "Front -> ";
    while (p != nullptr)
    {
        os << p->data << " -> ";
        p = p->next;
    }
    os << "Rear";
    return os;
}

int main()
{
    LinkedQueue<int> queue;
    queue.EnQueue(10);
    queue.EnQueue(20);
    queue.EnQueue(30);
    std::cout << queue << std::endl;

    int frontItem;
    queue.getFront(frontItem);
    std::cout << "Front item: " << frontItem << std::endl;

    int dequeuedItem;
    queue.DeQueue(dequeuedItem);
    std::cout << "Dequeued item: " << dequeuedItem << std::endl;
    std::cout << queue << std::endl;

    std::cout << "Queue size: " << queue.getSize() << std::endl;

    queue.Clear();
    std::cout << "After clearing: " << queue << std::endl;

    return 0;
}