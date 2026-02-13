#include "array.h"

namespace miniSTL {

// array 是固定大小，常用尺寸显式实例化
template class array<int, 0>;
template class array<int, 1>;
template class array<int, 8>;
template class array<int, 16>;
template class array<double, 8>;

} // namespace miniSTL
