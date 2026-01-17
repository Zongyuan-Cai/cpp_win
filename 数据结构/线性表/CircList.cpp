#include <iostream>
#include <initializer_list>
#include <cstddef>
using namespace std;
template <typename T>
struct LinkNode
{
    T data;
    LinkNode *next;
    LinkNode(const T &d = T(), LinkNode *n = nullptr) : data(d), next(n) {}
};
template <typename T>
class CircList
{
private:
    LinkNode<T> *head;
    LinkNode<T> *tail;

public:
    CircList();
    CircList(const T &value);
    CircList(const initializer_list<T> &list);
    CircList(const CircList<T> &other);
    ~CircList();
    int Length() const;
    bool isEmpty() const;
    LinkNode<T> *getHead() const;
    LinkNode<T> *getTail() const;
    void setHead(LinkNode<T> *node);
    void setTail(LinkNode<T> *node);
    LinkNode<T> *Search(const T &value) const;
    LinkNode<T> *Locate(size_t index) const;
    bool getData(size_t index, T &value) const;
    bool setData(size_t index, const T &value);
    bool Insert(size_t index, const T &value);
    bool Remove(size_t index, T &value);
    void input();

    template <typename... Args>
    void input(const Args &...args);

    void output() const;
    CircList<T> &operator=(const CircList<T> &other);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
};

template <typename T>
CircList<T>::CircList()
{
    head = new LinkNode<T>();
    tail = head;
    tail->next = head;
}

template <typename T>
CircList<T>::CircList(const T &value)
{
    head = new LinkNode<T>(value);
    tail = head;
    tail->next = head;
}

template <typename T>
CircList<T>::CircList(const initializer_list<T> &list)
{
    head = new LinkNode<T>();
    tail = head;
    for (const T &value : list)
    {
        tail->next = new LinkNode<T>(value);
        tail = tail->next;
    }
    tail->next = head;
}

template <typename T>
CircList<T>::CircList(const CircList<T> &other)
{
    head = new LinkNode<T>();
    tail = head;
    LinkNode<T> *current = other.head->next;
    while (current != other.head)
    {
        tail->next = new LinkNode<T>(current->data);
        tail = tail->next;
        current = current->next;
    }
    tail->next = head;
}

template <typename T>
CircList<T>::~CircList()
{
    LinkNode<T> *current = head;
    if (current != nullptr)
    {
        LinkNode<T> *start = head;
        do
        {
            LinkNode<T> *temp = current;
            current = current->next;
            delete temp;
        } while (current != start);
    }
}

template <typename T>
int CircList<T>::Length() const
{
    int len = 0;
    LinkNode<T> *current = head->next;
    while (current != head)
    {
        ++len;
        current = current->next;
    }
    return len;
}

template <typename T>
bool CircList<T>::isEmpty() const
{
    return head->next == head;
}

template <typename T>
LinkNode<T> *CircList<T>::getHead() const
{
    return head;
}

template <typename T>
LinkNode<T> *CircList<T>::getTail() const
{
    return tail;
}

template <typename T>
void CircList<T>::setHead(LinkNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    LinkNode<T> *current = node;
    bool found = false;
    if (current != nullptr)
    {
        do
        {
            if (current == node)
            {
                found = true;
                break;
            }
            current = current->next;
        } while (current != head);
    }
    if (found)
    {
        head = node;
    }
    head = node;
    tail = head;
    current = head->next;
    while (current != head)
    {
        tail = current;
        current = current->next;
    }
    tail->next = head;
}

template <typename T>
void CircList<T>::setTail(LinkNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    LinkNode<T> *current = head;
    bool found = false;
    if (current != nullptr)
    {
        do
        {
            if (current == node)
            {
                found = true;
                break;
            }
            current = current->next;
        } while (current != head);
    }
    if (!found)
    {
        return;
    }
    tail = node;
    tail->next = head;
}

template <typename T>
LinkNode<T> *CircList<T>::Search(const T &value) const
{
    LinkNode<T> *current = head->next;
    while (current != head)
    {
        if (current->data == value)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
LinkNode<T> *CircList<T>::Locate(size_t index) const
{
    if (index < 0)
    {
        return nullptr;
    }
    LinkNode<T> *current = head->next;
    size_t count = 0;
    while (current != head)
    {
        if (count == index)
        {
            return current;
        }
        current = current->next;
        ++count;
    }
    return nullptr;
}

template <typename T>
bool CircList<T>::getData(size_t index, T &value) const
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        return false;
    }
    value = node->data;
    return true;
}

template <typename T>
bool CircList<T>::setData(size_t index, const T &value)
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        return false;
    }
    node->data = value;
    return true;
}

template <typename T>
bool CircList<T>::Insert(size_t index, const T &value)
{
    if (index < 0)
    {
        return false;
    }
    LinkNode<T> *node = Locate(index - 1);
    if (node == nullptr)
    {
        return false;
    }
    LinkNode<T> *newNode = new LinkNode<T>(value);
    newNode->next = node->next;
    node->next = newNode;
    if (node == tail)
    {
        tail = newNode;
    }
    return true;
}

template <typename T>
bool CircList<T>::Remove(size_t index, T &value)
{
    if (index < 0)
    {
        return false;
    }
    LinkNode<T> *node = Locate(index - 1);
    if (node == nullptr || node->next == head)
    {
        return false;
    }
    LinkNode<T> *toDelete = node->next;
    value = toDelete->data;
    node->next = toDelete->next;
    if (toDelete == tail)
    {
        tail = node;
    }
    delete toDelete;
    return true;
}

