# 第11章：面向对象编程：继承 — 知识点

## 11.1 引言
- **继承**：从现有类创建新类
  - 吸收现有类的数据和行为
  - 通过新功能增强
- 基（父）类 → 派生（子）类

## 11.2 基类和派生类

### 关系类型：
- **is-a** 关系（继承）：正方形是一种矩形；教师是一个人
- **has-a** 关系（组合）：见第9章下半部分

### 关键术语：
- **基类** / **派生类**
- **直接** / **间接**基类
- **单** / **多重**继承

### 三种继承方式：
- `public` 继承
- `protected` 继承
- `private` 继承（也是 `class` 的默认方式）

### 继承层次结构（示例）：
| 基类 | 派生类 |
|------------|----------------|
| Student | GraduateStudent, UndergraduateStudent |
| Shape | Circle, Triangle, Rectangle, Sphere, Cube |
| Loan | CarLoan, HomeImprovementLoan, MortgageLoan |
| Employee | Faculty, Staff |
| Account | CheckingAccount, SavingsAccount |

### 派生类的成员组成：
- **继承的成员**：基类的所有成员，**除了**构造函数、析构函数和友元函数
- **新增成员**：包括派生类自己的构造函数和析构函数

### 继承语法：
```cpp
class DerivedClass : public BaseClass {
    // 新增成员
};
```

### 在派生类中重定义基类成员：
- 基类成员可以用相同名称重定义 → 基类成员在派生类中被**隐藏**
- 被隐藏的基类成员可以通过以下方式访问：`BaseClassName::MemberName`
- 可重定义的成员：数据成员（同名）、成员函数（同名 + 返回类型；参数可以不同）

### 三种继承方式：

#### （1）公有继承：`class B : public A`
所有继承的成员保持其原始访问权限：

| 基类访问权限 | 派生类中 | 派生类外 |
|------------------|------------------|----------------------|
| public | public | 可访问 |
| protected | protected | 不可访问 |
| private | private | 不可访问 |

- 基类的 private 成员**不能**被派生类的新成员直接访问
- protected 成员**可以**在派生类内访问
- public 成员可以在派生类内外访问

#### （2）私有继承：`class B : private A`（或 `class B : A`）
基类的公有和受保护成员在派生类中变为 **private**：

| 基类访问权限 | 派生类中 | 派生类外 |
|------------------|------------------|----------------------|
| public | private | 不可访问 |
| protected | private | 不可访问 |
| private | private | 不可访问 |

- protected 成员可以在派生类内访问
- public 成员变为 private；可以在派生类内访问但**不能**在派生类外访问

#### （3）受保护继承：`class B : protected A`
基类的公有和受保护成员在派生类中变为 **protected**：

| 基类访问权限 | 派生类中 | 派生类外 |
|------------------|------------------|----------------------|
| public | protected | 不可访问 |
| protected | protected | 不可访问 |
| private | private | 不可访问 |

- public 和 protected 在派生类中都变为 protected
- 两者都可以在派生类内访问

## 11.3 protected 成员
- 基类的 `protected` 成员可以被以下访问：
  - 基类本身的成员和友元
  - 从该基类**派生**的任何类的成员和友元

### 使用 protected 数据的优缺点：

**优点：**
- 派生类可以直接修改值
- 性能略有提升（无 getter/setter 开销）

**缺点：**
- 无有效性检查 — 派生类可以赋非法值
- 依赖实现 — 基类变更可能需要修改派生类
- 导致**脆弱软件**

**更好的方法**：使用 `private` 数据成员 + `public` 函数接口

## 11.4 基类与派生类的关系

### 案例研究：CommissionEmployee 继承层次结构

### 11.4.1 CommissionEmployee 类（图 11.4~11.6）：
- 数据：firstName、lastName、socialSecurityNumber、commissionRate、grossSales
- 独立的类，无继承

### 11.4.2 不使用继承的 BasePlusCommissionEmployee（图 11.7~11.9）：
- 重复了 CommissionEmployee 的所有成员，外加 baseSalary
- 代码重复问题

### 11.4.3 使用继承（图 11.10~11.12）：
- `BasePlusCommissionEmployee` **派生自** `CommissionEmployee`
- **继承**所有成员（除了构造函数和析构函数）
- 构造函数使用**基类初始化器语法**：
```cpp
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &ssn,
    double sales, double rate, double salary)
    : CommissionEmployee(first, last, ssn, sales, rate)  // 基类初始化器
{
    setBaseSalary(salary);  // 新增成员
}
```

### 11.4.4 使用 protected 数据（图 11.12~11.13）：
- 基类数据成员改为 `protected`
- 派生类可以直接访问（不需要 getter）

### 11.4.5 使用 private 数据（图 11.14~11.15）：
- 最佳实践：保持数据 `private`，使用公有 getter 函数
- 更健壮和可维护

## 11.5 派生类中的构造函数和析构函数

### 关键规则：
- 派生类**不继承**基类的构造函数和析构函数
- 但派生类**可以调用**它们

### 构造函数调用顺序：
对于 `B b;`（B 派生自 A）：
1. 基类 A 的构造函数首先执行
2. 然后派生类 B 的构造函数体执行

对于多级继承，`C` 派生自 `B`，`B` 派生自 `A`：
1. A 的构造函数
2. B 的构造函数
3. C 的构造函数体

### 调用基类构造函数的两种方式：
1. **隐式** — 调用基类的**默认**构造函数
2. **显式** — 通过**基类成员初始化器**：`Derived(...) : Base(...) { ... }`

### 析构函数调用顺序：
对于 `C c;`（C 派生自 B，B 派生自 A）：
1. C 的析构函数
2. B 的析构函数
3. A 的析构函数
**与构造函数顺序相反！**

### 当组合与继承结合时：
构造函数顺序：基类 → 成员对象 → 派生类体
析构函数顺序：派生类 → 成员对象 → 基类（逆序）

## 11.6 public、protected 和 private 继承（已在 11.2 中介绍）

## 11.7 继承的软件工程
- 继承促进软件重用
- ISV（独立软件供应商）可以提供基类
- 通过继承自定义现有软件，无需修改原始代码

---

## 小结：
1. 基类和派生类的定义
2. protected 成员访问说明符
3. 基类和派生类之间的关系（public/protected/private 继承）
4. 派生类中的构造函数和析构函数
   - 构造函数：先基类，后派生类
   - 析构函数：先派生类，后基类（逆序）
5. 基类成员初始化器语法
