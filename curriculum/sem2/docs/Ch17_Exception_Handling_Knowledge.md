# 第17章：异常处理 — 知识点

## 17.1 引言
- **错误**（Error）：
  - 编译错误
  - 运行时错误（包括逻辑错误）
- **异常**（Exception）：不寻常但**可预测**的事件
- **异常处理**（Exception Handling）：
  - 将错误处理代码与程序执行的"主线"分离
  - 使程序更**健壮**（Robust）和**容错**（Fault-tolerant）

## 17.2 C++ 异常处理基础：try、throw、catch

### 三个关键字
| 关键字 | 作用 | 位置要求 |
|--------|------|---------|
| `throw` | **抛出**异常 | 抛出点必须在可能出错代码之前 |
| `try` | **检测**异常 | 每个 try 块后必须紧跟至少一个 catch 处理器 |
| `catch` | **处理**异常 | 紧跟在 try 块之后 |

### 基本结构
```cpp
try {
    // 可能抛出异常的代码
    throw ExceptionTypeA();
    // ...
    throw ExceptionTypeB();
}
catch (ExceptionTypeA &) {
    // 处理 ExceptionTypeA
}
catch (ExceptionTypeB &) {
    // 处理 ExceptionTypeB
}
catch (...) {
    // 处理所有其他异常
}
```

### 异常类
- **标准库异常类**：如 `<exception>`、`<stdexcept>` 中的类
- **用户自定义异常类**：程序员自行定义

### 异常参数
- 语法：`catch (<exception-type> <parameter>)`
- 参数可以是值、引用或指针

### 多异常处理
- 一个 try 块可以抛出多种异常类型
- `catch(...)` 可以捕获任何类型的异常

## 17.3 标准库异常层次结构

```
<exception>
├── <stdexcept> 中的各种标准异常类
│   ├── runtime_error
│   ├── logic_error
│   └── ...
```
- 所有标准异常类都有 `what()` 虚函数，返回描述信息

## 17.4 异常与继承

### 异常类的继承
- 新异常类可以从现有异常类**继承**而来
- 基类异常的 catch 处理器**也能**捕获派生类异常
- 允许对相关错误进行**多态处理**

### 示例
```cpp
bool flag = true;
try {
    if (flag)
        throw runtime_error("runtime error");
    else
        throw logic_error("logic error");
}
catch (exception &e) {
    cout << e.what() << endl;  // 多态：what() 是虚函数
}
```

## 17.5 示例：处理除零异常

### 步骤一：抛出异常（throw）
```cpp
#include <stdexcept>
using std::runtime_error;

class DivideByZeroException : public runtime_error {
public:
    DivideByZeroException()
        : runtime_error("attempted to divide by zero") {}
};

double quotient(int numerator, int denominator) {
    if (denominator == 0)
        throw DivideByZeroException();  // 抛出异常对象
    return static_cast<double>(numerator) / denominator;
}
```

### 步骤二：检测异常（try）
```cpp
int main() {
    int number1, number2; double result;
    cout << "Enter 2 integers (end-of-file to end): ";
    while (cin >> number1 >> number2) {
        try {  // try 块应包含可能出错的语句
            result = quotient(number1, number2);
            cout << "The quotient is: " << result << endl;
        }  // try 块结束，以下是 catch
        cout << "Enter 2 integers (end-of-file to end): ";
    }
    return 0;
}
```

### 步骤三：处理异常（catch）
```cpp
        catch (DivideByZeroException &divideByZeroException) {
            cout << "Exception occurred: "
                 << divideByZeroException.what() << endl;
        }
```

- `what()` 是基类 `exception` 中的**虚函数**，返回异常信息字符串

### 运行结果
```
Enter two integers (end-of-file to end): 100 7
The quotient is: 14.2857
Enter two integers (end-of-file to end): 100 0
Exception occurred: attempted to divide by zero
Enter two integers (end-of-file to end): ^Z
```

## 17.6 重新抛出异常

### 语法
```cpp
throw;  // 不带参数，重新抛出当前异常
```

### 用途
- 当 catch 处理器**不能**或只能**部分**处理异常时
- 下一个外层 try 块尝试匹配该异常

### 示例（图 17.3）
```cpp
void throwException() {
    try {
        cout << "Function throwException throws an exception\n";
        throw exception();
    }
    catch (exception &) {
        cout << "Exception handled in function throwException\n";
        cout << "Function throwException rethrows exception";
        throw;  // 重新抛出
    }
    cout << "This also should not print\n";  // 被跳过
}

int main() {
    try {
        cout << "main invokes function throwException\n";
        throwException();
        cout << "This should not print\n";  // 被跳过
    }
    catch (exception &) {
        cout << "\n\nException handled in main\n";
    }
    cout << "Program control continues after catch in main\n";
    return 0;
}
```

