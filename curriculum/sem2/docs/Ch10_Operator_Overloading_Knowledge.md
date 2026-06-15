# Chapter 10: Operator Overloading — Knowledge Points

## 10.1 Introduction
- Operator overloading makes programs more readable and programming more convenient
- Built-in operators already overloaded: `operator+(int,int)` vs `operator+(double,double)`
- Operator overloading for user-defined objects is generally necessary for class objects
- Straightforward and natural way to extend C++

## 10.2 Fundamentals of Operator Overloading

### Basic concept
- To use an operator on a class object, it must be overloaded for that class
- **Three exceptions** (can also be overloaded): assignment (`=`), address (`&`), comma (`,`)
- Overloading provides concise notation:
  - `complex1.add(complex2)` → `complex1 + complex2`

### Operator function definition:
- Function name: `operator@` (keyword `operator` + operand symbol `@`)
- Example: `Complex operator+(const Complex& a);`

### Operator function invocation:
- `complex1 + complex2;` — compiler interprets as function call

## 10.3 Restrictions on Operator Overloading

### Cannot:
- Create **new** operators
- Change **precedence** of operator
- Change **associativity** (left-to-right / right-to-left)
- Change **number of operands** (arity)

### Unary/binary/ternary:
| Operator type | Examples |
|--------------|----------|
| Unary | `+1`, `-1`, `!0`, ... |
| Binary | `1+2`, `1-2`, `1*2`, ... |
| Ternary | `?:` (only ternary operator) |

### Unary operators that can also be binary: `+`, `-`, `*`, `&`

### Important restriction:
- How an operator works on **fundamental types** cannot be changed
- Operator overloading works only with objects of **user-defined types**
- `int + int` — cannot be changed; `complex + complex` — can be overloaded; `complex + int` — can be defined

## 10.4 Operator Functions as Class Members vs. Global Functions

### As member function:
```cpp
class String {
public:
    bool operator!() const;
};
// Definition:
T ClassName::operator op (...) {
    // function body
}
```
- Uses `*this` to implicitly get the left (or only) operand
- Left operand must be an object (or reference) of the **same class**
- Number of parameters = **Number of operands - 1**
- **Operators `()`, `[]`, `->` or any assignment operator must be overloaded as member function**

### Examples (member function):
```cpp
a3 = a1 * a2;    →  a3 = a1.operator*(a2);
a3 = a1++;       →  a3 = a1.operator++();
a3 += a1;        →  a3.operator+=(a1);
```

### As global function:
```cpp
T operator op (...) {
    // function body
}
```
- No `this` pointer
- Needs parameters for **all** operands
- Number of parameters = **Number of operands**
- Can have left object of different class or fundamental type
- Can be a **friend** to access non-public data

### Examples (global function):
```cpp
a3 = a1 * a2;    →  a3 = operator*(a1, a2);
a3 = a1++;       →  a3 = operator++(a1);
a3 += a1;        →  operator+=(a3, a1);
```

### Commutative operators:
- For `+` to be commutative (both `a+b` and `b+a` work with different classes):
  - `ComplexClass + int` and `int + ComplexClass` — may need global function

## 10.5 Overloading Stream Insertion and Stream Extraction Operators

### `<<` operator (stream insertion):
```cpp
ostream &operator<<(ostream &output, const PhoneNumber &number) {
    output << ... ;
    return output;  // enables cascading: cout << a << b;
}
```
- Must be a **global function** (left operand is `ostream`, not the user class)
- Return reference to `ostream` for **cascading** calls

### `>>` operator (stream extraction):
```cpp
istream &operator>>(istream &input, PhoneNumber &number) {
    input >> ...;
    return input;  // enables cascading: cin >> a >> b;
}
```
- Uses `input.ignore()` to skip characters
- Uses `setw(n)` to restrict number of characters read

### Example: PhoneNumber class
- Stores: `areaCode` (3 digits), `exchange` (3 digits), `line` (4 digits)
- Format: `(123) 456-7890`
- `cin >> phone` reads: skip `(`, read 3-digit area code, skip `)` and space, read 3-digit exchange, skip `-`, read 4-digit line
- `cout << phone` outputs: `(areaCode) exchange-line`

## 10.6 Overloading Unary Operators

### Two ways:

**(1) As non-static member function with NO argument:**
- Interpreted as: `Object.operator op()`
- `this` serves as the implicit operand

**(2) As global function with ONE argument:**
- Argument must be an object (or reference) of the class
- Interpreted as: `operator op(Object)`

## 10.7 Overloading Binary Operators

### Two ways:

