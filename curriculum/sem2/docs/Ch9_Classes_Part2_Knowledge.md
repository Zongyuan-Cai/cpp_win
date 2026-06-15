# 第9章：类的深入探索（下）— 知识点

## 9.12 const（常量）对象和 const 成员函数

### const 对象
- 关键字 `const` 指定一个对象**不可修改**
- `const Time noon(12, 0, 0);` — 任何修改尝试 → 编译错误
- 只有 **const 成员函数**可以被 const 对象调用

### const 成员函数
- 在**原型**和**定义**中都要用 `const` 声明：
```cpp
void printUniversal() const;
void Time::printUniversal() const { ... }
```
- const 成员函数**不允许**修改对象
- 非 const 成员函数**不能**从 const 成员函数中调用
- **构造函数和析构函数不允许使用 const**（它们负责初始化和终止）

### 兼容性表：
| 对象 | 成员函数 | 允许/错误 |
|--------|----------------|----------|
| const | const | ✓ |
| const | 非 const | ✗ |
| 非 const | const | ✓ |
| 非 const | 非 const | ✓ |

### 成员初始化器语法
- 数据成员名后跟包含初始值的括号：
```cpp
class Test {
public:
    Test() : x(0) { y = 0; }
    Test(int a, int b) : x(a) { y = b; }
private:
    int x, y;
};
```
- 任何数据成员都可以使用成员初始化器语法初始化

### 必须使用成员初始化器的情况（必须使用，不能赋值）：
1. **const 数据成员** — 初始化后不能赋值
2. **引用数据成员** — 必须在初始化时绑定
3. **成员对象** — 调用其构造函数
4. **基类** — 调用基类构造函数（第11章）

### 成员初始化器列表
- 多个初始化器用逗号分隔：
```cpp
ClassName::ClassName(...) : m_1(v_1), m_2(v_2), ... {
    // 函数体
}
```
- 在构造函数体**之前**执行
- 成员按照类定义中**声明的顺序**初始化，而**不是**初始化器列表中的顺序

### 示例：Increment 类（图 9.16-3~9.16-5）
- `const int increment;` — 必须使用成员初始化器
- `int &refCount;` — 必须使用成员初始化器
- 必需的初始化器列表：`Increment(int c, int i) : count(c), increment(i), refCount(count) {}`

## 9.13 组合：对象作为类的成员

### 定义
- 一个类可以将其他类的对象作为成员 → **has-a** 关系
- "组合"有时被称为 has-a 关系
- 示例：一个 `AlarmClock` 包含一个 `Time` 对象

### 格式：
```cpp
class ClassName {
    ClassName_1 member_1;
    // ...
    ClassName_n member_n;
};
```

### 术语：
- **宿主对象** — 包含其他对象的类
- **成员对象**（被包含的对象） — 作为另一个类对象的成员

### 初始化成员对象：
- 使用**成员初始化器**将参数从宿主构造函数传递给成员对象的构造函数
- 如果没有提供成员初始化器 → 成员对象的**默认构造函数**被隐式调用

### 成员对象的构造/析构顺序：
- **构造函数**：成员对象先于宿主对象
  - 成员对象按类中**声明**的顺序构造（不是初始化器列表中的顺序）
  - 然后宿主对象构造函数体执行
- **析构函数**：宿主对象先于成员对象（逆序）
  - `manager` → `hireDate` → `birthDate`

### 示例：Employee 类（图 9.17~9.21）
- `Employee` 包含 `const Date birthDate` 和 `const Date hireDate`
- 使用成员初始化器：`Employee(...) : birthDate(dateOfBirth), hireDate(dateOfHire) { ... }`
- 输出显示：`birth` 构造函数 → `hire` 构造函数 → birthDate 复制构造函数 → hireDate 复制构造函数 → manager 构造函数 → ... → manager 析构函数 → hireDate 析构函数 → birthDate 析构函数 → hire 析构函数 → birth 析构函数

## 9.14 friend 函数和 friend 类

### friend 函数
- 一个**普通函数**（不是成员函数），在类定义中用关键字 `friend` 声明
- 在**类作用域外**定义
- 有权访问该类的**非公有**（及公有）成员
- 可以提高性能
- 当成员函数不适用时通常很合适

