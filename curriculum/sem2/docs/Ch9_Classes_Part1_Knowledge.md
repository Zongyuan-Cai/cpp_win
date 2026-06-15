# Chapter 9: Classes — A Deeper Look (Part I) — Knowledge Points

## 9.1 Introduction
- Integrated Time class case study (3 versions, each adding new features)
- Preprocessor wrapper — prevent multiple definition errors
- Two ways to define member functions (inside or outside class)
- class handles (object name / reference / pointer)
- Two kinds of member functions: predicate function & utility function

## 9.2 Time Class Case Study

### Preprocessors
- `#define` — define macro (e.g. `#define PI 3.1415926`)
- `#include` — include header file
- Conditional compilation directives:
  - `#ifdef FLAG` ... `#endif`
  - `#ifndef FLAG` ... `#endif`
  - `#define FLAG`
  - `#undef FLAG`
  - `#else`

### Preprocessor Wrappers (Header Guard)
- Used to prevent multiple-definition (compilation) errors when a header is included more than once.
- **Problem**: If `A.h` defines `class A{}` and `B.h` includes `A.h`, then a `.cpp` including both `A.h` and `B.h` gets `class A` defined twice → compilation error C2011.
- **Solution**:
```cpp
#ifndef FLAG
#define FLAG
// ... class definition ...
#endif
```

### 1st Time Class (Fig. 9.1~9.3)
- Basic class with `Time()` default constructor, `setTime()`, `printUniversal()`, `printStandard()`
- Data members: `hour`, `minute`, `second` (private)
- Member functions can be defined in two ways:
  1. Inside class definition (inline implicitly)
  2. Outside class definition (using `ClassName::functionName`), can use `inline` keyword

### Header file structure (Time.h):
```cpp
#ifndef TIME_H
#define TIME_H
class Time {
public:
    Time(); // default constructor
    void setTime(int, int, int);
    void printUniversal();
    void printStandard();
private:
    int hour;   // 0-23
    int minute; // 0-59
    int second; // 0-59
};
#endif
```

### Using class handles to access members:
- By object name: `Time sunset;`
- By reference: `Time &dinnerTime = sunset;`
- By pointer: `Time *timeptr = &sunset;`

### Implementation (Time.cpp):
- `setTime()` validates hour (0-23), minute (0-59), second (0-59), sets to 0 if invalid
- `printUniversal()` outputs `HH:MM:SS` using `setfill('0')` and `setw(2)`
- `printStandard()` outputs 12-hour format with AM/PM

### Rules:
- Member function must be declared in class definition
- Cannot explicitly initialize non-static data members in class definition (compilation error)

## 9.3 Class Scope and Accessing Class Members

### Scope categories (review from §6.10):
- Function Scope, File Scope, Block Scope (Local Scope), Function-prototype Scope, Class Scope

### Class Scope contains:
- Data members (variables declared in class definition)
- Member functions (declared in class definition, including those defined outside)
- Any member function has unlimited authority to access any data member in class scope

### Access rules:
- **Within class scope**: class members can be directly accessed by all member functions
- **Outside class scope**: public members are accessed via handles:
  - Object name + dot: `obj.member`
  - Reference + dot: `ref.member`
  - Pointer + arrow: `ptr->member`
- Member functions can be overloaded (only by other member functions of same class)
- Variables in member functions have block scope (known only to that function)
- Non-member functions are at file scope
- **Hiding**: a block-scope variable hides a class-scope variable of same name;
  use `ClassName::var` to access the hidden class member; use `::var` for global variable

### Two member selection operators:
| Operator | Used with | Example |
|----------|-----------|---------|
| `.` (dot) | object name or reference | `counter.setX(1);` `counterRef.print();` |
| `->` (arrow) | pointer to object | `counterPtr->setX(4);` |

Four ways to access: `counter.setX(1)`, `counterRef.setX(2)`, `(*counterPtr).setX(3)`, `counterPtr->setX(4)`.

## 9.4 Separating Interface from Implementation
- Interface: class definition in header `.h` file (function prototypes)
- Implementation: member function definitions in `.cpp` file
- Client code only needs to know the interface, not the implementation

## 9.5 Access Functions and Utility Functions

### Access Functions (public)
- Can read or display data
- Can test truth/falsity of conditions → **predicate functions**
- Examples: `isEmpty()`, `isFull()` — used before accessing objects from container classes (Vector, Linked list, Stack, Queue, ...)
- E.g. `vector<int> v; v.empty(); // returns true if empty`

### Utility Functions (Helper functions, private)
- `private` member functions
- Support public member functions
- Not part of public interface, not intended for client use

Example: `SalesPerson` class — `totalAnnualSales()` is a private utility function called by public `printAnnualSales()`. The `sales[]` array manipulation is completely encapsulated inside member functions.

## 9.6 Constructors with Default Arguments (2nd Time Class, Fig. 9.4~9.6)

### Default arguments rules:
- Must be specified at the **first occurrence** of the function name:
  - For global functions: in declaration or in header of definition
  - For class member functions: in declaration (prototype) or in inline function definition header

