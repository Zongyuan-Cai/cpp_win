#ifndef MINISTL_FORWARD_LIST_H
#define MINISTL_FORWARD_LIST_H

#include <cstddef>
#include <memory>
#include <initializer_list>

namespace miniSTL {

template <typename T, typename Allocator = std::allocator<T>>
class forward_list {
public:
    using value_type             = T;
    using allocator_type         = Allocator;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;

    struct node {
        node* next;
        T value;
        node(const T& v) : next(nullptr), value(v) {}
        node(T&& v) : next(nullptr), value(std::move(v)) {}
        template <typename... Args>
        node(Args&&... args) : next(nullptr), value(std::forward<Args>(args)...) {}
    };

    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<node>;

    class iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::forward_iterator_tag;

        iterator() : ptr_(nullptr) {}
        explicit iterator(node* p) : ptr_(p) {}

        reference operator*() const { return ptr_->value; }
        pointer operator->() const { return &ptr_->value; }

        iterator& operator++() { ptr_ = ptr_->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; ptr_ = ptr_->next; return tmp; }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

        node* base() const { return ptr_; }

    private:
        node* ptr_;
    };

    class const_iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() : ptr_(nullptr) {}
        explicit const_iterator(const node* p) : ptr_(p) {}
        const_iterator(const iterator& it) : ptr_(it.base()) {}

        reference operator*() const { return ptr_->value; }
        pointer operator->() const { return &ptr_->value; }

        const_iterator& operator++() { ptr_ = ptr_->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ptr_ = ptr_->next; return tmp; }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }

        const node* base() const { return ptr_; }

    private:
        const node* ptr_;
    };

    forward_list() : head_(nullptr), size_(0) {}
    explicit forward_list(const Allocator& alloc) : alloc_(alloc), node_alloc_(alloc), head_(nullptr), size_(0) {}
    forward_list(size_type count, const T& value, const Allocator& alloc = Allocator());
    explicit forward_list(size_type count, const Allocator& alloc = Allocator());
    template <typename InputIt>
    forward_list(InputIt first, InputIt last, const Allocator& alloc = Allocator());
    forward_list(const forward_list& other);
    forward_list(forward_list&& other) noexcept;
    forward_list(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    ~forward_list();

    forward_list& operator=(const forward_list& other);
    forward_list& operator=(forward_list&& other) noexcept;
    forward_list& operator=(std::initializer_list<T> init);

    void assign(size_type count, const T& value);
    template <typename InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> init);

    allocator_type get_allocator() const { return alloc_; }

    reference front() { return head_->value; }
    const_reference front() const { return head_->value; }

    iterator before_begin() { return iterator(&dummy_); }
    const_iterator before_begin() const { return const_iterator(&dummy_); }
    const_iterator cbefore_begin() const { return const_iterator(&dummy_); }
    iterator begin() { return iterator(head_); }
    const_iterator begin() const { return const_iterator(head_); }
    const_iterator cbegin() const { return const_iterator(head_); }
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }
    const_iterator cend() const { return const_iterator(nullptr); }

    bool empty() const { return head_ == nullptr; }
    size_type size() const { return size_; }
    size_type max_size() const { return node_alloc_.max_size(); }

    void clear();
    iterator insert_after(const_iterator pos, const T& value);
    iterator insert_after(const_iterator pos, T&& value);
    iterator insert_after(const_iterator pos, size_type count, const T& value);
    template <typename InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);
    iterator insert_after(const_iterator pos, std::initializer_list<T> init);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
    void resize(size_type count, const value_type& value = value_type());
    void swap(forward_list& other) noexcept;

private:
    Allocator alloc_;
    node_allocator node_alloc_;
    node dummy_;
    node* head_;
    size_type size_;

    node* dummy_next() { return dummy_.next; }
    const node* dummy_next() const { return dummy_.next; }
    void set_dummy_next(node* p) { dummy_.next = p; }

    node* create_node(const T& value) {
        node* p = node_alloc_.allocate(1);
        node_alloc_.construct(p, value);
        return p;
    }
    node* create_node(T&& value) {
        node* p = node_alloc_.allocate(1);
        node_alloc_.construct(p, std::move(value));
        return p;
    }
    void destroy_node(node* p) {
        node_alloc_.destroy(p);
        node_alloc_.deallocate(p, 1);
    }
};

} // namespace miniSTL

