#ifndef MINISTL_VECTOR_H
#define MINISTL_VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <initializer_list>

namespace miniSTL {

template <typename T, typename Allocator = std::allocator<T>>
class vector {
public:
    using value_type             = T;
    using allocator_type         = Allocator;
    using size_type              = std::size_t;
    // difference_type 是用于表示指针之间距离的有符号整数类型
    using difference_type = std::ptrdiff_t;
    using reference             = T&;
    using const_reference        = const T&;
    using pointer               = T*;
    using const_pointer         = const T*;

    class iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::random_access_iterator_tag;
        //随机访问迭代器，支持随机访问，支持++，--，+，-，==，!=，<，<=，>，>=，-
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
        //拿到原始指针
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

    vector() : start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {}
    explicit vector(const Allocator& alloc) : alloc_(alloc), start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {}
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());
    template <typename InputIt>
    vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
    vector(const vector& other);
    vector(vector&& other) noexcept;//noexcept不抛异常，优先移动构造
    vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    ~vector();

    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;
    vector& operator=(std::initializer_list<T> init);

    void assign(size_type count, const T& value);
    template <typename InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> init);

    allocator_type get_allocator() const { return alloc_; }

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos) { return start_[pos]; }
    const_reference operator[](size_type pos) const { return start_[pos]; }
    reference front() { return *start_; }
    const_reference front() const { return *start_; }
    reference back() { return *(finish_ - 1); }//左闭右开区间
    const_reference back() const { return *(finish_ - 1); }
    pointer data() { return start_; }
    const_pointer data() const { return start_; }

    iterator begin() { return iterator(start_); }
    const_iterator begin() const { return const_iterator(start_); }
    const_iterator cbegin() const { return const_iterator(start_); }
    iterator end() { return iterator(finish_); }
    const_iterator end() const { return const_iterator(finish_); }
    const_iterator cend() const { return const_iterator(finish_); }
    iterator rbegin() { return iterator(finish_ - 1); }
    const_iterator rbegin() const { return const_iterator(finish_ - 1); }
    iterator rend() { return iterator(start_ - 1); }
    const_iterator rend() const { return const_iterator(start_ - 1); }

    bool empty() const { return start_ == finish_; }
    size_type size() const { return static_cast<size_type>(finish_ - start_); }
    size_type max_size() const { return alloc_.max_size(); }
    void reserve(size_type new_cap);
    size_type capacity() const { return static_cast<size_type>(end_of_storage_ - start_); }
    void shrink_to_fit();

    void clear();
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> init);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void resize(size_type count, const value_type& value = value_type());
    void swap(vector& other) noexcept;

private:
    Allocator alloc_;
    pointer start_;
    pointer finish_;
    pointer end_of_storage_;

    void reallocate(size_type new_cap);
};

} // namespace miniSTL

namespace miniSTL {

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type count, const T& value, const Allocator& alloc)
    : alloc_(alloc), start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {
    if (count > 0) {
        start_ = alloc_.allocate(count);
        finish_ = start_;
        end_of_storage_ = start_ + count;
        for (size_type i = 0; i < count; ++i) {
            alloc_.construct(finish_++, value);
        }
    }
}

