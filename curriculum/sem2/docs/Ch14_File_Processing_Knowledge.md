# 第14章：文件处理 — 知识点

## 14.1 引言
- **信息存储**：
  - **临时数据**：变量、数组、常量等 → 存储在内存中，量小但访问快
  - **持久数据**：文件 → 存储在辅助存储设备（磁盘、光盘、磁带等），量大但访问慢

## 14.2 数据层次结构

| 层次 | 说明 | C++ 表示 |
|------|------|---------|
| **位**（Bit） | 二进制数字，值为 0 或 1 | — |
| **字符**（Character） | 数字、字母和特殊符号（@, %, &...） | `char`（1字节）、`wchar_t`（多字节） |
| **字段**（Field） | 一组传达某种含义的字符 | 数据成员 |
| **记录**（Record） | 由若干相关字段组成 | 类（class） |
| **文件**（File） | 记录通常按键字段排序存储 | — |

- **记录键**（Record-key）：每条记录独有的字段，用于标识记录

### 按存储格式分类
| 类型 | 说明 |
|------|------|
| **文本文件** | 以 ASCII 字符（字节）形式存储 |
| **二进制文件** | 以二进制位（01）形式存储 |

### 按访问方式分类
| 类型 | 说明 |
|------|------|
| **顺序文件** | 记录长度可不同，只能顺序访问 |
| **随机访问文件** | 记录长度通常相同，可随机访问 |

## 14.3 文件和流

### I/O 流模板层次结构
```
basic_ios
├── basic_istream → basic_ifstream（文件输入）
├── basic_ostream → basic_ofstream（文件输出）
└── basic_iostream → basic_fstream（文件输入/输出）
```

### 标准 I/O 流对象
| 对象 | 说明 | 方向 |
|------|------|------|
| `cin` | 标准输入（键盘） | 键盘 → 内存 |
| `cout` | 标准输出（屏幕） | 内存 → 屏幕 |
| `cerr` | 标准错误（无缓冲） | 内存 → 屏幕 |
| `clog` | 标准错误（有缓冲） | 内存 → 屏幕 |

- 定义在 `<iostream>` 中
- `cin`：`istream` 类型；`cout`/`cerr`/`clog`：`ostream` 类型

### 文件 I/O 流对象
| 对象 | 说明 |
|------|------|
| `ifstream` | 从文件读取（输入） |
| `ofstream` | 写入文件（输出） |
| `fstream` | 文件读写（输入和输出） |

- 定义在 `<fstream>` 中（包含三个类模板及 `char` 特化）

### 程序与文件的通信
- 通过**流对象**进行
- 需要包含：`<iostream>` 和 `<fstream>`

## 14.4 创建顺序文件

### 创建 ofstream 对象

#### 方式一：创建流对象时直接打开文件
```cpp
ofstream outClientFile("clients.dat", ios::out);
```
- `filename`：路径 + 文件名（如 `"c:\\clients.dat"` 或 `"clients.dat"`）
- `mode`：文件打开模式

#### 方式二：先创建流对象，再打开文件
```cpp
ofstream outClientFile;
outClientFile.open("clients.dat", ios::out);
```

### 文件打开模式
| 模式 | 说明 |
|------|------|
| `ios::out` | ofstream 默认模式；文件存在则覆盖，不存在则创建 |
| `ios::app` | 追加数据到文件末尾 |
| `ios::trunc` | 等同于 `ios::out`，打开时清空已有内容 |

### 判断文件是否成功打开
```cpp
if (!outClientFile) {
    cerr << "File can not be opened!";
    exit(1);
}
```
- `operator!`：文件打开**失败**返回 `true`，成功返回 `false`

### 写入数据
```cpp
outClientFile << myVariable;
```

### 判断输入是否结束（operator void*）
```cpp
while (cin >> account >> name >> balance) { ... }
// 或
while (!cin.eof()) { ... }
```
- `operator void*`：流正常时返回非空指针（`true`），遇到 EOF 或错误返回空指针 `0`（`false`）

### 关闭文件
- **隐式**：ofstream 对象析构函数自动关闭
- **显式**（推荐）：
```cpp
outClientFile.close();
```
- 性能提示：程序不再需要引用文件时应显式关闭

