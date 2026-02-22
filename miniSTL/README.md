# miniSTL

按**容器类型**分文件夹的 miniSTL 实现，命名空间 `miniSTL`。一种类型一个文件夹。

## 目录结构

```
miniSTL/
├── detail/              # 内部实现（BST、哈希表）
│   ├── bst.h
│   └── hash_table.h
│
├── sequential/           # 顺序容器
│   ├── vector.h
│   ├── vector.cpp
│   ├── deque.h
│   ├── deque.cpp
│   ├── list.h
│   ├── list.cpp
│   ├── forward_list.h
│   ├── forward_list.cpp
│   ├── array.h
│   └── array.cpp
│
├── associative/          # 有序关联容器
│   ├── set.h
│   ├── set.cpp
│   ├── multiset.h
│   ├── multiset.cpp
│   ├── map.h
│   ├── map.cpp
│   ├── multimap.h
│   └── multimap.cpp
│
├── unordered/            # 无序关联容器
│   ├── unordered_set.h
│   ├── unordered_set.cpp
│   ├── unordered_multiset.h
│   ├── unordered_multiset.cpp
│   ├── unordered_map.h
│   ├── unordered_map.cpp
│   ├── unordered_multimap.h
│   └── unordered_multimap.cpp
│
└── adapters/             # 容器适配器
    ├── stack.h
    ├── stack.cpp
    ├── queue.h
    ├── queue.cpp
    ├── priority_queue.h
    └── priority_queue.cpp
```

## 使用方式

包含路径指向 miniSTL 根目录（例如 `-I miniSTL`），然后按类型目录包含头文件：

```cpp
#include "sequential/vector.h"
#include "sequential/deque.h"
#include "associative/map.h"
#include "unordered/unordered_set.h"
#include "adapters/stack.h"

int main() {
    miniSTL::vector<int> v = {1, 2, 3};
    miniSTL::map<int, int> m;
    miniSTL::stack<int> s;
    return 0;
}
```

适配器默认底层容器为同命名空间内的顺序容器（如 `miniSTL::deque`、`miniSTL::vector`），通过 `../sequential/` 引用，无需额外配置。
