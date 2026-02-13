#ifndef MINISTL_DEQUE_H
#define MINISTL_DEQUE_H

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <initializer_list>

namespace miniSTL {

template <typename T, typename Allocator = std::allocator<T>>
class deque {
public:
    using value_type             = T;
    using allocator_type         = Allocator;
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

        iterator() : buf_(nullptr), pos_(0), cap_(0), start_(0) {}
        iterator(pointer buf, size_type pos, size_type cap, size_type start = 0)
            : buf_(buf), pos_(pos), cap_(cap), start_(start) {}

        reference operator*() const { return buf_[pos_]; }
        pointer operator->() const { return buf_ + pos_; }
        reference operator[](difference_type n) const { return buf_[(pos_ + n) % cap_]; }

        iterator& operator++() { pos_ = (pos_ + 1) % cap_; return *this; }
        iterator operator++(int) { iterator tmp = *this; pos_ = (pos_ + 1) % cap_; return tmp; }
        iterator& operator--() { pos_ = (pos_ + cap_ - 1) % cap_; return *this; }
        iterator operator--(int) { iterator tmp = *this; pos_ = (pos_ + cap_ - 1) % cap_; return tmp; }

        iterator& operator+=(difference_type n) {
            difference_type new_logical = static_cast<difference_type>(logical_index()) + n;
            pos_ = cap_ ? static_cast<size_type>((static_cast<difference_type>(start_) + new_logical % static_cast<difference_type>(cap_) + static_cast<difference_type>(cap_) * 2) % static_cast<difference_type>(cap_)) : 0;
            return *this;
        }
        iterator& operator-=(difference_type n) { return *this += -n; }
        iterator operator+(difference_type n) const { iterator tmp = *this; return tmp += n; }
        iterator operator-(difference_type n) const { iterator tmp = *this; return tmp -= n; }
        difference_type operator-(const iterator& other) const {
            return static_cast<difference_type>(logical_index()) - static_cast<difference_type>(other.logical_index());
        }

        bool operator==(const iterator& other) const { return buf_ == other.buf_ && pos_ == other.pos_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        bool operator<(const iterator& other) const;

        size_type position() const { return pos_; }
        pointer buffer() const { return buf_; }
        size_type capacity() const { return cap_; }
        size_type start_index() const { return start_; }
        size_type logical_index() const {
            return cap_ ? (pos_ - start_ + cap_) % cap_ : 0;
        }

    private:
        pointer buf_;
        size_type pos_;
        size_type cap_;
        size_type start_;
    };

    class const_iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator() : buf_(nullptr), pos_(0), cap_(0), start_(0) {}
        const_iterator(const_pointer buf, size_type pos, size_type cap, size_type start = 0)
            : buf_(buf), pos_(pos), cap_(cap), start_(start) {}
        const_iterator(const iterator& it)
            : buf_(it.buffer()), pos_(it.position()), cap_(it.capacity()), start_(it.start_index()) {}

        reference operator*() const { return buf_[pos_]; }
        pointer operator->() const { return buf_ + pos_; }
        reference operator[](difference_type n) const { return buf_[(pos_ + n) % cap_]; }

        const_iterator& operator++() { pos_ = (pos_ + 1) % cap_; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; pos_ = (pos_ + 1) % cap_; return tmp; }
        const_iterator& operator--() { pos_ = (pos_ + cap_ - 1) % cap_; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; pos_ = (pos_ + cap_ - 1) % cap_; return tmp; }

        const_iterator& operator+=(difference_type n) {
            difference_type new_logical = static_cast<difference_type>(logical_index()) + n;
            pos_ = cap_ ? static_cast<size_type>((static_cast<difference_type>(start_) + new_logical % static_cast<difference_type>(cap_) + static_cast<difference_type>(cap_) * 2) % static_cast<difference_type>(cap_)) : 0;
            return *this;
        }
        const_iterator& operator-=(difference_type n) { return *this += -n; }
        const_iterator operator+(difference_type n) const { const_iterator tmp = *this; return tmp += n; }
        const_iterator operator-(difference_type n) const { const_iterator tmp = *this; return tmp -= n; }
        difference_type operator-(const const_iterator& other) const {
            return static_cast<difference_type>(logical_index()) - static_cast<difference_type>(other.logical_index());
        }