template <typename T, typename Allocator>
template <typename InputIt>
vector<T, Allocator>::vector(InputIt first, InputIt last, const Allocator& alloc)
    : alloc_(alloc), start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {
    for (; first != last; ++first) push_back(*first);
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other)
    : alloc_(other.alloc_), start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {
    size_type n = other.size();
    if (n > 0) {
        start_ = alloc_.allocate(n);
        finish_ = start_;
        end_of_storage_ = start_ + n;
        for (size_type i = 0; i < n; ++i) alloc_.construct(finish_++, other.start_[i]);
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept
    : alloc_(std::move(other.alloc_)),
      start_(other.start_), finish_(other.finish_), end_of_storage_(other.end_of_storage_) {
    other.start_ = other.finish_ = other.end_of_storage_ = nullptr;
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> init, const Allocator& alloc)
    : alloc_(alloc), start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {
    reserve(init.size());
    for (const auto& v : init) push_back(v);
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector() {
    clear();
    if (start_) alloc_.deallocate(start_, capacity());
}

template <typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
    if (this != &other) assign(other.begin(), other.end());
    return *this;
}

template <typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept {
    if (this != &other) {
        clear();
        if (start_) alloc_.deallocate(start_, capacity());
        start_ = other.start_; finish_ = other.finish_; end_of_storage_ = other.end_of_storage_;
        other.start_ = other.finish_ = other.end_of_storage_ = nullptr;
    }
    return *this;
}

template <typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> init) {
    assign(init);
    return *this;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(size_type count, const T& value) {
    clear();
    if (count > capacity()) reallocate(count);
    for (size_type i = 0; i < count; ++i) alloc_.construct(finish_++, value);
}

template <typename T, typename Allocator>
template <typename InputIt>
void vector<T, Allocator>::assign(InputIt first, InputIt last) {
    clear();
    for (; first != last; ++first) push_back(*first);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(std::initializer_list<T> init) {
    clear();
    reserve(init.size());
    for (const auto& v : init) push_back(v);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
    if (pos >= size()) throw std::out_of_range("vector::at");
    return start_[pos];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const {
    if (pos >= size()) throw std::out_of_range("vector::at");
    return start_[pos];
}

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type new_cap) {
    if (new_cap > capacity()) reallocate(new_cap);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
    if (size() < capacity()) reallocate(size());
}

template <typename T, typename Allocator>
void vector<T, Allocator>::clear() {
    while (finish_ != start_) alloc_.destroy(--finish_);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, const T& value) {
    return insert(pos, size_type(1), value);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, T&& value) {
    difference_type offset = pos.base() - start_;
    if (finish_ != end_of_storage_) {
        alloc_.construct(finish_, std::move(*(finish_ - 1)));
        ++finish_;
        pointer p = start_ + offset;
        for (pointer move = finish_ - 1; move != p; --move) *move = std::move(*(move - 1));
        *p = std::move(value);
    } else {
        size_type old_size = size();
        size_type new_cap = old_size == 0 ? 1 : old_size * 2;
        pointer new_start = alloc_.allocate(new_cap);
        pointer new_finish = new_start;
        for (pointer it = start_; it != pos.base(); ++it, ++new_finish) alloc_.construct(new_finish, std::move(*it));
        alloc_.construct(new_finish++, std::move(value));
        for (pointer it = pos.base(); it != finish_; ++it, ++new_finish) alloc_.construct(new_finish, std::move(*it));
        clear();
        alloc_.deallocate(start_, capacity());
        start_ = new_start; finish_ = new_finish; end_of_storage_ = start_ + new_cap;
    }
    return iterator(start_ + offset);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, size_type count, const T& value) {
    if (count == 0) return iterator(const_cast<pointer>(pos.base()));
    difference_type offset = pos.base() - start_;
    if (size() + count > capacity()) {
        size_type old_size = size();
        size_type new_cap = old_size + (old_size > count ? old_size : count);
        pointer new_start = alloc_.allocate(new_cap);
        pointer new_finish = new_start;
        for (pointer it = start_; it != pos.base(); ++it, ++new_finish) alloc_.construct(new_finish, std::move(*it));
        for (size_type i = 0; i < count; ++i) alloc_.construct(new_finish++, value);
        for (pointer it = pos.base(); it != finish_; ++it, ++new_finish) alloc_.construct(new_finish, std::move(*it));
        clear();
        alloc_.deallocate(start_, capacity());
        start_ = new_start; finish_ = new_finish; end_of_storage_ = start_ + new_cap;
    } else {
        size_type elems_after = finish_ - pos.base();
        if (elems_after >= count) {
            for (size_type i = 0; i < count; ++i) { alloc_.construct(finish_, *(finish_ - count)); ++finish_; }
            for (pointer move = finish_ - count - elems_after; move != pos.base(); ) {
                --move;
                *(move + count) = std::move(*move);
            }
            pointer p = start_ + offset;
            for (size_type i = 0; i < count; ++i) *(p + i) = value;
        } else {
            for (size_type i = 0; i < count - elems_after; ++i) alloc_.construct(finish_++, value);
            for (pointer it = pos.base(); it != finish_ - (count - elems_after); ++it) alloc_.construct(finish_++, std::move(*it));
            for (pointer it = pos.base(); it != start_ + offset + count; ++it) *it = value;
        }
    }
    return iterator(start_ + offset);
}

template <typename T, typename Allocator>
template <typename InputIt>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
    difference_type offset = pos.base() - start_;
    while (first != last) {
        insert(begin() + offset, *first);
        ++offset; ++first;
    }
    return iterator(start_ + offset);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> init) {
    return insert(pos, init.begin(), init.end());
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator pos) {
    pointer p = const_cast<pointer>(pos.base());
    for (pointer it = p + 1; it != finish_; ++it) *(it - 1) = std::move(*it);
    alloc_.destroy(--finish_);
    return iterator(p);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
    pointer p_first = const_cast<pointer>(first.base());
    pointer p_last = const_cast<pointer>(last.base());
    difference_type n = p_last - p_first;
    for (pointer it = p_last; it != finish_; ++it) *(it - n) = std::move(*it);
    for (difference_type i = 0; i < n; ++i) alloc_.destroy(--finish_);
    return iterator(p_first);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value) {
    if (finish_ != end_of_storage_) alloc_.construct(finish_++, value);
    else { reallocate(size() == 0 ? 1 : size() * 2); alloc_.construct(finish_++, value); }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(T&& value) {
    if (finish_ != end_of_storage_) alloc_.construct(finish_++, std::move(value));
    else { reallocate(size() == 0 ? 1 : size() * 2); alloc_.construct(finish_++, std::move(value)); }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
    alloc_.destroy(--finish_);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count, const value_type& value) {
    if (count < size()) { while (size() > count) pop_back(); }
    else if (count > size()) { reserve(count); while (size() < count) push_back(value); }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept {
    std::swap(start_, other.start_);
    std::swap(finish_, other.finish_);
    std::swap(end_of_storage_, other.end_of_storage_);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::reallocate(size_type new_cap) {
    pointer new_start = alloc_.allocate(new_cap);
    pointer new_finish = new_start;
    for (pointer it = start_; it != finish_; ++it, ++new_finish) alloc_.construct(new_finish, std::move(*it));
    size_type old_size = size();
    clear();
    if (start_) alloc_.deallocate(start_, capacity());
    start_ = new_start;
    finish_ = new_start + old_size;
    end_of_storage_ = start_ + new_cap;
}

} // namespace miniSTL

#endif // MINISTL_VECTOR_H