### Constructor:
- A special member function to initialize data members of an object
- Characteristics:
  - Same name as class
  - Invoked **implicitly** by compiler
  - Usually `public`
  - With or without parameters
  - **No return type** (not even `void`), no return value
  - Can have multiple constructors (overloaded)

### Default Constructor:
- Takes no arguments, OR defaults all its arguments
- Two ways to provide:
  1. Compiler implicitly creates one if no constructors defined: `className::className() {}`
  2. Programmer explicitly defines parameterless constructor
- **Maximum of one default constructor per class**

### Overloaded Constructor:
```cpp
class A {
    int x, y;
public:
    A() { x = y = 0; }
    A(int a) { x = a; y = 0; }
    A(int a, int b) { x = a; y = b; }
};
```

### Constructor with default arguments (better approach):
```cpp
Time(int = 0, int = 0, int = 0); // replaces the 3 overloaded constructors
// Time t1;         // all defaulted
// Time t2(2);       // hour=2, others defaulted
// Time t3(21, 34);  // hour+minute, second defaulted
// Time t4(12, 25, 42); // all specified
```

### Important notices:
- Constructor is invoked implicitly when object is **defined**
- Once an explicit constructor exists, compiler does **NOT** create a default constructor
- Constructor must be invoked when object is defined → must be unique

### 2nd Time Class additions (Fig. 9.4~9.5):
- set/get functions: `setHour()`, `setMinute()`, `setSecond()`, `getHour()`, `getMinute()`, `getSecond()`
- `setTime()` calls the three individual set functions
- Constructor calls `setTime()` for validation

## 9.7 Destructors

### Definition:
```cpp
class A { ... ~A(...) { ... } ... };
// Or:
ClassName::~ClassName() { ... }
```
- Name: `~` + ClassName
- Invoked **implicitly** by compiler
- Usually `public`
- **No parameters**
- **No return type**, no return value
- **Cannot be overloaded** (one destructor per class)

### Purpose:
- Called implicitly when an object is destroyed (execution leaves the object's scope)
- Does **NOT** actually release memory — system reclaims memory afterward
- Performs "**termination housekeeping**" (cleanup work)
- If programmer doesn't define one, compiler creates a default: `className::~className(){}`

## 9.8 When Constructors and Destructors Are Called

### General rule:
- Destructor calls are in the **reverse order** of corresponding constructor calls
- Storage class of objects can alter the order

### Memory layout (RAM):
| Region | Contents |
|--------|----------|
| Heap | Allocated by `new` |
| Stack | Local variables, arguments, return value, return address |
| Data | Global/static global/static local variables, constants |
| Code | Code of member/normal functions |

### Three categories of objects (by storage class):

| Type | Constructor called | Destructor called |
|------|-------------------|-------------------|
| **Global object** (defined outside any function) | Before `main()` begins execution | When `main` terminates or `exit()` is called; NOT with `abort()` |
| **Local object** (defined in function/class) | When object is defined | When execution leaves object scope `{...}`; NOT called if `exit()`/`abort()` |
| **Static local object** | **Only once**, when execution first reaches definition | When `main` terminates or `exit()`; NOT with `abort()` |

### Additional rules:
- Global and static objects destroyed in **reverse order of definition**
- Local object constructors and destructors called **each time** execution enters/leaves scope

## 9.9 A Subtle Trap — Returning a Reference to a Private Data Member

- A reference is an **alias** of a variable; an acceptable **lvalue** (left side of assignment)
- If a function returns a reference, that reference can be used as a modifiable lvalue
- **Danger**: A public member function returning a reference to a private data member allows client code to alter private data → **breaks encapsulation** (serious logic error)

## 9.10 Default Memberwise Assignment

### Assignment operator (`=`)
- Can assign one object to another object of same class
- Each data member of right object is copied to the corresponding data member of left object
- **Copies data members, not member functions**
- Can cause serious problems when data members contain **pointers** to dynamically allocated memory

### Copy Constructor:
- Initializes a **new** object with an **existing** object of the same class
- Copies each member (memberwise assignment)
- Two syntax forms:
```cpp
Date date2(date1);   // form 1
Date date2 = date1;  // form 2
Date date2 = date1, date3 = date2;  // chained
```

### Default Copy Constructor:
- If not defined, compiler provides one: `ClassName::ClassName(const ClassName&) {}`
- This does **shallow copy** — problematic with pointer members

### User-defined Copy Constructor:
```cpp
ClassName::ClassName(ClassName &objectName) {
    // data members assignment
}
```

### When copy constructor is invoked:
1. A new object is initialized by an existing object of the same class
2. Objects are **passed by value** (as function argument or return value)

### Important:
- Copy constructor must receive its argument by **(const) reference**, not by value
- Passing by value would cause **infinite recursion** (fatal logic error)

## 9.11 Software Reusability
- Well-designed classes can be reused in multiple programs

---

## Summary of Part I:
1. Preprocessor wrappers (`#ifndef`/`#define`/`#endif`)
2. Class scope — three ways to access members (handle: `.` / `->`)
3. Access functions & Utility functions
4. Constructor with default arguments
5. Order of constructor & destructor calls
6. Destructor encapsulation — returning reference to private data member
7. Default memberwise assignment (assignment operator + copy constructor)
