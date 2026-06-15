# 第18章：模板 — 知识点

## 18.1 引言
- **代码复用**：组合（Composite）、继承（Inherit）、模板（Template）
- **模板**：使程序员能够指定一整套相关函数和相关类
- **泛型编程**（Generic Programming）：使用**参数化类型**（Parameterized Type）
- 模板 vs. 模板特化：函数模板、类模板

### 模板、函数、类与对象的关系
```
模板(stencil) ──实例化(instantiation)──→ 函数/类
函数/类 ──实例化──→ 对象
```

## 18.2 函数模板

### 函数模板定义
- 以**模板头**开头：
```cpp
template <typename T>      // 或 template <class T>
T max(T v1, T v2) { ... }
```

### 模板参数列表
- 包含在 `<` 和 `>` 中
- 每个模板参数以关键字 `class` 或 `typename` 开头
- 用于指定函数模板的**参数类型**、**局部变量类型**和**返回类型**

### 示例
```cpp
template <typename T>
template <class ElementType>
template <typename BorderType, class Filltype>
```

### 使用函数模板
```cpp
template <typename T>
T max(T v1, T v2) {
    return (v1 > v2) ? v1 : v2;
}

int main() {
    max(1, 0);          // T 被推断为 int
    max(1.0, 0.0);      // T 被推断为 double
    string s1 = "hi", s2 = "world";
    max(s1, s2);        // T 被推断为 string
}
```

### printArray 函数模板（图 18.1）
```cpp
template <typename T>
void printArray(const T *array, int count) {
    for (int i = 0; i < count; i++)
        cout << array[i] << " ";
    cout << endl;
}

int main() {
    const int a[] = {1, 2, 3, 4, 5};
    const double b[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    const char c[] = "HELLO";  // 6th position for null

    printArray(a, 5);  // 创建函数模板特化 printArray<int>
    printArray(b, 7);  // 创建函数模板特化 printArray<double>
    printArray(c, 6);  // 创建函数模板特化 printArray<char>
}
```
- 编译器根据调用时参数类型自动生成对应的函数特化

## 18.3 重载函数模板

### 三种重载方式

#### （1）模板函数之间重载
```cpp
printArray(int, 5);
printArray(double, 7);
printArray(char, 6);
```

#### （2）函数模板之间重载（同名不同参数列表）
```cpp
template <typename T>
void printArray(const T *array, int count);

template <typename T>
void printArray(const T *array, int low, int high);
```

#### （3）函数模板与非模板函数重载（同名不同参数列表）
```cpp
template <typename T>
void printArray(const T *array, int count);       // 模板版本

void printArray(const int *array, int count);     // 非模板版本（专门处理 int）
```

## 18.4 类模板

### 概念
- 类是问题空间的抽象
- **类模板**是类的抽象 — 为具有相同结构但不同类型的**一组类**提供标准

### 类模板定义
```cpp
template <typename T>
class A {
public:
    T getX();
    void setX(const T &);
private:
    T x;
};
```
- `T` 是类的类型参数
- 数据成员的类型、成员函数中参数/局部变量/返回值的类型都可以使用 `T`

### 类外成员函数定义
```cpp
// 每个成员函数定义前必须加上模板头
template <typename T>
T A<T>::getX() {
    return x;
}

template <typename T>
void A<T>::setX(const T &a) {
    x = a;
}
```
- 使用泛型类名 `A<T>` 而非 `A`

### 类模板的使用（实例化）
```cpp
A<int> a;           // int 版本的类
a.setX(0);
cout << a.getX();

A<double> b;        // double 版本的类
b.setX(1.0);
cout << b.getX();
```
- 格式：`ClassName<type> obj;`

### Stack 类模板案例（图 18.2~18.4）
```cpp
template <typename T>
class Stack {
public:
    Stack(int = 10);          // 默认构造函数（栈大小10）
    ~Stack() { delete[] stackPtr; }
    bool push(const T &);     // 压入元素
    bool pop(T &);            // 弹出元素
    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == size - 1; }
private:
    int size;
    int top;
    T *stackPtr;  // 指向 T 类型数组的指针
};

// 构造函数
template <typename T>
Stack<T>::Stack(int s)
    : size(s > 0 ? s : 10), top(-1),
      stackPtr(new T[size]) {}

// push
template <typename T>
bool Stack<T>::push(const T &pushValue) {
    if (!isFull()) {
        stackPtr[++top] = pushValue;  // 先+1，再设值
        return true;
    }
    return false;
}

// pop
template <typename T>
bool Stack<T>::pop(T &popValue) {
    if (!isEmpty()) {
        popValue = stackPtr[top--];   // 先取值，再-1
        return true;
    }
    return false;
}
```

### 测试程序
```cpp
Stack<double> doubleStack(5);    // double 类型，大小5
Stack<int> intStack;             // int 类型，默认大小10

doubleStack.push(1.1);
intStack.push(1);
```

### 使用函数模板处理类模板特化（图 18.4）
```cpp
template <typename T>
void testStack(Stack<T> &theStack, T value, T increment,
               const string stackName) {
    while (theStack.push(value)) {
        cout << value << ' ';
        value += increment;
    }
    // ...
}

int main() {
    Stack<double> doubleStack(5);
    Stack<int> intStack;
    testStack(doubleStack, 1.1, 1.1, "doubleStack");
    testStack(intStack, 1, 1, "intStack");
}
```

