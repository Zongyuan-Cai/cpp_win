# 第12章：面向对象编程：多态 — 知识点

## 12.1 引言
- **多态**（Polymorphism）：同一继承层次结构中的不同对象对同一消息做出不同响应
- 通过**基类指针或引用**处理派生类对象，使程序更易扩展
- 核心机制：**虚函数**（Virtual Function）+ **函数重写**（Function Overridden）

## 12.3 继承层次结构中对象间的关系

### 12.3.1 从派生类对象调用基类函数
- 基类和派生类可以有**同名函数**
- 通过对象名调用时，调用该对象所属类的版本
- 图 12.1：基类 `CommissionEmployee::print()` 和派生类 `BasePlusCommissionEmployee::print()`

### 12.3.2 将派生类指针指向基类对象
- 将派生类指针指向基类对象 → **编译错误**
- 基类对象不是派生类对象（基类对象缺少派生类新增成员）
- 图 12.2

### 12.3.3 通过基类指针调用派生类成员函数
- 基类指针指向派生类对象时，**正常情况**下调用基类版本
- 调用的是**句柄类型**决定的功能，而非对象类型
- 调用仅存在于派生类中的函数 → **编译错误**
- **向下转型**（Downcasting）可解决此问题：
```cpp
BasePlusCommissionEmployee *derivedPtr =
    dynamic_cast<BasePlusCommissionEmployee *>(commissionEmployeePtr);
derivedPtr->setBaseSalary(500);
```

### 12.3.4 虚函数

#### 基本概念
- **没有 virtual**：句柄的类型决定调用哪个版本（静态绑定）
- **有 virtual**：**对象**的类型（而非句柄的类型）决定调用哪个版本的虚函数

#### 虚函数声明与重写
```cpp
class Animal {
public:
    virtual void move() const;
};

class Bird : public Animal {
public:
    virtual void move() const;  // 重写（Override），virtual 关键字在定义中可省略
};
```

- 派生类中重写的虚函数必须具有**相同的签名和返回类型**
- 函数**定义**中不需要 `virtual` 关键字
- 示例：`Bird b; Animal *p = &b; p->move();` — 调用 `Bird::move()`

#### 动态绑定与静态绑定
| 绑定类型 | 时机 | 调用方式 |
|---------|------|---------|
| **静态绑定**（早期绑定） | 编译时 | 通过**对象名**和 `.` 运算符调用 |
| **动态绑定**（晚期绑定） | 运行时 | 通过**基类指针或引用**和 `->` / `.` 运算符调用 |

- 多态仅通过基类的**指针**和**引用**句柄发生
- 调用哪个成员函数取决于要处理的对象类型

#### 虚函数的限制
1. 虚函数必须是**成员函数**
2. 虚函数**不能**是 **static** 成员函数
3. 构造函数**不能**是虚函数
4. 析构函数**可以**是虚函数

#### 虚析构函数示例（图 12.4~12.6）
```cpp
class Base {
public:
    Base() { cout << "Base" << endl; p1 = new int(1); }
    virtual ~Base() { cout << "~Base" << endl; delete p1; }
private:
    int *p1;
};

class Derive : public Base {
public:
    Derive() { cout << "Derive" << endl; p2 = new int(2); }
    virtual ~Derive() { cout << "~Derive" << endl; delete p2; }
private:
    int *p2;
};

int main() {
    Base *pDerive = new Derive;
    delete pDerive;  // 输出：Base, Derive, ~Derive, ~Base
    return 0;
}
```
- 如果析构函数不是 virtual，`delete` 基类指针时**不会**调用派生类析构函数 → 内存泄漏

## 12.5 抽象类和纯虚函数

### 纯虚函数
- 在声明中放置 `= 0`：
```cpp
virtual void move() const = 0;
```
- 不在基类中提供实现

### 抽象类
- 声明了**一个或多个纯虚函数**的类
- **不能**实例化任何对象
- 但**可以**声明指针或引用
- 通常用作基类

```cpp
Animal obj;        // 错误！Animal 是抽象类
Bird objBird;      // OK，Bird 是具体类
Animal *ptr = &objBird;  // OK
Animal &ref = objBird;   // OK
```

### 具体类
- 不包含纯虚函数
- **可以**实例化对象
- 纯虚函数要求派生类重写该函数（派生类若不提供实现则仍为抽象类）

### 层次结构示例
- 抽象基类：`Shape`
  - 抽象类：`TwoDimensionalShape`、`ThreeDimensionalShape`
    - 具体类：`Circle`、`Rectangle`、`Square`、`Sphere`、`Cube`

### 结论
| 纯虚函数 | 效果 |
|---------|------|
| 提供实现 | 给派生类**选择**是否重写的权利 |
| 不提供实现（`= 0`） | **要求**派生类重写（否则派生类仍为抽象类） |

## 12.6 案例研究：使用多态的工资系统

### 设计
- **受薪员工**：姓名、SSN、周薪
- **佣金员工**：姓名、SSN、销售额、佣金率
- **底薪+佣金员工**：姓名、SSN、销售额、佣金率、底薪

### 12.6.1 抽象基类 Employee（图 12.9~12.10）
- 数据：`firstName`、`lastName`、`socialSecurityNumber`
- 纯虚函数：`earnings()`、`print()`
- 具体派生类**必须**重写这些纯虚函数

### 12.6.2 具体派生类 SalariedEmployee（图 12.11~12.12）
- 继承自 `Employee`
- 新增数据：`weeklySalary`
- 重写：`print()`、`earnings()`

### 12.6.3 具体派生类 CommissionEmployee（图 12.13~12.14）
- 继承自 `Employee`
- 新增数据：`grossSales`、`commissionRate`
- 重写：`print()`、`earnings()`

### 12.6.4 间接具体派生类 BasePlusCommissionEmployee（图 12.15~12.16）
- **直接**继承自 `CommissionEmployee`，**间接**继承自 `Employee`
- 新增数据：`baseSalary`
- 重写：`print()`（调用 `CommissionEmployee::print()`）、`earnings()`

### 12.6.6 演示多态处理（图 12.17）
- 创建四种类型的对象
- **静态绑定**：使用对象名调用 — 编译器确定类型
- **多态处理**：使用 `vector<Employee *>` 基类指针数组
  - 通过基类指针调用虚函数 → 动态绑定到正确的派生类版本

---

## 小结：
1. 多态概念 — 基类指针/引用 + 虚函数实现动态绑定
2. 虚函数声明（`virtual`）、重写（Override）、限制
3. 静态绑定（编译时）vs. 动态绑定（运行时）
4. 虚析构函数的重要性 — 防止内存泄漏
5. 纯虚函数（`= 0`）和抽象类 — 不能实例化
6. 向下转型（`dynamic_cast`）
7. 工资系统案例研究 — 抽象基类 Employee + 三层具体派生类
8. `vector<BaseClass*>` 实现多态处理
