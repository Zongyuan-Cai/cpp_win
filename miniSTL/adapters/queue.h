#ifndef MINISTL_QUEUE_H
#define MINISTL_QUEUE_H

#include <cstddef>
#include "../sequential/deque.h"

namespace miniSTL {

template <typename T, typename Container = miniSTL::deque<T>>
class queue {
public:
    using container_type = Container;
    using value_type     = typename Container::value_type;
    using size_type      = typename Container::size_type;
    using reference      = typename Container::reference;
    using const_reference = typename Container::const_reference;

    explicit queue(const Container& cont = Container()) : c_(cont) {}
    queue(const queue& other) : c_(other.c_) {}
    queue(queue&& other) noexcept : c_(std::move(other.c_)) {}
    queue& operator=(const queue& other) { c_ = other.c_; return *this; }
    queue& operator=(queue&& other) noexcept { c_ = std::move(other.c_); return *this; }

    bool empty() const { return c_.empty(); }
    size_type size() const { return c_.size(); }
    reference front() { return c_.front(); }
    const_reference front() const { return c_.front(); }
    reference back() { return c_.back(); }
    const_reference back() const { return c_.back(); }
    void push(const value_type& value) { c_.push_back(value); }
    void push(value_type&& value) { c_.push_back(std::move(value)); }
    void pop() { c_.pop_front(); }
    void swap(queue& other) noexcept { c_.swap(other.c_); }

    template <typename U, typename C>
    friend bool operator==(const queue<U, C>& a, const queue<U, C>& b);
    template <typename U, typename C>
    friend bool operator<(const queue<U, C>& a, const queue<U, C>& b);

protected:
    Container c_;
};

template <typename T, typename Container>
void swap(queue<T, Container>& a, queue<T, Container>& b) noexcept {
    a.swap(b);
}

template <typename T, typename Container>
bool operator==(const queue<T, Container>& a, const queue<T, Container>& b) {
    return a.c_ == b.c_;
}
template <typename T, typename Container>
bool operator!=(const queue<T, Container>& a, const queue<T, Container>& b) {
    return !(a == b);
}
template <typename T, typename Container>
bool operator<(const queue<T, Container>& a, const queue<T, Container>& b) {
    return a.c_ < b.c_;
}
template <typename T, typename Container>
bool operator<=(const queue<T, Container>& a, const queue<T, Container>& b) {
    return !(b < a);
}
template <typename T, typename Container>
bool operator>(const queue<T, Container>& a, const queue<T, Container>& b) {
    return b < a;
}
template <typename T, typename Container>
bool operator>=(const queue<T, Container>& a, const queue<T, Container>& b) {
    return !(a < b);
}

} // namespace miniSTL

#endif // MINISTL_QUEUE_H
