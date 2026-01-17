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
class List
{
private:
    LinkNode<T> *head;
    LinkNode<T> *mergeSort(LinkNode<T> *head);
    LinkNode<T> *merge(LinkNode<T> *left, LinkNode<T> *right);

public:
    List();
    List(const T &value);
    List(const initializer_list<T> &list);
    List(const List<T> &other);
    ~List();
    int Length() const;
    LinkNode<T> *getHead() const;
    LinkNode<T> *getTail() const;
    LinkNode<T> *Search(const T &value) const;
    LinkNode<T> *Locate(size_t index) const;
    bool getData(size_t index, T &value) const;
    bool setData(size_t index, const T &value);
    bool Insert(size_t index, const T &value);
    bool Remove(size_t index, T &value);
    bool isEmpty() const;
    void Sort();
    void input();

    template <typename... Args>
    void input(const Args &...args);

    void output() const;
    List<T> &operator=(const List<T> &other);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
};

template <typename T>
List<T>::List()
{
    head = new LinkNode<T>();
}

template <typename T>
List<T>::List(const T &value)
{
    head = new LinkNode<T>(value);
}

template <typename T>
List<T>::List(const initializer_list<T> &list)
{
    head = new LinkNode<T>();
    LinkNode<T> *tail = head;
    for (const T &value : list)
    {
        tail->next = new LinkNode<T>(value);
        tail = tail->next;
    }
}

template <typename T>
List<T>::List(const List<T> &other)
{
    head = new LinkNode<T>();
    LinkNode<T> *tail = head;
    LinkNode<T> *current = other.head->next;
    while (current != nullptr)
    {
        tail->next = new LinkNode<T>(current->data);
        tail = tail->next;
        current = current->next;
    }
}

template <typename T>
List<T>::~List()
{
    LinkNode<T> *current = head;
    while (current != nullptr)
    {
        LinkNode<T> *temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
int List<T>::Length() const
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

template <typename T>
LinkNode<T> *List<T>::getHead() const
{
    return head;
}

template <typename T>
LinkNode<T> *List<T>::getTail() const
{
    LinkNode<T> *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current;
}

template <typename T>
LinkNode<T> *List<T>::Search(const T &value) const
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

template <typename T>
LinkNode<T> *List<T>::Locate(size_t index) const
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

template <typename T>
bool List<T>::getData(size_t index, T &value) const
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
bool List<T>::setData(size_t index, const T &value)
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
bool List<T>::Insert(size_t index, const T &value)
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
    return true;
}

template <typename T>
bool List<T>::Remove(size_t index, T &value)
{
    if (index < 0)
    {
        return false;
    }
    LinkNode<T> *node = Locate(index - 1);
    if (node == nullptr || node->next == nullptr)
    {
        return false;
    }
    LinkNode<T> *toDelete = node->next;
    value = toDelete->data;
    node->next = toDelete->next;
    delete toDelete;
    return true;
}

template <typename T>
bool List<T>::isEmpty() const
{
    return head->next == nullptr;
}

template <typename T>
void List<T>::input()
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
        tail->next = new LinkNode<T>(value);
        tail = tail->next;
    }
}

template <typename T>
template <typename... Args>
void List<T>::input(const Args &...args)
{
    LinkNode<T> *tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    T temp[] = {args...};
    for (const T &value : temp)
    {
        tail->next = new LinkNode<T>(value);
        tail = tail->next;
    }
} // 后插法