## 18.5 非类型参数与默认类型

### 非类型模板参数
```cpp
template <typename T, int elements>
class Stack {
public:
    Stack() : top(-1) { ... }
    bool push(const T &);
    bool pop(T &);
    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == elements - 1; }
private:
    int top;
    T stackPtr[elements];  // 固定大小数组，不需要 size 成员
};
```

### 成员函数定义（带非类型参数）
```cpp
template <typename T, int elements>
Stack<T, elements>::Stack() : top(-1) { ... }

template <typename T, int elements>
bool Stack<T, elements>::push(const T &pushValue) {
    if (!isFull()) {
        stackPtr[++top] = pushValue;
        return true;
    }
    return false;
}
```

### 使用
```cpp
Stack<int, 100> intStack;     // int 类型，100个元素
intStack.push(1);
Stack<double, 200> doubleStack;  // double 类型，200个元素
doubleStack.push(1.0);
```
- `elements` 的值在**编译时**确定，必须是常量表达式
- `const int size = 100; Stack<int, size> s1;` ✓
- `Stack<int, 100> s2;` ✓
- `int n = 100; Stack<int, n> s1;` ✗（n 不是常量）

### 带默认值的非类型参数
```cpp
template <typename T, int elements = 5>
class Stack { ... };

Stack<int> s;  // elements 默认为 5，即 Stack<int, 5>
```

### 显式特化
- 当特定类型不适用于通用模板或需要定制处理时使用
- 格式：
```cpp
template<>
class Stack<Employee> { ... };  // 完全替代通用模板
```
- 可以有完全不同的成员

## 18.6 模板与继承的注意事项

| 关系 | 说明 |
|------|------|
| 类模板 → 实例化 → 模板类 → 继承 → 派生模板类 | 从模板类派生 |
| 类模板 → 继承 → 派生类模板 | 从类模板派生 |
| 非模板类 → 继承 → 类模板 | 模板也可以继承非模板类 |
| 类模板 → 实例化 → 模板类 → 继承 → 非模板派生类 | 从模板类派生出非模板类 |

## 18.7 模板与友元的注意事项

### 友元关系模式

| 友元类型 | 友元范围 | 关系 |
|---------|---------|------|
| 全局函数 | 特定模板类 | 1:1 |
| 另一个类的成员函数 | 所有模板类特化 | 1:N |
| 另一个类模板的成员函数 | 仅相同类型参数的模板类 | 1:1 |
| 另一个类 | 所有模板类特化 | 1:N |
| 另一个类模板 | 仅相同类型参数的模板类 | 1:1 |

### 示例
```cpp
template <typename T>
class X {
    friend void f1();                // 全局函数友元
    friend void A::f3();             // A::f3 是 X<double>, X<string> 等所有特化的友元 (1:N)
    friend void C<T>::f4(X<T> &);    // C<float>::f4 仅是 X<float> 的友元 (1:1)
    friend class Y;                  // Y 是所有特化的友元 (1:N)
    friend class Z<T>;               // Z<float> 仅是 X<float> 的友元 (1:1)
};
```

## 18.8 模板与 static 成员的注意事项

### 规则
- 类模板的每个**特化**都有自己的一份 `static` 数据成员副本
- 该特化的所有对象**共享**该副本
- `static` 数据成员必须在文件作用域定义和初始化

### 示例
```cpp
template <typename T>
class A {
public:
    static int x;
};

template <typename T>
int A<T>::x = 0;  // 文件作用域定义

int main() {
    A<int>::x = 10;
    A<double>::x = 20;

    A<int> a1, a2;
    cout << a1.x << " ";   // 10
    a1.x = 15;
    cout << a2.x << endl;  // 15 (共享)

    A<double> b1, b2;
    cout << b1.x << " " << b2.x << endl;  // 20 20 (不同特化，独立副本)
    return 0;
}
// 输出：10 15
//      20 20
```

- `A<int>` 和 `A<double>` 各自拥有独立的 `static int x`
- 类模板的每个特化也有自己独立的 `static` 成员函数副本

## 模板 vs. 继承

| 场景 | 使用 |
|------|------|
| 对象类型**不影响**成员函数定义 | 使用**类模板**生成一组类 |
| 对象类型**影响**成员函数定义 | 使用**继承**生成一组类 |

---

## 小结：
1. 模板 = 泛型编程 + 参数化类型
2. 函数模板：`template <typename T> T func(...)`，编译器自动推断类型
3. 函数模板重载：模板之间、模板 vs. 非模板函数
4. 类模板：类外成员函数定义需以 `template <typename T>` 开头，使用 `ClassName<T>::`
5. Stack 类模板案例（图 18.2~18.4）
6. 非类型参数：`template <typename T, int elements>`，值编译时确定
7. 默认类型/默认值：`template <typename T, int elements = 5>`
8. 显式特化：`template<> class Stack<Employee> { ... };`
9. 模板与继承 — 多种组合关系
10. 模板与友元 — 1:1 和 1:N 关系模式
11. 模板与 static — 每个特化独立拥有一份静态成员