        bool operator==(const const_iterator& other) const { return buf_ == other.buf_ && pos_ == other.pos_; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
        bool operator<(const const_iterator& other) const {
            return (buf_ == other.buf_) && (logical_index() < other.logical_index());
        }

        size_type logical_index() const { return cap_ ? (pos_ - start_ + cap_) % cap_ : 0; }

    private:
        const_pointer buf_;
        size_type pos_;
        size_type cap_;
        size_type start_;
    };

    deque() : buf_(nullptr), cap_(0), start_(0), size_(0) {}
    explicit deque(const Allocator& alloc) : alloc_(alloc), buf_(nullptr), cap_(0), start_(0), size_(0) {}
    deque(size_type count, const T& value, const Allocator& alloc = Allocator());
    explicit deque(size_type count, const Allocator& alloc = Allocator());
    template <typename InputIt>
    deque(InputIt first, InputIt last, const Allocator& alloc = Allocator());
    deque(const deque& other);
    deque(deque&& other) noexcept;
    deque(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    ~deque();

    deque& operator=(const deque& other);
    deque& operator=(deque&& other) noexcept;
    deque& operator=(std::initializer_list<T> init);

    void assign(size_type count, const T& value);
    template <typename InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> init);

    allocator_type get_allocator() const { return alloc_; }

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos) { return buf_[(start_ + pos) % cap_]; }
    const_reference operator[](size_type pos) const { return buf_[(start_ + pos) % cap_]; }
    reference front() { return buf_[start_]; }
    const_reference front() const { return buf_[start_]; }
    reference back() { return buf_[(start_ + size_ - 1) % cap_]; }
    const_reference back() const { return buf_[(start_ + size_ - 1) % cap_]; }

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    size_type max_size() const { return alloc_.max_size(); }
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
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_back();
    void pop_front();
    void resize(size_type count, const value_type& value = value_type());
    void swap(deque& other) noexcept;

private:
    Allocator alloc_;
    pointer buf_;
    size_type cap_;
    size_type start_;
    size_type size_;

    size_type index_at(size_type i) const { return (start_ + i) % cap_; }
    void ensure_capacity(size_type need);
    void reallocate(size_type new_cap);
};

} // namespace miniSTL