template <typename T>
template <typename... Args>
void CircList<T>::input(const Args &...args)
{
    T temp[] = {args...};
    for (const T &value : temp)
    {
        tail->next = new LinkNode<T>(value);
        tail = tail->next;
    }
    tail->next = head;
} // 后插法

template <typename T>
void CircList<T>::input()
{
    LinkNode<T> *current = tail;
    T value;
    cout << "Enter elements (type 'end' to stop):" << endl;
    while (cin >> value)
    {
        current->next = new LinkNode<T>(value);
        current = current->next;
    }
    current->next = head;
    tail = current;
} // 后插法

template <typename T>
void CircList<T>::output() const
{
    if (isEmpty())
    {
        cout << "CircList is empty!" << endl;
        return;
    }
    cout << "CircList elements: ";
    LinkNode<T> *current = head->next;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

template <typename T>
CircList<T> &CircList<T>::operator=(const CircList<T> &other)
{
    if (this != &other)
    {
        LinkNode<T> *current = head;
        if (current != nullptr)
        {
            LinkNode<T> *start = head;
            do
            {
                LinkNode<T> *temp = current;
                current = current->next;
                delete temp;
            } while (current != start);
        }
        head = new LinkNode<T>();
        tail = head;
        current = other.head->next;
        while (current != other.head)
        {
            tail->next = new LinkNode<T>(current->data);
            tail = tail->next;
            current = current->next;
        }
        tail->next = head;
    }
    return *this;
}

template <typename T>
T &CircList<T>::operator[](size_t index)
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        throw out_of_range("Index out of range");
    }
    return node->data;
}

template <typename T>
const T &CircList<T>::operator[](size_t index) const
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        throw out_of_range("Index out of range");
    }
    return node->data;
}

int main()
{
    system("chcp 65001"); // 设置控制台为UTF-8编码

    cout << "=== 约瑟夫问题求解 ===" << endl
         << endl;

    // 获取参数
    int n, m;
    cout << "请输入总人数 n: ";
    cin >> n;
    cout << "请输入报数 m: ";
    cin >> m;

    if (n <= 0 || m <= 0)
    {
        cout << "输入参数无效！" << endl;
        return 1;
    }

    // 创建循环链表，编号从1到n
    CircList<int> josephus;
    for (int i = 1; i <= n; ++i)
    {
        josephus.input(i);
    }

    cout << "\n初始循环链表: ";
    josephus.output();

    cout << "\n出列顺序: ";

    // 从头节点的下一个节点开始（第一个人）
    LinkNode<int> *current = josephus.getHead()->next;
    LinkNode<int> *prev = josephus.getHead();

    // 找到尾节点，作为初始的前驱节点
    while (prev->next != current)
    {
        prev = prev->next;
    }

    int count = 0;
    while (josephus.Length() > 0)
    {
        count++;

        // 报数到 m
        if (count == m)
        {
            // 输出出列的人
            cout << current->data << " ";

            // 删除当前节点
            LinkNode<int> *toDelete = current;
            prev->next = current->next;

            // 更新 tail（如果删除的是尾节点）
            if (current == josephus.getTail())
            {
                josephus.setTail(prev);
            }

            // 移动到下一个节点
            current = current->next;

            // 如果删除的是头节点的下一个节点，需要特殊处理
            if (toDelete == josephus.getHead()->next)
            {
                josephus.getHead()->next = current;
            }

            delete toDelete;

            // 重置计数
            count = 0;

            // 如果链表为空，退出
            if (prev->next == josephus.getHead())
            {
                break;
            }
        }
        else
        {
            // 移动到下一个节点
            prev = current;
            current = current->next;

            // 跳过头节点
            if (current == josephus.getHead())
            {
                prev = current;
                current = current->next;
            }
        }
    }

    cout << endl
         << endl;

    // 使用标准算法验证
    cout << "=== 使用标准算法验证 ===" << endl;
    CircList<int> josephus2;
    for (int i = 1; i <= n; ++i)
    {
        josephus2.input(i);
    }

    cout << "出列顺序: ";
    LinkNode<int> *curr = josephus2.getHead()->next;
    LinkNode<int> *pre = josephus2.getHead();

    // 找到尾节点
    while (pre->next != josephus2.getHead())
    {
        pre = pre->next;
    }

    while (!josephus2.isEmpty())
    {
        // 报数 m-1 次
        for (int i = 1; i < m; ++i)
        {
            pre = curr;
            curr = curr->next;
            // 跳过头节点
            if (curr == josephus2.getHead())
            {
                pre = curr;
                curr = curr->next;
            }
        }

        // 输出并删除
        cout << curr->data << " ";

        LinkNode<int> *del = curr;
        pre->next = curr->next;

        // 更新头节点的next指针
        if (del == josephus2.getHead()->next)
        {
            josephus2.getHead()->next = curr->next;
        }

        // 更新tail
        if (del == josephus2.getTail())
        {
            josephus2.setTail(pre);
        }

        curr = curr->next;

        // 跳过头节点
        if (curr == josephus2.getHead())
        {
            curr = curr->next;
        }

        delete del;
    }

    cout << endl
         << endl;
    cout << "=== 约瑟夫问题求解完成 ===" << endl;

    return 0;
}