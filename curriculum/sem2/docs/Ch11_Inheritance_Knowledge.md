# Chapter 11: Object-Oriented Programming: Inheritance — Knowledge Points

## 11.1 Introduction
- **Inheritance**: Create a new class from an existing class
  - Absorb data and behaviors of existing class(es)
  - Enhance with new capabilities
- Base (parent) class → Derived (son) class

## 11.2 Base Classes and Derived Classes

### Relationship types:
- **is-a** relation (Inheritance): Square is a rectangle; Teacher is a person
- **has-a** relation (Composition): covered in Ch9 Part2

### Key terminology:
- **Base class** / **Derived class**
- **Direct** / **Indirect** base class
- **Single** / **Multiple** inheritance

### Three kinds of inheritance:
- `public` inheritance
- `protected` inheritance
- `private` inheritance (also the default for `class`)

### Inheritance hierarchy (examples):
| Base class | Derived classes |
|------------|----------------|
| Student | GraduateStudent, UndergraduateStudent |
| Shape | Circle, Triangle, Rectangle, Sphere, Cube |
| Loan | CarLoan, HomeImprovementLoan, MortgageLoan |
| Employee | Faculty, Staff |
| Account | CheckingAccount, SavingsAccount |

### Member composition of derived class:
- **Inherited members**: All members of base class **except** constructors, destructors, and friend functions
- **New additional members**: Including derived class's own constructor and destructor

### Inheritance Syntax:
```cpp
class DerivedClass : public BaseClass {
    // new additional members
};
```

### Redefining base class members in derived class:
- Base class members can be redefined with same name → base class members are **hidden** in derived class
- Hidden base class members can be accessed via: `BaseClassName::MemberName`
- Redefinable members: data members (same name), member functions (same name + return type; params may differ)

### Three kinds of inheritance:

#### (1) Public Inheritance: `class B : public A`
All inherited members maintain their original access authority:

| Base class access | In derived class | Outside derived class |
|------------------|------------------|----------------------|
| public | public | accessible |
| protected | protected | inaccessible |
| private | private | inaccessible |

- private members of base class **cannot** be directly accessed by new members of derived class
- protected members **can** be accessed within derived class
- public members can be accessed both in and outside derived class

#### (2) Private Inheritance: `class B : private A` (or `class B : A`)
Public and protected members of base class become **private** in derived class:

| Base class access | In derived class | Outside derived class |
|------------------|------------------|----------------------|
| public | private | inaccessible |
| protected | private | inaccessible |
| private | private | inaccessible |

- protected members can be accessed within derived class
- public members become private; can be accessed within derived class but NOT outside

#### (3) Protected Inheritance: `class B : protected A`
Public and protected members of base class become **protected** in derived class:

| Base class access | In derived class | Outside derived class |
|------------------|------------------|----------------------|
| public | protected | inaccessible |
| protected | protected | inaccessible |
| private | private | inaccessible |

- Both public and protected become protected in derived class
- Both can be accessed within derived class

## 11.3 protected Members
- A base class's `protected` members can be accessed by:
  - Members and friends of the base class itself
  - Members and friends of any classes **derived** from it

### Pros and Cons of using protected data:

**Advantages:**
- Derived class can modify values directly
- Slight increase in performance (no getter/setter overhead)

**Disadvantages:**
- No validity checking — derived class can assign illegal values
- Implementation dependent — base class changes may require derived class modifications
- Leads to **fragile (brittle) software**

**Better approach**: Use `private` data members + `public` function interfaces

## 11.4 Relationship between Base Classes and Derived Classes

### Case study: CommissionEmployee inheritance hierarchy

### 11.4.1 CommissionEmployee class (Fig. 11.4~11.6):
- Data: firstName, lastName, socialSecurityNumber, commissionRate, grossSales
- Standalone class, no inheritance

### 11.4.2 BasePlusCommissionEmployee WITHOUT inheritance (Fig. 11.7~11.9):
- Duplicates all CommissionEmployee members plus baseSalary
- Code duplication problem

### 11.4.3 WITH inheritance (Fig. 11.10~11.12):
- `BasePlusCommissionEmployee` **derives from** `CommissionEmployee`
- **Inherits** all members (except constructor and destructor)
- Constructor uses **base class initializer syntax**:
```cpp
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &ssn,
    double sales, double rate, double salary)
    : CommissionEmployee(first, last, ssn, sales, rate)  // base class initializer
{
    setBaseSalary(salary);  // new member
}
```

### 11.4.4 Using protected data (Fig. 11.12~11.13):
- Base class data members changed to `protected`
- Derived class can directly access them (no getters needed)

### 11.4.5 Using private data (Fig. 11.14~11.15):
- Best practice: keep data `private`, use public getter functions
- More robust and maintainable

## 11.5 Constructors and Destructors in Derived Classes

### Key rule:
- Derived class does **NOT inherit** base class's constructors and destructors
- But derived class **can invoke** them

### Constructor Invoking Order:
For `B b;` (B derived from A):
1. Base class A's constructor executes first
2. Then derived class B's constructor body executes

For multi-level inheritance `C` derived from `B` derived from `A`:
1. A's constructor
2. B's constructor
3. C's constructor body

### Two ways to invoke base class constructor:
1. **Implicitly** — calls base class **default** constructor
2. **Explicitly** — via **base class member initializer**: `Derived(...) : Base(...) { ... }`

### Destructor Invoking Order:
For `C c;` (C derived from B derived from A):
1. C's destructor
2. B's destructor
3. A's destructor
**Reverse order of constructors!**

### When composition is combined with inheritance:
Constructor order: Base → Member objects → Derived body
Destructor order: Derived → Member objects → Base (reverse)

## 11.6 public, protected and private Inheritance (already covered in 11.2)

## 11.7 Software Engineering with Inheritance
- Inheritance promotes software reuse
- ISV (Independent Software Vendor) can provide base classes
- Customize existing software through inheritance without modifying original code

---

## Summary:
1. Base class and Derived class definitions
2. protected member access specifier
3. Relations between base and derived classes (public/protected/private inheritance)
4. Constructors and Destructors in Derived Classes
   - Constructor: base first, then derived
   - Destructor: derived first, then base (reverse order)
5. Base class member initializer syntax