// ========== 模板实现 ==========
namespace miniSTL {

template <typename T, typename Allocator>
bool deque<T, Allocator>::iterator::operator<(const iterator& other) const {
    if (buf_ != other.buf_) return false;
    return logical_index() < other.logical_index();
}

template <typename T, typename Allocator>
void deque<T, Allocator>::ensure_capacity(size_type need) {
    if (need <= cap_) return;
    size_type new_cap = (cap_ == 0) ? 4 : cap_ * 2;
    while (new_cap < need) new_cap *= 2;
    reallocate(new_cap);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::reallocate(size_type new_cap) {
    if (new_cap == 0) return;
    pointer new_buf = alloc_.allocate(new_cap);
    for (size_type i = 0; i < size_; ++i) {
        alloc_.construct(new_buf + i, std::move(buf_[index_at(i)]));
    }
    for (size_type i = 0; i < size_; ++i) {
        alloc_.destroy(buf_ + index_at(i));
    }
    if (buf_) alloc_.deallocate(buf_, cap_);
    buf_ = new_buf;
    cap_ = new_cap;
    start_ = 0;
}

template <typename T, typename Allocator>
deque<T, Allocator>::deque(size_type count, const T& value, const Allocator& alloc)
    : alloc_(alloc), buf_(nullptr), cap_(0), start_(0), size_(0) {
    ensure_capacity(count);
    for (size_type i = 0; i < count; ++i) {
        alloc_.construct(buf_ + i, value);
    }
    size_ = count;
}

template <typename T, typename Allocator>
deque<T, Allocator>::deque(size_type count, const Allocator& alloc)
    : alloc_(alloc), buf_(nullptr), cap_(0), start_(0), size_(0) {
    ensure_capacity(count);
    for (size_type i = 0; i < count; ++i) {
        alloc_.construct(buf_ + i, T());
    }
    size_ = count;
}

template <typename T, typename Allocator>
template <typename InputIt>
deque<T, Allocator>::deque(InputIt first, InputIt last, const Allocator& alloc)
    : alloc_(alloc), buf_(nullptr), cap_(0), start_(0), size_(0) {
    for (; first != last; ++first) push_back(*first);
}

template <typename T, typename Allocator>
deque<T, Allocator>::deque(const deque& other)
    : alloc_(other.alloc_), buf_(nullptr), cap_(0), start_(0), size_(0) {
    ensure_capacity(other.size_);
    for (size_type i = 0; i < other.size_; ++i) {
        alloc_.construct(buf_ + i, other.buf_[other.index_at(i)]);
    }
    size_ = other.size_;
}

template <typename T, typename Allocator>
deque<T, Allocator>::deque(deque&& other) noexcept
    : alloc_(std::move(other.alloc_)),
      buf_(other.buf_), cap_(other.cap_), start_(other.start_), size_(other.size_) {
    other.buf_ = nullptr;
    other.cap_ = other.start_ = other.size_ = 0;
}

template <typename T, typename Allocator>
deque<T, Allocator>::deque(std::initializer_list<T> init, const Allocator& alloc)
    : alloc_(alloc), buf_(nullptr), cap_(0), start_(0), size_(0) {
    for (const auto& v : init) push_back(v);
}

template <typename T, typename Allocator>
deque<T, Allocator>::~deque() {
    clear();
    if (buf_) alloc_.deallocate(buf_, cap_);
}

template <typename T, typename Allocator>
deque<T, Allocator>& deque<T, Allocator>::operator=(const deque& other) {
    if (this != &other) assign(other.begin(), other.end());
    return *this;
}

template <typename T, typename Allocator>
deque<T, Allocator>& deque<T, Allocator>::operator=(deque&& other) noexcept {
    if (this != &other) {
        clear();
        if (buf_) alloc_.deallocate(buf_, cap_);
        buf_ = other.buf_; cap_ = other.cap_; start_ = other.start_; size_ = other.size_;
        other.buf_ = nullptr; other.cap_ = other.start_ = other.size_ = 0;
    }
    return *this;
}

template <typename T, typename Allocator>
deque<T, Allocator>& deque<T, Allocator>::operator=(std::initializer_list<T> init) {
    assign(init);
    return *this;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::assign(size_type count, const T& value) {
    clear();
    ensure_capacity(count);
    for (size_type i = 0; i < count; ++i) alloc_.construct(buf_ + i, value);
    size_ = count;
}

template <typename T, typename Allocator>
template <typename InputIt>
void deque<T, Allocator>::assign(InputIt first, InputIt last) {
    clear();
    for (; first != last; ++first) push_back(*first);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::assign(std::initializer_list<T> init) {
    clear();
    for (const auto& v : init) push_back(v);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::reference deque<T, Allocator>::at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("deque::at");
    return buf_[index_at(pos)];
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_reference deque<T, Allocator>::at(size_type pos) const {
    if (pos >= size_) throw std::out_of_range("deque::at");
    return buf_[index_at(pos)];
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::begin() {
    return iterator(buf_, start_, cap_, start_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator deque<T, Allocator>::begin() const {
    return const_iterator(buf_, start_, cap_, start_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cbegin() const {
    return const_iterator(buf_, start_, cap_, start_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::end() {
    return iterator(buf_, index_at(size_), cap_, start_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator deque<T, Allocator>::end() const {
    return const_iterator(buf_, index_at(size_), cap_, start_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cend() const {
    return const_iterator(buf_, index_at(size_), cap_, start_);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::shrink_to_fit() {
    if (size_ < cap_) reallocate(size_);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::clear() {
    for (size_type i = 0; i < size_; ++i) alloc_.destroy(buf_ + index_at(i));
    size_ = 0;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator pos, const T& value) {
    return insert(pos, size_type(1), value);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator pos, T&& value) {
    size_type at_pos = pos.logical_index();
    if (at_pos >= size_) {
        push_back(std::move(value));
        return end() - 1;
    }
    if (at_pos == 0) {
        push_front(std::move(value));
        return begin();
    }
    ensure_capacity(size_ + 1);
    if (start_ != 0 || size_ == cap_) reallocate(cap_);
    for (size_type i = size_; i > at_pos; --i) {
        alloc_.construct(buf_ + i, std::move(buf_[i - 1]));
        alloc_.destroy(buf_ + (i - 1));
    }
    alloc_.construct(buf_ + at_pos, std::move(value));
    ++size_;
    return iterator(buf_, at_pos, cap_, 0);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator pos, size_type count, const T& value) {
    if (count == 0) return iterator(buf_, pos.position(), cap_, start_);
    size_type at_pos = pos.logical_index();
    for (size_type i = 0; i < count; ++i) {
        insert(begin() + at_pos + i, value);
    }
    return iterator(buf_, index_at(at_pos), cap_, start_);
}

template <typename T, typename Allocator>
template <typename InputIt>
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
    size_type at_pos = pos.logical_index();
    while (first != last) {
        insert(begin() + at_pos, *first);
        ++at_pos; ++first;
    }
    return iterator(buf_, index_at(at_pos), cap_, start_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> init) {
    return insert(pos, init.begin(), init.end());
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::erase(const_iterator pos) {
    size_type at_pos = (pos.position() - start_ + cap_) % cap_;
    for (size_type i = at_pos; i < size_ - 1; ++i) (*this)[i] = std::move((*this)[i + 1]);
    pop_back();
    return iterator(buf_, index_at(at_pos), cap_);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator deque<T, Allocator>::erase(const_iterator first, const_iterator last) {
    size_type n = last - first;
    size_type at_pos = first.logical_index();
    for (size_type i = 0; i < n; ++i) erase(begin() + at_pos);
    return iterator(buf_, index_at(at_pos), cap_, start_);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::push_back(const T& value) {
    ensure_capacity(size_ + 1);
    alloc_.construct(buf_ + index_at(size_), value);
    ++size_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::push_back(T&& value) {
    ensure_capacity(size_ + 1);
    alloc_.construct(buf_ + index_at(size_), std::move(value));
    ++size_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::push_front(const T& value) {
    ensure_capacity(size_ + 1);
    start_ = (start_ + cap_ - 1) % cap_;
    alloc_.construct(buf_ + start_, value);
    ++size_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::push_front(T&& value) {
    ensure_capacity(size_ + 1);
    start_ = (start_ + cap_ - 1) % cap_;
    alloc_.construct(buf_ + start_, std::move(value));
    ++size_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::pop_back() {
    alloc_.destroy(buf_ + index_at(size_ - 1));
    --size_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::pop_front() {
    alloc_.destroy(buf_ + start_);
    start_ = (start_ + 1) % cap_;
    --size_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::resize(size_type count, const value_type& value) {
    while (size_ > count) pop_back();
    while (size_ < count) push_back(value);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::swap(deque& other) noexcept {
    std::swap(buf_, other.buf_);
    std::swap(cap_, other.cap_);
    std::swap(start_, other.start_);
    std::swap(size_, other.size_);
}

} // namespace miniSTL

#endif // MINISTL_DEQUE_H
