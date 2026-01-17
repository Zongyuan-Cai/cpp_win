#include <iostream>
#include <stdexcept>
#include <initializer_list>
using namespace std;
const int defaultSize = 100;
template <typename T>
class SeqList
{
private:
    T *data;
    int maxSize;
    int length;
    void reSize(int newSize);

public:
    SeqList(int size = defaultSize);
    SeqList(const initializer_list<T> &list);
    SeqList(const SeqList<T> &other);
    ~SeqList();
    int Size() const;
    int Length() const;
    int Search(const T &value) const;
    bool getData(int index, T &value) const;
    bool setData(int index, const T &value);
    bool Insert(int index, const T &value);
    bool Remove(int index, T &value);
    bool isEmpty() const;
    bool isFull() const;
    void input();

    template <typename... Args>
    void input(const Args &...args);

    void output() const;

    SeqList<T> &operator=(const SeqList<T> &other);
};

template <typename T>
void SeqList<T>::reSize(int newSize)
{
    if (newSize <= 0 || newSize == maxSize || newSize < length)
    {
        throw invalid_argument("Invalid new size! Size must be positive, not equal to maxSize, and not less than length.");
    }
    T *newData = new T[newSize];
    if (newData == nullptr)
    {
        throw bad_alloc();
    }
    for (int i = 0; i < length; ++i)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    maxSize = newSize;
}

template <typename T>
SeqList<T>::SeqList(int size)
{
    if (size <= 0)
    {
        throw invalid_argument("Size must be positive!");
    }
    data = new T[size];
    if (data == nullptr)
    {
        throw bad_alloc();
    }
    maxSize = size;
    length = 0;
}

template <typename T>
SeqList<T>::SeqList(const initializer_list<T> &list)
{
    maxSize = list.size();
    length = list.size();
    data = new T[maxSize];
    if (data == nullptr)
    {
        throw bad_alloc();
    }
    int index = 0;
    for (const auto &item : list)
    {
        data[index++] = item;
    }
}