template <typename T>
void List<T>::output() const
{
    if (isEmpty())
    {
        cout << "List is empty!" << endl;
        return;
    }
    cout << "List elements: ";
    LinkNode<T> *current = head->next;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (this != &other)
    {
        LinkNode<T> *current = head;
        while (current != nullptr)
        {
            LinkNode<T> *temp = current;
            current = current->next;
            delete temp;
        }
        head = new LinkNode<T>();
        LinkNode<T> *tail = head;
        current = other.head->next;
        while (current != nullptr)
        {
            tail->next = new LinkNode<T>(current->data);
            tail = tail->next;
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
void List<T>::Sort()
{
    if (isEmpty() || head->next->next == nullptr)
    {
        return;
    }
    head->next = mergeSort(head->next);
}

template <typename T>
LinkNode<T> *List<T>::mergeSort(LinkNode<T> *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    LinkNode<T> *slow = head;
    LinkNode<T> *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    LinkNode<T> *mid = slow->next;
    slow->next = nullptr;
    LinkNode<T> *left = mergeSort(head);
    LinkNode<T> *right = mergeSort(mid);
    return merge(left, right);
}

template <typename T>
LinkNode<T> *List<T>::merge(LinkNode<T> *left, LinkNode<T> *right)
{
    LinkNode<T> dummy;
    LinkNode<T> *tail = &dummy;
    while (left != nullptr && right != nullptr)
    {
        if (left->data <= right->data)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    if (left != nullptr)
    {
        tail->next = left;
    }
    else
    {
        tail->next = right;
    }
    return dummy.next;
}

template <typename T>
T &List<T>::operator[](size_t index)
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        throw out_of_range("Index out of bounds! Index: " + to_string(index) + ", Length: " + to_string(Length()));
    }
    return node->data;
}

template <typename T>
const T &List<T>::operator[](size_t index) const
{
    LinkNode<T> *node = Locate(index);
    if (node == nullptr)
    {
        throw out_of_range("Index out of bounds! Index: " + to_string(index) + ", Length: " + to_string(Length()));
    }
    return node->data;
}

int main()
{
    system("chcp 65001"); // 设置控制台为UTF-8编码

    try
    {
        cout << "=== LinkedList 功能测试 ===" << endl
             << endl;

        // 1. 测试默认构造函数
        cout << "1. 测试默认构造函数:" << endl;
        List<int> list1;
        cout << "创建空链表，长度: " << list1.Length() << endl
             << endl;

        // 2. 测试可变参数初始化
        cout << "2. 测试可变参数初始化:" << endl;
        List<int> list2;
        list2.input(50, 30, 10, 40, 20, 60);
        cout << "初始链表: ";
        list2.output();
        cout << "长度: " << list2.Length() << endl
             << endl;

        // 3. 测试初始化列表构造函数
        cout << "3. 测试初始化列表构造函数:" << endl;
        List<int> list3({100, 200, 300, 400});
        cout << "通过初始化列表创建: ";
        list3.output();
        cout << "长度: " << list3.Length() << endl
             << endl;

        // 4. 测试 Insert
        cout << "4. 测试 Insert (在索引2处插入999):" << endl;
        list2.Insert(2, 999);
        cout << "插入后: ";
        list2.output();
        cout << "新长度: " << list2.Length() << endl
             << endl;

        // 5. 测试 getData
        cout << "5. 测试 getData:" << endl;
        int value;
        if (list2.getData(1, value))
        {
            cout << "索引1处的值: " << value << endl;
        }
        cout << endl;

        // 6. 测试 setData
        cout << "6. 测试 setData (将索引1的值改为777):" << endl;
        list2.setData(1, 777);
        cout << "修改后: ";
        list2.output();
        cout << endl;

        // 7. 测试 Search
        cout << "7. 测试 Search:" << endl;
        LinkNode<int> *node = list2.Search(999);
        if (node != nullptr)
        {
            cout << "找到元素999，其值为: " << node->data << endl;
        }
        else
        {
            cout << "未找到元素999" << endl;
        }

        node = list2.Search(123);
        if (node != nullptr)
        {
            cout << "找到元素123" << endl;
        }
        else
        {
            cout << "未找到元素123" << endl;
        }
        cout << endl;

        // 8. 测试 Locate
        cout << "8. 测试 Locate (定位索引3处):" << endl;
        node = list2.Locate(3);
        if (node != nullptr)
        {
            cout << "索引3处的值: " << node->data << endl;
        }
        cout << endl;

        // 9. 测试 Remove
        cout << "9. 测试 Remove (删除索引2处的元素):" << endl;
        int removedValue;
        if (list2.Remove(2, removedValue))
        {
            cout << "删除的值: " << removedValue << endl;
            cout << "删除后: ";
            list2.output();
            cout << "新长度: " << list2.Length() << endl;
        }
        cout << endl;

        // 10. 测试 isEmpty
        cout << "10. 测试 isEmpty:" << endl;
        cout << "list1 是否为空: " << (list1.isEmpty() ? "是" : "否") << endl;
        cout << "list2 是否为空: " << (list2.isEmpty() ? "是" : "否") << endl;
        cout << endl;

        // 11. 测试 getHead 和 getTail
        cout << "11. 测试 getHead 和 getTail:" << endl;
        LinkNode<int> *headNode = list2.getHead();
        LinkNode<int> *tailNode = list2.getTail();
        cout << "头节点: " << (headNode != nullptr ? "存在" : "不存在") << endl;
        cout << "尾节点数据: " << tailNode->data << endl
             << endl;

        // 12. 测试 Sort (归并排序)
        cout << "12. 测试 Sort (归并排序):" << endl;
        List<int> listToSort;
        listToSort.input(50, 30, 10, 40, 20, 60, 5, 15);
        cout << "排序前: ";
        listToSort.output();
        listToSort.Sort();
        cout << "排序后: ";
        listToSort.output();
        cout << endl;

        // 13. 测试复制构造函数
        cout << "13. 测试复制构造函数:" << endl;
        List<int> list4(listToSort);
        cout << "list4 (listToSort的副本): ";
        list4.output();
        cout << endl;

        // 14. 测试赋值运算符
        cout << "14. 测试赋值运算符:" << endl;
        List<int> list5;
        list5 = list3;
        cout << "list5 = list3 后的结果: ";
        list5.output();
        cout << endl;

        // 15. 测试单个值构造函数
        cout << "15. 测试单个值构造函数:" << endl;
        List<int> list6(888);
        cout << "创建仅包含888的链表: ";
        list6.output();
        cout << "长度: " << list6.Length() << endl
             << endl;

        // 16. 测试多次插入和删除
        cout << "16. 测试多次插入和删除:" << endl;
        List<int> list7;
        list7.input(1, 2, 3, 4, 5);
        cout << "初始: ";
        list7.output();

        list7.Insert(0, 0); // 在开头插入
        cout << "在索引0处插入0: ";
        list7.output();

        list7.Insert(list7.Length(), 6); // 在末尾插入
        cout << "在末尾插入6: ";
        list7.output();

        int val;
        list7.Remove(3, val);
        cout << "删除索引3处(值为" << val << "): ";
        list7.output();
        cout << endl;

        // 17. 测试空链表操作
        cout << "17. 测试空链表操作:" << endl;
        List<int> emptyList;
        cout << "空链表输出: ";
        emptyList.output();
        cout << "空链表长度: " << emptyList.Length() << endl;
        cout << "查找元素1: " << (emptyList.Search(1) != nullptr ? "找到" : "未找到") << endl;
        cout << endl;

        cout << "=== 所有测试完成 ===" << endl;
    }
    catch (const exception &e)
    {
        cout << "ERROR: " << e.what() << endl;
    }

    return 0;
}