### 示例：输出文本到顺序文件（图 14.4）
- 从键盘读取账户、姓名、余额，写入 `clients.dat`

## 14.5 从顺序文件读取数据

### 创建 ifstream 对象

#### 方式一：创建流对象时直接打开
```cpp
ifstream inClientFile("clients.dat", ios::in);
// ios::in 是 ifstream 默认模式
```

#### 方式二：先创建流对象，再打开
```cpp
ifstream inClientFile;
inClientFile.open("clients.dat");
```

### 读取数据与判断
- `operator!`：判断文件是否成功打开
- `operator void*`：判断是否到达文件末尾
```cpp
while (inClientFile >> account >> name >> balance)
    outputLine(account, name, balance);
```
- 遇到 EOF 返回 `0`（`false`），循环结束
- ifstream 析构函数隐式关闭文件
- 需要**重新读取**文件时：使用 `clear()` 重置 EOF 状态，`seekg(0)` 回到文件开头

### 文件位置指针
- 文件中下一个要读取（"get"指针）或写入（"put"指针）的字节编号

### 指针重定位成员函数

#### istream 成员函数
| 函数 | 说明 |
|------|------|
| `seekg(streamoff, ios::seek_dir)` | 移动 "get" 指针 |
| `tellg()` | 返回当前 "get" 指针位置（`long` 类型） |

#### ostream 成员函数
| 函数 | 说明 |
|------|------|
| `seekp(streamoff, ios::seek_dir)` | 移动 "put" 指针 |
| `tellp()` | 返回当前 "put" 指针位置（`long` 类型） |

#### 参数说明
- `offset`：从指定位置偏移的字节数（`long` 类型）
- `direction`：寻址方向

| 方向 | 说明 |
|------|------|
| `ios::beg` | 从文件**开头**开始定位（默认） |
| `ios::cur` | 从**当前**位置开始定位 |
| `ios::end` | 从文件**末尾**开始定位 |

#### 示例
```cpp
fileObject.seekg(0);           // 定位到第0字节（默认 ios::beg）
fileObject.seekg(n);           // 定位到第n字节
fileObject.seekg(n, ios::cur); // 从当前位置向前移动n字节
fileObject.seekg(y, ios::end); // 从文件末尾向后移动y字节
fileObject.seekg(0, ios::end); // 定位到文件末尾
location = fileObject.tellg(); // 将get指针值赋给location
```

### 字符输入函数

#### get()
```cpp
int istream::get();                         // 读取一个字符，返回整型
istream &istream::get(char &);              // 读取一个字符存入引用参数
istream &istream::get(unsigned char &);     // 读取一个字符（无符号版本）
cin.get();                                  // 常用调用方式
```
- `get()` 可以读取包括空白字符在内的任何字符
- 与 `>>` 不同，`>>` 会跳过空白字符

#### getline()
- `<string>` 版本：
```cpp
istream &getline(istream &is, string &str, char delim);
// 默认分隔符为 '\n'
```
- `<iostream>` 版本（用于 char*）：
```cpp
cin.getline(char *array, int count);
// 读取至多 count-1 个字符，自动添加 '\0'
```

### 分类处理示例（图 14.7）
- **零余额**：`balance == 0`
- **贷方余额**：`balance < 0`
- **借方余额**：`balance > 0`
- 读取整个文件后重新定位：`inClientFile.clear(); inClientFile.seekg(0);`

---

## 小结：
1. 数据层次结构：位 → 字符 → 字段 → 记录 → 文件
2. 文本文件 vs. 二进制文件；顺序文件 vs. 随机访问文件
3. 文件 I/O 流对象：`ifstream`、`ofstream`、`fstream`
4. 两种打开文件方式：构造时打开 vs. `open()`
5. 文件打开模式：`ios::out`、`ios::in`、`ios::app`、`ios::trunc`
6. `operator!` — 判断打开失败；`operator void*` — 判断 EOF
7. 显式关闭文件：`close()`（性能建议）
8. 文件位置指针：`seekg`/`seekp`（重定位）、`tellg`/`tellp`（获取位置）
9. 寻址方向：`ios::beg`、`ios::cur`、`ios::end`
10. `get()` 和 `getline()` 用于读取字符和行
11. `clear()` 重置流状态 + `seekg(0)` 回到开头重新读取
