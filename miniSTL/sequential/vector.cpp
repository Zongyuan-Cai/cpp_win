#include "vector.h"

namespace miniSTL {

// 显式实例化常用类型，减少编译时间
template class vector<char>;
template class vector<int>;
template class vector<long>;
template class vector<long long>;
template class vector<unsigned>;
template class vector<float>;
template class vector<double>;

} // namespace miniSTL