namespace miniSTL {

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list(size_type count, const T& value, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), head_(nullptr), size_(0) {
    dummy_.next = nullptr;
    node* tail = &dummy_;
    for (size_type i = 0; i < count; ++i) {
        node* n = create_node(value);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_next();
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list(size_type count, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), head_(nullptr), size_(0) {
    dummy_.next = nullptr;
    node* tail = &dummy_;
    for (size_type i = 0; i < count; ++i) {
        node* n = create_node(T());
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_next();
}

template <typename T, typename Allocator>
template <typename InputIt>
forward_list<T, Allocator>::forward_list(InputIt first, InputIt last, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), head_(nullptr), size_(0) {
    dummy_.next = nullptr;
    node* tail = &dummy_;
    for (; first != last; ++first) {
        node* n = create_node(*first);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_next();
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list(const forward_list& other)
    : alloc_(other.alloc_), node_alloc_(other.node_alloc_), head_(nullptr), size_(0) {
    dummy_.next = nullptr;
    node* tail = &dummy_;
    for (const_iterator it = other.begin(); it != other.end(); ++it) {
        node* n = create_node(*it);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_next();
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list(forward_list&& other) noexcept
    : alloc_(std::move(other.alloc_)), node_alloc_(std::move(other.node_alloc_)),
      head_(other.head_), size_(other.size_) {
    dummy_.next = other.dummy_next();
    other.dummy_.next = nullptr;
    other.head_ = nullptr;
    other.size_ = 0;
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list(std::initializer_list<T> init, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), head_(nullptr), size_(0) {
    dummy_.next = nullptr;
    node* tail = &dummy_;
    for (const auto& v : init) {
        node* n = create_node(v);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_next();
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::~forward_list() {
    clear();
}

template <typename T, typename Allocator>
forward_list<T, Allocator>& forward_list<T, Allocator>::operator=(const forward_list& other) {
    if (this != &other) assign(other.begin(), other.end());
    return *this;
}

template <typename T, typename Allocator>
forward_list<T, Allocator>& forward_list<T, Allocator>::operator=(forward_list&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        dummy_.next = other.dummy_next();
        size_ = other.size_;
        other.head_ = nullptr;
        other.dummy_.next = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T, typename Allocator>
forward_list<T, Allocator>& forward_list<T, Allocator>::operator=(std::initializer_list<T> init) {
    assign(init);
    return *this;
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::assign(size_type count, const T& value) {
    clear();
    node* tail = &dummy_;
    for (size_type i = 0; i < count; ++i) {
        node* n = create_node(value);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_.next;
}

template <typename T, typename Allocator>
template <typename InputIt>
void forward_list<T, Allocator>::assign(InputIt first, InputIt last) {
    clear();
    node* tail = &dummy_;
    for (; first != last; ++first) {
        node* n = create_node(*first);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_.next;
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::assign(std::initializer_list<T> init) {
    clear();
    node* tail = &dummy_;
    for (const auto& v : init) {
        node* n = create_node(v);
        tail->next = n;
        tail = n;
        ++size_;
    }
    head_ = dummy_.next;
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::clear() {
    while (head_) {
        node* p = head_;
        head_ = head_->next;
        destroy_node(p);
    }
    dummy_.next = nullptr;
    size_ = 0;
}

template <typename T, typename Allocator>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert_after(const_iterator pos, const T& value) {
    node* n = create_node(value);
    node* prev = const_cast<node*>(pos.base());
    n->next = prev->next;
    prev->next = n;
    if (prev == &dummy_) head_ = n;
    ++size_;
    return iterator(n);
}

template <typename T, typename Allocator>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert_after(const_iterator pos, T&& value) {
    node* n = create_node(std::move(value));
    node* prev = const_cast<node*>(pos.base());
    n->next = prev->next;
    prev->next = n;
    if (prev == &dummy_) head_ = n;
    ++size_;
    return iterator(n);
}

template <typename T, typename Allocator>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert_after(const_iterator pos, size_type count, const T& value) {
    iterator result(const_cast<node*>(pos.base()));
    for (size_type i = 0; i < count; ++i) {
        insert_after(pos, value);
    }
    return result;
}

template <typename T, typename Allocator>
template <typename InputIt>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert_after(const_iterator pos, InputIt first, InputIt last) {
    for (; first != last; ++first) {
        pos = const_iterator(insert_after(pos, *first).base());
    }
    return iterator(const_cast<node*>(pos.base())->next);
}

template <typename T, typename Allocator>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert_after(const_iterator pos, std::initializer_list<T> init) {
    return insert_after(pos, init.begin(), init.end());
}

template <typename T, typename Allocator>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::erase_after(const_iterator pos) {
    node* prev = const_cast<node*>(pos.base());
    node* to_remove = prev->next;
    if (!to_remove) return end();
    prev->next = to_remove->next;
    if (head_ == to_remove) head_ = prev->next;
    destroy_node(to_remove);
    --size_;
    return iterator(prev->next);
}

template <typename T, typename Allocator>
typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::erase_after(const_iterator first, const_iterator last) {
    node* prev = const_cast<node*>(first.base());
    while (prev->next != last.base()) {
        erase_after(const_iterator(prev));
    }
    return iterator(const_cast<node*>(last.base()));
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::push_front(const T& value) {
    insert_after(cbefore_begin(), value);
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::push_front(T&& value) {
    insert_after(cbefore_begin(), std::move(value));
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::pop_front() {
    erase_after(cbefore_begin());
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::resize(size_type count, const value_type& value) {
    while (size_ > count) pop_front();
    while (size_ < count) push_front(value);
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::swap(forward_list& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(dummy_.next, other.dummy_.next);
    std::swap(size_, other.size_);
}

} // namespace miniSTL

#endif // MINISTL_FORWARD_LIST_H
