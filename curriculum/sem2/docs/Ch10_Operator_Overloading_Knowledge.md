# 第10章：运算符重载 — 知识点

## 10.1 引言
- 运算符重载使程序更易读，编程更方便
- 内置运算符已被重载：`operator+(int,int)` vs `operator+(double,double)`
- 对用户自定义对象的运算符重载通常是类对象所必需的
- 扩展 C++ 的直接而自然的方式

## 10.2 运算符重载基础

### 基本概念
- 要在类对象上使用运算符，必须为该类重载该运算符
- **三个例外**（也可以被重载）：赋值（`=`）、取地址（`&`）、逗号（`,`）
- 重载提供简洁的表示法：
  - `complex1.add(complex2)` → `complex1 + complex2`

### 运算符函数定义：
- 函数名：`operator@`（关键字 `operator` + 操作符 `@`）
- 示例：`Complex operator+(const Complex& a);`

### 运算符函数调用：
- `complex1 + complex2;` — 编译器将其解释为函数调用

## 10.3 运算符重载的限制

### 不能：
- 创建**新的**运算符
- 改变运算符的**优先级**
- 改变**结合性**（左到右 / 右到左）
- 改变**操作数个数**（元数）

### 一元/二元/三元：
| 运算符类型 | 示例 |
|--------------|----------|
| 一元 | `+1`、`-1`、`!0`…… |
| 二元 | `1+2`、`1-2`、`1*2`…… |
| 三元 | `?:`（唯一的三元运算符） |

### 也可以用作二元的一元运算符：`+`、`-`、`*`、`&`

### 重要限制：
- 运算符对**基本类型**的工作方式不能改变
- 运算符重载仅适用于**用户自定义类型**的对象
- `int + int` — 不能改变；`complex + complex` — 可以重载；`complex + int` — 可以定义

## 10.4 运算符函数作为类成员 vs. 全局函数

### 作为成员函数：
```cpp
class String {
public:
    bool operator!() const;
};
// 定义：
T ClassName::operator op (...) {
    // 函数体
}
```
- 使用 `*this` 隐式获取左（或唯一）操作数
- 左操作数必须是**同类**的对象（或引用）
- 参数个数 = **操作数个数 - 1**
- **运算符 `()`、`[]`、`->` 或任何赋值运算符必须作为成员函数重载**

### 示例（成员函数）：
```cpp
a3 = a1 * a2;    →  a3 = a1.operator*(a2);
a3 = a1++;       →  a3 = a1.operator++();
a3 += a1;        →  a3.operator+=(a1);
```

### 作为全局函数：
```cpp
T operator op (...) {
    // 函数体
}
```
- 没有 `this` 指针
- 需要**所有**操作数的参数
- 参数个数 = **操作数个数**
- 左对象可以是不同类或基本类型
- 可以是 **friend** 以访问非公有数据

### 示例（全局函数）：
```cpp
a3 = a1 * a2;    →  a3 = operator*(a1, a2);
a3 = a1++;       →  a3 = operator++(a1);
a3 += a1;        →  operator+=(a3, a1);
```

### 交换律运算符：
- 要使 `+` 满足交换律（`a+b` 和 `b+a` 对不同类都适用）：
  - `ComplexClass + int` 和 `int + ComplexClass` — 可能需要全局函数

## 10.5 重载流插入和流提取运算符

### `<<` 运算符（流插入）：
```cpp
ostream &operator<<(ostream &output, const PhoneNumber &number) {
    output << ... ;
    return output;  // 允许级联：cout << a << b;
}
```
- 必须是**全局函数**（左操作数是 `ostream`，不是用户类）
- 返回 `ostream` 的引用以支持**级联**调用

### `>>` 运算符（流提取）：
```cpp
istream &operator>>(istream &input, PhoneNumber &number) {
    input >> ...;
    return input;  // 允许级联：cin >> a >> b;
}
```
- 使用 `input.ignore()` 跳过字符
- 使用 `setw(n)` 限制读取的字符数

### 示例：PhoneNumber 类
- 存储：`areaCode`（3位）、`exchange`（3位）、`line`（4位）
- 格式：`(123) 456-7890`
- `cin >> phone` 读取：跳过 `(`，读取3位区号，跳过 `)` 和空格，读取3位交换码，跳过 `-`，读取4位号码
- `cout << phone` 输出：`(areaCode) exchange-line`

## 10.6 重载一元运算符

### 两种方式：

**（1）作为无参数的非静态成员函数：**
- 解释为：`Object.operator op()`
- `this` 作为隐式操作数

**（2）作为带一个参数的全局函数：**
- 参数必须是类的对象（或引用）
- 解释为：`operator op(Object)`

## 10.7 重载二元运算符

### 两种方式：

**（1）作为带一个参数的非静态成员函数：**
- 解释为：`ObjectL.operator op(ObjectR)`
- `this` → ObjectL；参数 → ObjectR