## 17.7 异常规格说明

### 语法
```cpp
int someFunction(double value)
    throw(ExceptionA, ExceptionB, ExceptionC)
{
    // ...
}
```
- 枚举函数**可以**抛出的异常类型列表（包括派生类型）

### 规则
| 规格说明 | 含义 |
|---------|------|
| 无规格说明（`void func() {...}`） | 可以抛出**任何**异常 |
| 空规格说明（`void func() throw() {...}`） | **不能**抛出任何异常 |
| `void func() throw(A, B) {...}` | 只能抛出 A、B 及它们的派生类型 |

- 如果函数抛出非规格说明中的异常 → 调用 `unexpected()`
- `unexpected()` 通常调用 `terminate()` 结束程序

## 17.8 处理意外异常

```
抛出非规格说明异常          异常未被捕获
     ↓                        ↓
unexpected()              terminate()
     ↓                        ↓
terminate()          abort() / set_terminate()
```
- 都定义在 `<exception>` 中
- 可通过 `set_unexpected()` / `set_terminate()` 自定义处理函数

## 17.9 栈展开

### 概念
- 当抛出的异常在**当前作用域未被捕获**时发生
- 尝试在**外层** try...catch 块中捕获异常

### 终止模型（Termination Model）
1. 抛出异常的函数被**终止**
2. 在外层作用域搜索 try 块和匹配的 catch 处理器
3. 找到匹配的 catch → 执行处理器，然后继续执行 catch 块后的第一条语句
4. 未找到 → 继续向更外层展开

### 示例（图 17.4）
```
main() → function1() → function2() → function3()
                                      throw runtime_error(...)
                                      异常未被 function3 捕获
                                      → 终止 function3()
                                      → 终止 function2()
                                      → 终止 function1()
                                      → main 中的 catch 捕获
```

## 17.10 构造函数、析构函数与异常处理

### 异常与构造函数
- 异常导致对象**部分构造**
- 已构造的**自动对象**的析构函数会被调用
- 如果对象包含**成员对象**，已构造的成员对象的析构函数会被调用
- 如果**对象数组**部分构造，只有已构造对象的析构函数会被调用

### 异常与析构函数
- 如果栈展开调用的析构函数**抛出异常** → 调用 `terminate()`
- **通常析构函数不应抛出异常**

## 17.11 处理 new 失败

### 三种情况
| 方式 | 行为 | 符合标准 |
|------|------|---------|
| 返回 `0`（空指针） | 旧式编译器行为 | 否 |
| 抛出 `bad_alloc` 异常 | 标准行为（包含 `<new>` 时） | 是 |
| `set_new_handler` | 注册自定义处理函数 | 是 |

### 方式一：检查 new 返回 0（旧式）
```cpp
double *ptr = new double[50000000];
if (ptr == 0) {
    cerr << "Memory allocation failed\n";
    break;
}
```

### 方式二：捕获 bad_alloc 异常（标准）
```cpp
#include <new>
using std::bad_alloc;

try {
    double *ptr = new double[50000000];
}
catch (bad_alloc &memoryAllocationException) {
    cerr << "Exception occurred: "
         << memoryAllocationException.what() << endl;
}
```

### 方式三：set_new_handler
```cpp
#include <new>
using std::set_new_handler;

void customNewHandler() {
    cerr << "customNewHandler was called";
    abort();  // 或：释放一些内存让 new 重试
}

int main() {
    set_new_handler(customNewHandler);
    // 此后 new 失败时会调用 customNewHandler
    double *ptr = new double[50000000];
    return 0;
}
```
- `set_new_handler` 接受一个无参无返回值的函数指针
- new-handler 函数应该：释放内存让 new 重试、抛出 bad_alloc 或终止程序

---

## 小结：
1. 错误 vs. 异常，异常处理使程序更健壮
2. try（检测）、throw（抛出）、catch（处理）三关键字
3. 异常类：标准库类 + 用户自定义类
4. 继承在异常中的应用 — 基类 catch 可捕获派生类异常
5. 除零异常案例研究 — DivideByZeroException 继承 runtime_error
6. 重新抛出异常：`throw;`（不带参数）
7. 异常规格说明：`throw(A, B)`、`throw()`（不抛任何异常）
8. 意外异常 → `unexpected()` → `terminate()`
9. 栈展开 — 搜索外层 try...catch 块
10. 构造函数/析构函数中的异常 — 部分构造对象、析构函数不应抛异常
11. new 失败处理：返回 0（旧式）→ bad_alloc 异常（标准）→ set_new_handler（自定义）
12. `what()` 虚函数返回异常描述
