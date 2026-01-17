#include <iostream>
#include <initializer_list>
using namespace std;
template <typename T>
struct LinkNode
{
    T data;
    LinkNode *lext;
    LinkNode *next;
    LinkNode(const T &d = T(), LinkNode *l = nullptr, LinkNode *n = nullptr) : data(d), lext(l), next(n) {}
};
template <typename T>
class DblList
{
private:
    LinkNode<T> *head;

public:
    DblList();
    DblList(const T &value);
    DblList(const initializer_list<T> &list);
    DblList(const DblList<T> &other);
    ~DblList();
    int Length() const;
    bool isEmpty() const;
    LinkNode<T> *getHead() const;
    LinkNode<T> *getTail() const;
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
    DblList<T> &operator=(const DblList<T> &other);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
};

// 默认构造函数
template <typename T>
DblList<T>::DblList()
{
    head = new LinkNode<T>();
    head->next = nullptr;
    head->lext = nullptr;
}

// 单值构造函数
template <typename T>
DblList<T>::DblList(const T &value)
{
    head = new LinkNode<T>();
    head->next = new LinkNode<T>(value, head, nullptr);
    head->lext = nullptr;
}

// 初始化列表构造函数
template <typename T>
DblList<T>::DblList(const initializer_list<T> &list)
{
    head = new LinkNode<T>();
    head->lext = nullptr;
    LinkNode<T> *tail = head;

    for (const T &value : list)
    {
        LinkNode<T> *newNode = new LinkNode<T>(value, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
    }
}

// 拷贝构造函数
template <typename T>
DblList<T>::DblList(const DblList<T> &other)
{
    head = new LinkNode<T>();
    head->lext = nullptr;
    LinkNode<T> *tail = head;
    LinkNode<T> *current = other.head->next;

    while (current != nullptr)
    {
        LinkNode<T> *newNode = new LinkNode<T>(current->data, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
        current = current->next;
    }
}

// 析构函数
template <typename T>
DblList<T>::~DblList()
{
    LinkNode<T> *current = head;
    while (current != nullptr)
    {
        LinkNode<T> *temp = current;
        current = current->next;
        delete temp;
    }
}

// 获取长度
template <typename T>
int DblList<T>::Length() const
{
    int len = 0;
    LinkNode<T> *current = head->next;
    while (current != nullptr)
    {
        ++len;
        current = current->next;
    }
    return len;
}

// 判断是否为空
template <typename T>
bool DblList<T>::isEmpty() const
{
    return head->next == nullptr;
}

// 获取头节点
template <typename T>
LinkNode<T> *DblList<T>::getHead() const
{
    return head;
}

// 获取尾节点
template <typename T>
LinkNode<T> *DblList<T>::getTail() const
{
    LinkNode<T> *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current;
}

// 查找值
template <typename T>
LinkNode<T> *DblList<T>::Search(const T &value) const
{
    LinkNode<T> *current = head->next;
    while (current != nullptr)
    {
        if (current->data == value)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// 定位索引
template <typename T>
LinkNode<T> *DblList<T>::Locate(size_t index) const
{
    if (index < 0)
    {
        return nullptr;
    }
    LinkNode<T> *current = head->next;
    size_t count = 0;
    while (current != nullptr)
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

// 获取数据
template <typename T>
bool DblList<T>::getData(size_t index, T &value) const
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        return false;
    }
    value = node->data;
    return true;
}

// 设置数据
template <typename T>
bool DblList<T>::setData(size_t index, const T &value)
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        return false;
    }
    node->data = value;
    return true;
}

// 插入
template <typename T>
bool DblList<T>::Insert(size_t index, const T &value)
{
    if (index < 0 || index > Length())
    {
        return false;
    }

    LinkNode<T> *prev = head;

    // 找到插入位置的前驱节点
    for (size_t i = 0; i < index; ++i)
    {
        prev = prev->next;
        if (prev == nullptr)
        {
            return false;
        }
    }

    LinkNode<T> *newNode = new LinkNode<T>(value, prev, prev->next);
    if (prev->next != nullptr)
    {
        prev->next->lext = newNode;
    }
    prev->next = newNode;
    return true;
}

// 删除
template <typename T>
bool DblList<T>::Remove(size_t index, T &value)
{
    if (isEmpty() || index < 0)
    {
        return false;
    }

    LinkNode<T> *toDelete = Locate(index);
    if (toDelete == nullptr)
    {
        return false;
    }

    value = toDelete->data;

    // 更新前驱节点的next指针
    toDelete->lext->next = toDelete->next;

    // 更新后继节点的lext指针
    if (toDelete->next != nullptr)
    {
        toDelete->next->lext = toDelete->lext;
    }

    delete toDelete;
    return true;
}

// 从键盘输入
template <typename T>
void DblList<T>::input()
{
    int n;
    cout << "Enter number of elements to input: ";
    cin >> n;
    cout << "Enter " << n << " elements:" << endl;

    LinkNode<T> *tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }

    for (int i = 0; i < n; ++i)
    {
        T value;
        cin >> value;
        LinkNode<T> *newNode = new LinkNode<T>(value, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
    }
}

// 可变参数输入
template <typename T>
template <typename... Args>
void DblList<T>::input(const Args &...args)
{
    LinkNode<T> *tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }

    T temp[] = {args...};
    for (const T &value : temp)
    {
        LinkNode<T> *newNode = new LinkNode<T>(value, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
    }
}

// 输出
template <typename T>
void DblList<T>::output() const
{
    if (isEmpty())
    {
        cout << "DblList is empty!" << endl;
        return;
    }
    cout << "DblList elements: ";
    LinkNode<T> *current = head->next;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 赋值运算符
template <typename T>
DblList<T> &DblList<T>::operator=(const DblList<T> &other)
{
    if (this != &other)
    {
        // 删除当前链表
        LinkNode<T> *current = head;
        while (current != nullptr)
        {
            LinkNode<T> *temp = current;
            current = current->next;
            delete temp;
        }

        // 复制新链表
        head = new LinkNode<T>();
        head->lext = nullptr;
        LinkNode<T> *tail = head;
        current = other.head->next;

        while (current != nullptr)
        {
            LinkNode<T> *newNode = new LinkNode<T>(current->data, tail, nullptr);
            tail->next = newNode;
            tail = newNode;
            current = current->next;
        }
    }
    return *this;
}

// 下标运算符
template <typename T>
T &DblList<T>::operator[](size_t index)
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        throw out_of_range("Index out of range");
    }
    return node->data;
}