**（2）作为带两个参数的全局函数：**
- 解释为：`operator op(ObjectL, ObjectR)`

## 10.8 案例研究：Array 类（图 10.10~10.11）

### 关键特性：
- 动态分配的整数数组
- 默认构造函数：`Array(int = 10)`
- 复制构造函数：`Array(const Array &)` — 深复制
- 析构函数：`~Array()` — 释放 `delete[] ptr`
- 赋值运算符：`const Array &operator=(const Array &)` — 检查自赋值，大小不同时重新分配
- 相等判断：`bool operator==(const Array &) const`
- 不等判断：`bool operator!=(const Array &right) const { return !(*this == right); }` — 重用 `==`
- 下标（左值）：`int &operator[](int)` — 返回引用，允许修改
- 下标（右值）：`int operator[](int) const` — 返回副本，用于 const 对象
- 流运算符：`friend ostream &operator<<` 和 `friend istream &operator>>`

### 赋值运算符模式：
1. 检查**自赋值**：`if (&right != this)`
2. 如果大小不同，`delete[]` 旧数组，分配新数组
3. 复制元素
4. 返回 `*this`（允许级联：`x = y = z`）

## 10.9 类型之间的转换

### 两个方向：

**（1）转换构造函数 — 其他类型 → 类类型：**
- 单参数构造函数
- 将基本类型或另一个类类型转换为本类类型
- 格式：`ClassName(T) { ... // 转换方法 }`

**（2）转换/类型转换运算符 — 类类型 → 其他类型：**
- 一种特殊的成员函数
- 将本类类型转换为基本类型或另一个类类型
- 格式：
```cpp
ClassName::operator T() {
    // 转换方法
    return data_Of_T;
}
```
- 是一个**非静态成员函数**
- 目标类型 `T` 可以是基本类型或用户自定义类型
- **无参数，无返回类型**，但必须返回一个 `T` 类型的对象

## 10.10 案例研究：String 类（图 10.1）

### 关键特性：
- 动态字符数组（`char *sPtr`）+ 长度跟踪
- **转换/默认构造函数**：`String(const char * = "")` — 将 `char*` 转换为 String
- **复制构造函数**：`String(const String &)`
- **析构函数**：`~String()` — 释放动态内存
- **赋值运算符**：`const String &operator=(const String &)`
- **拼接**：`const String &operator+=(const String &)`
- **判空**：`bool operator!() const` — String 是否为空？
- **关系运算符**：`==`、`!=`（重用 `==`）、`<`、`>`（重用 `<`）、`<=`（重用 `>`）
  - 展示了**代码可重用性**：`!=` 调用 `==`，`>` 调用 `<`，`<=` 调用 `>`
- **下标运算符**：`char &operator[](int)`（左值）和 `char operator[](int) const`（右值）
- **函数调用运算符（子串）**：`String operator()(int index, int subLength = 0) const`
- **工具函数**：`void setString(const char *)` — 被构造函数和 `operator=` 调用

## 10.11 重载 ++ 和 --

### 前缀自增（++x）：
- 通过**引用**返回：`Date &operator++()`
- 修改对象，返回 `*this`（创建左值）

### 后缀自增（x++）：
- 有一个哑元 `int` 参数（未命名）以区别于前缀
- 通过**值**返回：`Date operator++(int)`
- 将当前状态保存在临时对象中，自增，返回**未自增的临时对象**（不是引用）

```cpp
Date &Date::operator++() {      // 前缀
    helpIncrement();
    return *this;
}
Date Date::operator++(int) {    // 后缀
    Date temp = *this;
    helpIncrement();
    return temp;  // 值返回，不是引用
}
```

## 10.12 案例研究：Date 类（图 10.6~10.7）

### 特性：
- 默认构造函数、`setDate()`、`leapYear()`、`endOfMonth()`
- 前缀/后缀 `++` 重载
- `+=` 运算符：`const Date &operator+=(int)` — 返回 `*this` 支持级联
- `<<` 运算符：输出 "Month day, year" 格式
- 工具函数：`helpIncrement()` — 处理日/月/年进位

## 10.13 标准库类 string
- C++ 标准类：`#include <string>`（作为参考提及，类似于自定义的 String 类）

## 10.14 显式构造函数
- 单参数构造函数上的关键字 `explicit` 防止**隐式**转换
- `explicit Array(int = 10);` — 防止意外转换 `outputArray(3)` 将 int 转换为 Array
- 没有 `explicit`，`3` 会被静默转换为 `Array(3)`

---

## 小结：
1. 哪些运算符可以重载、何时、如何以及限制
2. 成员函数 vs. 全局函数的方法
3. 重载一元和二元运算符
4. 转换构造函数（→ 类类型）vs. 转换运算符（类类型 →）
5. Array、String、Date 类案例研究
6. 前缀 vs. 后缀 `++`/`--`
7. 显式构造函数