### 声明：
```cpp
class X {
    friend T f(...); // friend 声明（可以在类中任何位置，通常在开头）
};
T f(...) { ... }  // 在类外定义，不带 friend 关键字
```

### 性质：
- **友元关系是被授予的，不是索取的** — B 要成为 A 的友元，A 必须显式声明
- **不对称**：B 是 A 的友元 ⇏ A 是 B 的友元
- **不传递**：A 是 B 的友元，B 是 C 的友元 ⇏ A 是 C 的友元

### Friend 类：
- 友元类的所有成员函数可以访问授予友元关系的类的所有成员
```cpp
class A { ... };
class B {
    friend class A;  // B 授予 A 友元关系
    ...
};
// 现在 A 的所有成员可以访问 B 的任何成员
```

### 一个类的成员函数作为另一个类的友元：
- A 类的成员函数可以声明为 B 类的友元
- 友元函数所属的类必须先定义

## 9.15 使用 this 指针
- （*目录中提到但本节简要涉及 — `this` 在成员函数和运算符重载中隐式使用；详见第10章*）

## 9.16 使用 new 和 delete 运算符进行动态内存管理

### new 运算符
- 在**运行时**从**堆**（自由存储区）动态分配精确大小的内存
- 语法：
  - `ptr = new Type;` — 分配一个对象
  - `ptr = new Type(x);` — 分配并初始化
  - `ptr = new Type[n];` — 分配 n 个对象的数组

### delete 运算符
- 将内存归还给堆，供后续 `new` 操作重用
- 语法：
  - `delete ptr;` — 释放单个对象
  - `delete[] ptr;` — 释放数组

### 对于基本类型：
```cpp
double *ptr = new double;  // 分配
cout << *ptr << endl;
delete ptr;                // 释放
```

### 对于类对象：
- **new**：分配存储空间 → 调用构造函数 → 返回指定类型的指针
- **delete**：调用析构函数 → 释放内存

## 9.17 static 类成员

### static 数据成员
- 只有**一个副本**，被类的**所有对象**共享（"类范围"信息）
- 存储在内存的**数据区**（编译时分配，而非对象定义时分配）
- 看起来像全局变量，但具有**类作用域**
- 可以声明为 `public`、`private` 或 `protected`

### static 数据成员的定义和初始化：
```cpp
class Employee {
    static const int a = 0;   // const static int：可在类内定义+初始化
    static int count;         // 仅声明
};
// 在类外定义（在 .cpp 文件中）：
int Employee::count = 0;     // 定义 + 初始化
```

### 隐式初始化：
- 基本类型的 static 数据成员默认为 **0**
  - `int Employee::count;` // 默认初始化为 0
- 类类型的 static 成员：调用默认构造函数

### 访问公有 static 成员：
- 通过类名 + 作用域解析：`Student::count`（当没有对象存在时）
- 通过任何对象：`student_1.count`

### static 成员函数
- 只能访问 **static 数据成员**和 **static 成员函数**
- 是**类**的服务，不是特定对象的服务
- **没有** `this` 指针
- 可以在类内或类外定义
- 不能声明为 `const`

### 兼容性表：
| 调用者类型 | 访问目标 | 允许/错误 |
|-------------|--------------|----------|
| static 成员函数 | static 成员 | ✓ |
| static 成员函数 | 非 static 成员 | ✗ |
| 非 static 成员函数 | static 成员 | ✓ |
| 非 static 成员函数 | 非 static 成员 | ✓ |

### 调用：
```cpp
int a = X::stcF();     // OK（不需要对象）
int b = X::memF();     // 错误（非 static 需要对象）
```

## 9.18 数据抽象与信息隐藏
- （*贯穿多个章节 — 封装、public/private 访问控制的总体主题*）

---

## 第二部分小结：
1. const 对象和 const 成员函数
2. 成员初始化器语法/列表（const、引用、成员对象必须使用）
3. 对象组合（has-a 关系）
4. friend 函数和 friend 类
5. this 指针
6. 动态内存分配（`new`/`delete`）
7. static 类成员（数据 + 函数）