template <typename T>
SeqList<T>::SeqList(const SeqList<T> &other)
{
    maxSize = other.maxSize;
    length = other.length;
    data = new T[maxSize];
    if (data == nullptr)
    {
        throw bad_alloc();
    }
    for (int i = 0; i < length; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
SeqList<T>::~SeqList()
{
    delete[] data;
}

template <typename T>
int SeqList<T>::Size() const
{
    return maxSize;
}

template <typename T>
int SeqList<T>::Length() const
{
    return length;
}

template <typename T>
int SeqList<T>::Search(const T &value) const
{
    for (int i = 0; i < length; ++i)
    {
        if (data[i] == value)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
bool SeqList<T>::getData(int index, T &value) const
{
    if (index < 0 || index >= length)
    {
        throw out_of_range("Index out of bounds! Index: " + to_string(index) + ", Length: " + to_string(length));
    }
    value = data[index];
    return true;
}

template <typename T>
bool SeqList<T>::setData(int index, const T &value)
{
    if (index < 0 || index >= length)
    {
        throw out_of_range("Index out of bounds! Index: " + to_string(index) + ", Length: " + to_string(length));
    }
    data[index] = value;
    return true;
}

template <typename T>
bool SeqList<T>::Insert(int index, const T &value)
{
    if (isFull())
    {
        throw overflow_error("List is full! Cannot insert more elements.");
    }
    if (index < 0 || index > length)
    {
        throw out_of_range("Invalid insert position! Index: " + to_string(index) + ", Length: " + to_string(length));
    }
    for (int i = length; i > index; --i)
    {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++length;
    return true;
}

template <typename T>
bool SeqList<T>::Remove(int index, T &value)
{
    if (isEmpty())
    {
        throw underflow_error("List is empty! Cannot remove elements.");
    }
    if (index < 0 || index >= length)
    {
        throw out_of_range("Index out of bounds! Index: " + to_string(index) + ", Length: " + to_string(length));
    }
    value = data[index];
    for (int i = index; i < length - 1; ++i)
    {
        data[i] = data[i + 1];
    }
    --length;
    return true;
}

template <typename T>
bool SeqList<T>::isEmpty() const
{
    return length == 0;
}

template <typename T>
bool SeqList<T>::isFull() const
{
    return length == maxSize;
}

template <typename T>
void SeqList<T>::input()
{
    cout << "Enter number of elements to input: ";
    int n;
    cin >> n;
    if (n > maxSize)
    {
        cout << "Input exceeds maximum size. Resizing..." << endl;
        reSize(n);
    }
    length = n;
    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }
}

template <typename T>
template <typename... Args>
void SeqList<T>::input(const Args &...args)
{
    constexpr int n = sizeof...(args);
    if (n > maxSize)
    {
        cout << "Input exceeds maximum size. Resizing..." << endl;
        reSize(n);
    }
    length = n;
    T temp[] = {args...};
    for (int i = 0; i < n; ++i)
    {
        data[i] = temp[i];
    }
}

template <typename T>
void SeqList<T>::output() const
{
    if (isEmpty())
    {
        cout << "List is empty!" << endl;
        return;
    }
    cout << "List elements: ";
    for (int i = 0; i < length; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

template <typename T>
SeqList<T> &SeqList<T>::operator=(const SeqList<T> &other)
{
    if (this != &other)
    {
        delete[] data;
        maxSize = other.maxSize;
        length = other.length;
        data = new T[maxSize];
        if (data == nullptr)
        {
            throw bad_alloc();
        }
        for (int i = 0; i < length; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

int main()
{
    system("chcp 65001"); // 设置控制台为UTF-8编码

    try
    {
        cout << "=== SeqList 功能测试 ===" << endl
             << endl;

        // 1. 测试初始化和基本操作
        cout << "1. 使用可变参数初始化列表:" << endl;
        SeqList<int> list1;
        list1.input(10, 20, 30, 40, 50);
        list1.output();
        cout << "Size: " << list1.Size() << ", Length: " << list1.Length() << endl
             << endl;

        // 2. 测试初始化列表构造函数
        cout << "2. 使用初始化列表构造函数:" << endl;
        SeqList<int> list2({100, 200, 300});
        list2.output();
        cout << "Size: " << list2.Size() << ", Length: " << list2.Length() << endl
             << endl;

        // 3. 测试 Insert
        cout << "3. 在索引2处插入元素 999:" << endl;
        list1.Insert(2, 999);
        list1.output();
        cout << "新长度: " << list1.Length() << endl
             << endl;

        // 4. 测试 Remove
        cout << "4. 删除索引4处的元素:" << endl;
        int removedValue;
        list1.Remove(4, removedValue);
        cout << "删除的值: " << removedValue << endl;
        list1.output();
        cout << "新长度: " << list1.Length() << endl
             << endl;

        // 5. 测试 Search
        cout << "5. 查找元素 30 的索引:" << endl;
        int idx = list1.Search(30);
        if (idx != -1)
        {
            cout << "找到，索引为: " << idx << endl;
        }
        else
        {
            cout << "未找到" << endl;
        }

        cout << "查找元素 999 的索引:" << endl;
        idx = list1.Search(999);
        if (idx != -1)
        {
            cout << "找到，索引为: " << idx << endl;
        }
        else
        {
            cout << "未找到" << endl;
        }
        cout << endl;

        // 6. 测试 getData 和 setData
        cout << "6. 测试 getData 和 setData:" << endl;
        int value;
        list1.getData(0, value);
        cout << "索引0的值: " << value << endl;
        list1.setData(0, 111);
        cout << "将索引0修改为111" << endl;
        list1.output();
        cout << endl;

        // 7. 测试 isEmpty 和 isFull
        cout << "7. 测试 isEmpty 和 isFull:" << endl;
        cout << "list1 是否为空: " << (list1.isEmpty() ? "是" : "否") << endl;
        cout << "list1 是否已满: " << (list1.isFull() ? "是" : "否") << endl;
        cout << endl;

        // 8. 测试复制构造函数
        cout << "8. 测试复制构造函数:" << endl;
        SeqList<int> list3(list1);
        cout << "list3 (list1的副本):" << endl;
        list3.output();
        cout << endl;

        // 9. 测试赋值运算符
        cout << "9. 测试赋值运算符:" << endl;
        SeqList<int> list4;
        list4 = list2;
        cout << "list4 = list2 后的结果:" << endl;
        list4.output();
        cout << endl;

        // 10. 测试空列表的输出
        cout << "10. 测试空列表:" << endl;
        SeqList<int> emptyList(5);
        emptyList.output();
        cout << endl;

        // 11. 测试异常处理 - 越界访问
        cout << "11. 测试异常处理 - getData越界访问:" << endl;
        int testValue;
        list1.getData(100, testValue); // 将抛出异常
    }
    catch (const out_of_range &e)
    {
        cout << "ERROR [out_of_range]: " << e.what() << endl;
    }
    catch (const overflow_error &e)
    {
        cout << "ERROR [overflow_error]: " << e.what() << endl;
    }
    catch (const underflow_error &e)
    {
        cout << "ERROR [underflow_error]: " << e.what() << endl;
    }
    catch (const invalid_argument &e)
    {
        cout << "ERROR [invalid_argument]: " << e.what() << endl;
    }
    catch (const bad_alloc &e)
    {
        cout << "ERROR [bad_alloc]: Memory allocation failed! " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "ERROR [unknown exception]: " << e.what() << endl;
    }

    cout << "=== 测试完成 ===" << endl;

    return 0;
}