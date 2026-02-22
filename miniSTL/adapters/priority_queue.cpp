#include "priority_queue.h"

namespace miniSTL {

template class priority_queue<int>;
template class priority_queue<int, miniSTL::vector<int>, std::greater<int>>;
template class priority_queue<double>;

} // namespace miniSTL