**(1) As non-static member function with ONE argument:**
- Interpreted as: `ObjectL.operator op(ObjectR)`
- `this` → ObjectL; parameter → ObjectR

**(2) As global function with TWO arguments:**
- Interpreted as: `operator op(ObjectL, ObjectR)`

## 10.8 Case Study: Array Class (Fig. 10.10~10.11)

### Key features:
- Dynamically allocated integer array
- Default constructor: `Array(int = 10)`
- Copy constructor: `Array(const Array &)` — deep copy
- Destructor: `~Array()` — releases `delete[] ptr`
- Assignment operator: `const Array &operator=(const Array &)` — checks for self-assignment, reallocates if size differs
- Equality: `bool operator==(const Array &) const`
- Inequality: `bool operator!=(const Array &right) const { return !(*this == right); }` — reuses `==`
- Subscript (lvalue): `int &operator[](int)` — returns reference, allows modification
- Subscript (rvalue): `int operator[](int) const` — returns copy, for const objects
- Stream operators: `friend ostream &operator<<` and `friend istream &operator>>`

### Assignment operator pattern:
1. Check for **self-assignment**: `if (&right != this)`
2. If sizes differ, `delete[]` old, allocate new
3. Copy elements
4. Return `*this` (enables cascading: `x = y = z`)

## 10.9 Converting Between Types

### Two directions:

**(1) Conversion Constructor — Other type → Class type:**
- Single-argument constructor
- Converts fundamental type or another class type to this class type
- Format: `ClassName(T) { ... // converting methods }`

**(2) Conversion/Cast Operator — Class type → Other type:**
- A special member function
- Converts this class type to fundamental type or another class type
- Format:
```cpp
ClassName::operator T() {
    // converting methods
    return data_Of_T;
}
```
- Is a **non-static member function**
- Target type `T` can be fundamental or user-defined
- **No parameters, no return type**, but must return an object of type `T`

## 10.10 Case Study: String Class (Fig. 10.1)

### Key features:
- Dynamic char array (`char *sPtr`) + length tracking
- **Conversion/default constructor**: `String(const char * = "")` — converts `char*` to String
- **Copy constructor**: `String(const String &)`
- **Destructor**: `~String()` — releases dynamic memory
- **Assignment operator**: `const String &operator=(const String &)`
- **Concatenation**: `const String &operator+=(const String &)`
- **Empty test**: `bool operator!() const` — is String empty?
- **Relational operators**: `==`, `!=` (reuses `==`), `<`, `>` (reuses `<`), `<=` (reuses `<`)
  - Demonstrates **code reusability**: `!=` calls `==`, `>` calls `<`, `<=` calls `>`
- **Subscript operators**: `char &operator[](int)` (lvalue) and `char operator[](int) const` (rvalue)
- **Function call operator (substring)**: `String operator()(int index, int subLength = 0) const`
- **Utility function**: `void setString(const char *)` — called by constructors and `operator=`

## 10.11 Overloading ++ and --

### Prefix increment (++x):
- Returns by **reference**: `Date &operator++()`
- Modifies object, returns `*this` (creates an lvalue)

### Postfix increment (x++):
- Has a dummy `int` parameter (unnamed) to distinguish from prefix
- Returns by **value**: `Date operator++(int)`
- Saves current state in temp, increments, returns **unincremented temp** (not a reference)

```cpp
Date &Date::operator++() {      // prefix
    helpIncrement();
    return *this;
}
Date Date::operator++(int) {    // postfix
    Date temp = *this;
    helpIncrement();
    return temp;  // value return, not reference
}
```

## 10.12 Case Study: Date Class (Fig. 10.6~10.7)

### Features:
- Default constructor, `setDate()`, `leapYear()`, `endOfMonth()`
- Prefix/postfix `++` overloaded
- `+=` operator: `const Date &operator+=(int)` — returns `*this` for cascading
- `<<` operator: outputs "Month day, year" format
- Utility function: `helpIncrement()` — handles day/month/year rollover

## 10.13 Standard Library Class string
- C++ standard class: `#include <string>` (mentioned for reference, similar to the custom String class)

## 10.14 Explicit Constructors
- Keyword `explicit` on single-argument constructor prevents **implicit** conversion
- `explicit Array(int = 10);` — prevents accidental conversion `outputArray(3)` from converting int to Array
- Without `explicit`, `3` would be silently converted to `Array(3)`

---

## Summary:
1. What operators can be overloaded, when, how, and restrictions
2. Member function vs. global function approaches
3. Overloading unary and binary operators
4. Conversion constructor (→ class type) vs. conversion operator (class type →)
5. Array, String, Date class case studies
6. Prefix vs. postfix `++`/`--`
7. Explicit constructors
