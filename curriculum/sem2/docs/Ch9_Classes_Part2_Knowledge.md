# Chapter 9: Classes — A Deeper Look (Part II) — Knowledge Points

## 9.12 const (Constant) Objects and const Member Functions

### const Object
- Keyword `const` specifies that an object is **not modifiable**
- `const Time noon(12, 0, 0);` — any modification attempt → compilation error
- Only **const member functions** can be called on const objects

### const Member Function
- Declared with `const` both in **prototype** and **definition**:
```cpp
void printUniversal() const;
void Time::printUniversal() const { ... }
```
- A const member function is **not allowed** to modify the object
- Non-const member functions **cannot** be called from const member functions
- **const is NOT allowed for constructors and destructors** (they handle initialization/termination)

### Compatibility table:
| Object | Member function | OK/Error |
|--------|----------------|----------|
| const | const | ✓ |
| const | non-const | ✗ |
| non-const | const | ✓ |
| non-const | non-const | ✓ |

### Member Initializer Syntax
- Data member name followed by parentheses containing initial value:
```cpp
class Test {
public:
    Test() : x(0) { y = 0; }
    Test(int a, int b) : x(a) { y = b; }
private:
    int x, y;
};
```
- Any data member can be initialized using member initializer syntax

### Required uses of member initializer (must use, not assignment):
1. **const data member** — cannot be assigned after initialization
2. **Reference data member** — must be bound at initialization
3. **Member object** — calls its constructor
4. **Base-class** — calls base class constructor (Chapter 11)

### Member Initializer List
- Multiple initializers separated by commas:
```cpp
ClassName::ClassName(...) : m_1(v_1), m_2(v_2), ... {
    // body
}
```
- Executes **before** the constructor body
- Members initialized in the **order they are declared** in the class definition, **NOT** the order in the initializer list

### Example: Increment class (Fig. 9.16-3~9.16-5)
- `const int increment;` — must use member initializer
- `int &refCount;` — must use member initializer
- Required initializer list: `Increment(int c, int i) : count(c), increment(i), refCount(count) {}`

## 9.13 Composition: Objects as Members of Classes

### Definition
- A class can have objects of other classes as members → **has-a** relationship
- "Composition" is sometimes called a has-a relationship
- Example: An `AlarmClock` has a `Time` object

### Format:
```cpp
class ClassName {
    ClassName_1 member_1;
    // ...
    ClassName_n member_n;
};
```

### Terminology:
- **Host object** — the containing class
- **Member object** (contained object) — the member that is an object of another class

### Initializing member objects:
- Use **member initializers** to pass arguments from host's constructor to member object's constructor
- If no member initializer provided → member object's **default constructor** is called implicitly

### Order of constructors/destructors for member objects:
- **Constructor**: Member objects precede host objects
  - Member objects constructed in the order they are **declared** in the class (not order in initializer list)
  - Then host object constructor body executes
- **Destructor**: Host objects precede member objects (reverse order)
  - `manager` → `hireDate` → `birthDate`

### Example: Employee class (Fig. 9.17~9.21)
- `Employee` contains `const Date birthDate` and `const Date hireDate`
- Uses member initializer: `Employee(...) : birthDate(dateOfBirth), hireDate(dateOfHire) { ... }`
- Output shows: `birth` constructor → `hire` constructor → birthDate copy constructor → hireDate copy constructor → manager constructor → ... → manager destructor → hireDate destructor → birthDate destructor → hire destructor → birth destructor

## 9.14 friend Functions and friend Classes

### friend Function
- An **ordinary function** (not member function) declared in class definition with keyword `friend`
- Defined **outside** class scope
- Has the right to access **non-public** (and public) members of that class
- Can enhance performance
- Often appropriate when a member function cannot be used

### Declaration:
```cpp
class X {
    friend T f(...); // friend declaration (can be anywhere in class, usually at front)
};
T f(...) { ... }  // definition outside class, without friend keyword
```

### Properties:
- **Friendship is granted, not taken** — for B to be a friend of A, A must explicitly declare it
- **NOT symmetric**: B friend of A ⇏ A friend of B
- **NOT transitive**: A friend of B, B friend of C ⇏ A friend of C

### Friend Class:
- All member functions of a friend class can access all members of the class that granted friendship
```cpp
class A { ... };
class B {
    friend class A;  // B grants A as friend
    ...
};
// Now all members of A can access any member of B
```

### Member function as friend of another class:
- A member function of class A can be declared as friend of class B
- The class from which the friend function comes must be defined first

## 9.15 Using the this Pointer
- (*Mentioned in TOC but briefly covered in this part — `this` is implicitly used in member functions and operator overloading; see Ch10 for detailed usage*)

## 9.16 Dynamic Memory Management with Operators new and delete

### new operator
- Dynamically allocates exact amount of memory at **runtime** in the **heap** (free store)
- Syntax:
  - `ptr = new Type;` — allocate one object
  - `ptr = new Type(x);` — allocate with initial value
  - `ptr = new Type[n];` — allocate array of n

### delete operator
- Returns memory to heap for reuse by future `new` operations
- Syntax:
  - `delete ptr;` — deallocate single object
  - `delete[] ptr;` — deallocate array

### For fundamental types:
```cpp
double *ptr = new double;  // allocate
cout << *ptr << endl;
delete ptr;                // deallocate
```

### For class objects:
- **new**: allocates storage → calls constructor → returns pointer of the specified type
- **delete**: calls destructor → deallocates memory

## 9.17 static Class Members

### static Data Member
- Only **one copy** shared by **all objects** of the class ("class-wide" information)
- Stored in **data zone** of memory (assigned during compilation, not during object definition)
- Seems like a global variable but has **class scope**
- Can be declared `public`, `private`, or `protected`

### static data member definition and initialization:
```cpp
class Employee {
    static const int a = 0;   // const static int: can define+initialize in class
    static int count;         // declaration only
};
// Outside class definition (in .cpp file):
int Employee::count = 0;     // definition + initialization
```

### Implicit initialization:
- Fundamental-type static data member defaults to **0**
  - `int Employee::count;` // initialized to 0 by default
- static member of class type: default constructor is invoked

### Accessing public static members:
- Via class name + scope resolution: `Student::count` (when no object exists)
- Via any object: `student_1.count`

### static Member Function
- Only accesses **static data members** and **static member functions**
- Is a service of the **class**, not of a specific object
- Does **NOT** have a `this` pointer
- Can be defined inside or outside class
- Cannot be declared `const`

### Compatibility table:
| Caller type | Access target | OK/Error |
|-------------|--------------|----------|
| static member function | static member | ✓ |
| static member function | non-static member | ✗ |
| non-static member function | static member | ✓ |
| non-static member function | non-static member | ✓ |

### Invocation:
```cpp
int a = X::stcF();     // OK (no object needed)
int b = X::memF();     // ERROR (non-static needs object)
```

## 9.18 Data Abstraction and Information Hiding
- (*Covered across multiple sections — the overall theme of encapsulation, public/private access control*)

---

## Summary of Part II:
1. const objects and const member functions
2. Member initializer syntax / list (required for const, reference, member objects)
3. Object composition (has-a relationship)
4. friend function & friend class
5. this pointer
6. Dynamic memory allocation (`new`/`delete`)
7. Static class members (data + function)
