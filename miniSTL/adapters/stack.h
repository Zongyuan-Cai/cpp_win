#ifndef MINISTL_STACK_H
#define MINISTL_STACK_H

#include <cstddef>
#include "../sequential/deque.h"

namespace miniSTL {

template <typename T, typename Container = miniSTL::deque<T>>
class stack {
public:
    using container_type = Container;
    using value_type     = typename Container::value_type;
    using size_type      = typename Container::size_type;
    using reference      = typename Container::reference;
    using const_reference = typename Container::const_reference;

    explicit stack(const Container& cont = Container()) : c_(cont) {}
    stack(const stack& other) : c_(other.c_) {}
    stack(stack&& other) noexcept : c_(std::move(other.c_)) {}
    stack& operator=(const stack& other) { c_ = other.c_; return *this; }
    stack& operator=(stack&& other) noexcept { c_ = std::move(other.c_); return *this; }

    bool empty() const { return c_.empty(); }
    size_type size() const { return c_.size(); }
    reference top() { return c_.back(); }
    const_reference top() const { return c_.back(); }
    void push(const value_type& value) { c_.push_back(value); }
    void push(value_type&& value) { c_.push_back(std::move(value)); }
    void pop() { c_.pop_back(); }
    void swap(stack& other) noexcept { c_.swap(other.c_); }

    template <typename U, typename C>
    friend bool operator==(const stack<U, C>& a, const stack<U, C>& b);
    template <typename U, typename C>
    friend bool operator<(const stack<U, C>& a, const stack<U, C>& b);

protected:
    Container c_;
};

template <typename T, typename Container>
void swap(stack<T, Container>& a, stack<T, Container>& b) noexcept {
    a.swap(b);
}

template <typename T, typename Container>
bool operator==(const stack<T, Container>& a, const stack<T, Container>& b) {
    return a.c_ == b.c_;
}
template <typename T, typename Container>
bool operator!=(const stack<T, Container>& a, const stack<T, Container>& b) {
    return !(a == b);
}
template <typename T, typename Container>
bool operator<(const stack<T, Container>& a, const stack<T, Container>& b) {
    return a.c_ < b.c_;
}
template <typename T, typename Container>
bool operator<=(const stack<T, Container>& a, const stack<T, Container>& b) {
    return !(b < a);
}
template <typename T, typename Container>
bool operator>(const stack<T, Container>& a, const stack<T, Container>& b) {
    return b < a;
}
template <typename T, typename Container>
bool operator>=(const stack<T, Container>& a, const stack<T, Container>& b) {
    return !(a < b);
}

} // namespace miniSTL

#endif // MINISTL_STACK_H