// 下标运算符（const版本）
template <typename T>
const T &DblList<T>::operator[](size_t index) const
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
    system("chcp 65001");

    cout << "=== 双向链表功能测试 ===" << endl
         << endl;

    // 1. 测试默认构造
    cout << "1. 测试默认构造:" << endl;
    DblList<int> list1;
    cout << "长度: " << list1.Length() << endl
         << endl;

    // 2. 测试可变参数输入
    cout << "2. 测试可变参数输入:" << endl;
    DblList<int> list2;
    list2.input(10, 20, 30, 40, 50);
    list2.output();
    cout << "长度: " << list2.Length() << endl
         << endl;

    // 3. 测试初始化列表构造
    cout << "3. 测试初始化列表构造:" << endl;
    DblList<int> list3({100, 200, 300, 400});
    list3.output();
    cout << "长度: " << list3.Length() << endl
         << endl;

    // 4. 测试插入
    cout << "4. 测试插入(在索引2处插入999):" << endl;
    list2.Insert(2, 999);
    list2.output();
    cout << "长度: " << list2.Length() << endl
         << endl;

    // 5. 测试删除
    cout << "5. 测试删除(删除索引1):" << endl;
    int val;
    list2.Remove(1, val);
    cout << "删除的值: " << val << endl;
    list2.output();
    cout << "长度: " << list2.Length() << endl
         << endl;

    // 6. 测试查找
    cout << "6. 测试查找:" << endl;
    LinkNode<int> *found = list2.Search(999);
    cout << "查找999: " << (found != nullptr ? "找到" : "未找到") << endl;
    found = list2.Search(777);
    cout << "查找777: " << (found != nullptr ? "找到" : "未找到") << endl
         << endl;

    // 7. 测试getData和setData
    cout << "7. 测试getData和setData:" << endl;
    int value;
    list2.getData(0, value);
    cout << "索引0的值: " << value << endl;
    list2.setData(0, 888);
    cout << "修改索引0为888后: ";
    list2.output();
    cout << endl;

    // 8. 测试下标运算符
    cout << "8. 测试下标运算符:" << endl;
    cout << "list2[1] = " << list2[1] << endl;
    list2[1] = 555;
    cout << "修改后: ";
    list2.output();
    cout << endl;

    // 9. 测试拷贝构造
    cout << "9. 测试拷贝构造:" << endl;
    DblList<int> list4(list2);
    cout << "list4(list2的副本): ";
    list4.output();
    cout << endl;

    // 10. 测试赋值运算符
    cout << "10. 测试赋值运算符:" << endl;
    DblList<int> list5;
    list5 = list3;
    cout << "list5 = list3: ";
    list5.output();
    cout << endl;

    // 11. 测试双向遍历
    cout << "11. 测试双向遍历(从尾到头):" << endl;
    LinkNode<int> *tail = list2.getTail();
    cout << "从尾到头: ";
    while (tail != list2.getHead())
    {
        cout << tail->data << " ";
        tail = tail->lext;
    }
    cout << endl
         << endl;

    cout << "=== 所有测试完成 ===" << endl;

    return 0;
}