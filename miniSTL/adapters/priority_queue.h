#ifndef MINISTL_PRIORITY_QUEUE_H
#define MINISTL_PRIORITY_QUEUE_H

#include <cstddef>
#include <algorithm>
#include <functional>
#include "../sequential/vector.h"

namespace miniSTL {

template <typename T, typename Container = miniSTL::vector<T>,
          typename Compare = std::less<typename Container::value_type>>
class priority_queue {
public:
    using container_type = Container;
    using value_type     = typename Container::value_type;
    using size_type      = typename Container::size_type;
    using reference     = typename Container::reference;
    using const_reference = typename Container::const_reference;

    priority_queue() : c_(), comp_() {}
    explicit priority_queue(const Compare& compare) : c_(), comp_(compare) {}
    explicit priority_queue(const Compare& compare, const Container& cont) : c_(cont), comp_(compare) {
        std::make_heap(c_.begin(), c_.end(), comp_);
    }
    explicit priority_queue(const Compare& compare, Container&& cont) : c_(std::move(cont)), comp_(compare) {
        std::make_heap(c_.begin(), c_.end(), comp_);
    }
    template <typename InputIt>
    priority_queue(InputIt first, InputIt last, const Compare& compare = Compare())
        : c_(first, last), comp_(compare) {
        std::make_heap(c_.begin(), c_.end(), comp_);
    }
    template <typename InputIt>
    priority_queue(InputIt first, InputIt last, const Compare& compare, const Container& cont)
        : c_(cont), comp_(compare) {
        c_.insert(c_.end(), first, last);
        std::make_heap(c_.begin(), c_.end(), comp_);
    }
    priority_queue(const priority_queue& other) : c_(other.c_), comp_(other.comp_) {}
    priority_queue(priority_queue&& other) noexcept : c_(std::move(other.c_)), comp_(std::move(other.comp_)) {}
    priority_queue& operator=(const priority_queue& other) {
        c_ = other.c_;
        comp_ = other.comp_;
        return *this;
    }
    priority_queue& operator=(priority_queue&& other) noexcept {
        c_ = std::move(other.c_);
        comp_ = std::move(other.comp_);
        return *this;
    }

    bool empty() const { return c_.empty(); }
    size_type size() const { return c_.size(); }
    const_reference top() const { return c_.front(); }
    void push(const value_type& value) {
        c_.push_back(value);
        std::push_heap(c_.begin(), c_.end(), comp_);
    }
    void push(value_type&& value) {
        c_.push_back(std::move(value));
        std::push_heap(c_.begin(), c_.end(), comp_);
    }
    void pop() {
        std::pop_heap(c_.begin(), c_.end(), comp_);
        c_.pop_back();
    }
    void swap(priority_queue& other) noexcept {
        c_.swap(other.c_);
        std::swap(comp_, other.comp_);
    }

protected:
    Container c_;
    Compare comp_;
};

template <typename T, typename Container, typename Compare>
void swap(priority_queue<T, Container, Compare>& a, priority_queue<T, Container, Compare>& b) noexcept {
    a.swap(b);
}

} // namespace miniSTL

#endif // MINISTL_PRIORITY_QUEUE_H
