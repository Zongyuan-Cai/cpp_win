#ifndef MINISTL_ARRAY_H
#define MINISTL_ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

namespace miniSTL {

template <typename T, std::size_t N>
class array {
public:
    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;

    class iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::random_access_iterator_tag;

        iterator() : ptr_(nullptr) {}
        explicit iterator(pointer p) : ptr_(p) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        reference operator[](difference_type n) const { return ptr_[n]; }

        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }
        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr_; return tmp; }

        iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }
        iterator operator+(difference_type n) const { return iterator(ptr_ + n); }
        iterator operator-(difference_type n) const { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

        pointer base() const { return ptr_; }

    private:
        pointer ptr_;
    };

    class const_iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator() : ptr_(nullptr) {}
        explicit const_iterator(const_pointer p) : ptr_(p) {}
        const_iterator(const iterator& it) : ptr_(it.base()) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        reference operator[](difference_type n) const { return ptr_[n]; }

        const_iterator& operator++() { ++ptr_; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++ptr_; return tmp; }
        const_iterator& operator--() { --ptr_; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --ptr_; return tmp; }

        const_iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        const_iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }
        const_iterator operator+(difference_type n) const { return const_iterator(ptr_ + n); }
        const_iterator operator-(difference_type n) const { return const_iterator(ptr_ - n); }
        difference_type operator-(const const_iterator& other) const { return ptr_ - other.ptr_; }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const const_iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const const_iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const const_iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const const_iterator& other) const { return ptr_ >= other.ptr_; }

        const_pointer base() const { return ptr_; }

    private:
        const_pointer ptr_;
    };

    T elems_[N];

    array() = default;
    array(std::initializer_list<T> init) {
        std::size_t i = 0;
        for (const auto& v : init) {
            if (i >= N) break;
            elems_[i++] = v;
        }
        for (; i < N; ++i) elems_[i] = T();
    }

    reference at(size_type pos) {
        if (pos >= N) throw std::out_of_range("array::at");
        return elems_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= N) throw std::out_of_range("array::at");
        return elems_[pos];
    }
    reference operator[](size_type pos) { return elems_[pos]; }
    const_reference operator[](size_type pos) const { return elems_[pos]; }
    reference front() { return elems_[0]; }
    const_reference front() const { return elems_[0]; }
    reference back() { return elems_[N - 1]; }
    const_reference back() const { return elems_[N - 1]; }
    pointer data() { return elems_; }
    const_pointer data() const { return elems_; }

    iterator begin() { return iterator(elems_); }
    const_iterator begin() const { return const_iterator(elems_); }
    const_iterator cbegin() const { return const_iterator(elems_); }
    iterator end() { return iterator(elems_ + N); }
    const_iterator end() const { return const_iterator(elems_ + N); }
    const_iterator cend() const { return const_iterator(elems_ + N); }

    bool empty() const { return N == 0; }
    size_type size() const { return N; }
    size_type max_size() const { return N; }

    void fill(const T& value) {
        std::fill_n(elems_, N, value);
    }
    void swap(array& other) noexcept {
        std::swap_ranges(elems_, elems_ + N, other.elems_);
    }
};

template <typename T, std::size_t N>
bool operator==(const array<T, N>& a, const array<T, N>& b) {
    return std::equal(a.begin(), a.end(), b.begin());
}
template <typename T, std::size_t N>
bool operator!=(const array<T, N>& a, const array<T, N>& b) {
    return !(a == b);
}
template <typename T, std::size_t N>
bool operator<(const array<T, N>& a, const array<T, N>& b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}
template <typename T, std::size_t N>
bool operator<=(const array<T, N>& a, const array<T, N>& b) {
    return !(b < a);
}
template <typename T, std::size_t N>
bool operator>(const array<T, N>& a, const array<T, N>& b) {
    return b < a;
}
template <typename T, std::size_t N>
bool operator>=(const array<T, N>& a, const array<T, N>& b) {
    return !(a < b);
}

} // namespace miniSTL

#endif // MINISTL_ARRAY_H
