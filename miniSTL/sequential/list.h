#ifndef MINISTL_LIST_H
#define MINISTL_LIST_H

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <initializer_list>

namespace miniSTL {

template <typename T, typename Allocator = std::allocator<T>>
class list {
public:
    using value_type             = T;
    using allocator_type         = Allocator;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;

    struct node_base {
        node_base* prev;
        node_base* next;
        node_base() : prev(this), next(this) {}
    };

    struct node : node_base {
        T value;
        node(const T& v) : value(v) {}
        node(T&& v) : value(std::move(v)) {}
        template <typename... Args>
        node(Args&&... args) : value(std::forward<Args>(args)...) {}//多个参数构造成一个节点
    };

    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<node>;
    //将T的allocator转成node的allocator
    class iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() : ptr_(nullptr) {}
        explicit iterator(node_base* p) : ptr_(p) {}

        reference operator*() const { return static_cast<node*>(ptr_)->value; }
        pointer operator->() const { return &static_cast<node*>(ptr_)->value; }

        iterator& operator++() { ptr_ = ptr_->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; ptr_ = ptr_->next; return tmp; }
        iterator& operator--() { ptr_ = ptr_->prev; return *this; }
        iterator operator--(int) { iterator tmp = *this; ptr_ = ptr_->prev; return tmp; }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

        node_base* base() const { return ptr_; }

    private:
        node_base* ptr_;
    };

    class const_iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator() : ptr_(nullptr) {}
        explicit const_iterator(const node_base* p) : ptr_(p) {}
        const_iterator(const iterator& it) : ptr_(it.base()) {}

        reference operator*() const { return static_cast<const node*>(ptr_)->value; }
        pointer operator->() const { return &static_cast<const node*>(ptr_)->value; }

        const_iterator& operator++() { ptr_ = ptr_->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ptr_ = ptr_->next; return tmp; }
        const_iterator& operator--() { ptr_ = ptr_->prev; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; ptr_ = ptr_->prev; return tmp; }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }

        const node_base* base() const { return ptr_; }

    private:
        const node_base* ptr_;
    };

    list() : alloc_(), node_alloc_(), size_(0) { head_.prev = head_.next = &head_; }
    explicit list(const Allocator& alloc) : alloc_(alloc), node_alloc_(alloc), size_(0) { head_.prev = head_.next = &head_; }
    list(size_type count, const T& value, const Allocator& alloc = Allocator());
    explicit list(size_type count, const Allocator& alloc = Allocator());
    template <typename InputIt>
    list(InputIt first, InputIt last, const Allocator& alloc = Allocator());
    list(const list& other);
    list(list&& other) noexcept;
    list(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    ~list();

    list& operator=(const list& other);
    list& operator=(list&& other) noexcept;
    list& operator=(std::initializer_list<T> init);

    void assign(size_type count, const T& value);
    template <typename InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> init);

    allocator_type get_allocator() const { return alloc_; }

    reference front() { return static_cast<node*>(head_.next)->value; }
    const_reference front() const { return static_cast<const node*>(head_.next)->value; }
    reference back() { return static_cast<node*>(head_.prev)->value; }
    const_reference back() const { return static_cast<const node*>(head_.prev)->value; }

    iterator begin() { return iterator(head_.next); }
    const_iterator begin() const { return const_iterator(head_.next); }
    const_iterator cbegin() const { return const_iterator(head_.next); }
    iterator end() { return iterator(&head_); }
    const_iterator end() const { return const_iterator(&head_); }
    const_iterator cend() const { return const_iterator(&head_); }

    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    size_type max_size() const { return node_alloc_.max_size(); }

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
    void swap(list& other) noexcept;

private:
    Allocator alloc_;
    node_allocator node_alloc_;
    node_base head_;//头节点
    size_type size_;

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
    void link(node_base* pos, node* n) {
        n->next = pos;
        n->prev = pos->prev;
        pos->prev->next = n;
        pos->prev = n;
    }
    void unlink(node_base* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    void destroy_node(node* p) {
        node_alloc_.destroy(p);
        node_alloc_.deallocate(p, 1);
    }
};

} // namespace miniSTL

namespace miniSTL {

template <typename T, typename Allocator>
list<T, Allocator>::list(size_type count, const T& value, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), size_(0) {
    head_.prev = head_.next = &head_;
    for (size_type i = 0; i < count; ++i) {
        link(&head_, create_node(value));
        ++size_;
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::list(size_type count, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), size_(0) {
    head_.prev = head_.next = &head_;
    for (size_type i = 0; i < count; ++i) {
        link(&head_, create_node(T()));
        ++size_;
    }
}

template <typename T, typename Allocator>
template <typename InputIt>
list<T, Allocator>::list(InputIt first, InputIt last, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), size_(0) {
    head_.prev = head_.next = &head_;
    for (; first != last; ++first) {
        link(&head_, create_node(*first));
        ++size_;
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::list(const list& other)
    : alloc_(other.alloc_), node_alloc_(other.node_alloc_), size_(0) {
    head_.prev = head_.next = &head_;
    for (const_iterator it = other.begin(); it != other.end(); ++it) {
        link(&head_, create_node(*it));
        ++size_;
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::list(list&& other) noexcept
    : alloc_(std::move(other.alloc_)), node_alloc_(std::move(other.node_alloc_)), size_(other.size_) {
    if (other.empty()) {
        head_.prev = head_.next = &head_;
    } else {
        head_.next = other.head_.next;
        head_.prev = other.head_.prev;
        head_.next->prev = head_.prev->next = &head_;
        other.head_.next = other.head_.prev = &other.head_;
        other.size_ = 0;
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::list(std::initializer_list<T> init, const Allocator& alloc)
    : alloc_(alloc), node_alloc_(alloc), size_(0) {
    head_.prev = head_.next = &head_;
    for (const auto& v : init) {
        link(&head_, create_node(v));
        ++size_;
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::~list() {
    clear();
}

template <typename T, typename Allocator>
list<T, Allocator>& list<T, Allocator>::operator=(const list& other) {
    if (this != &other) assign(other.begin(), other.end());
    return *this;
}

template <typename T, typename Allocator>
list<T, Allocator>& list<T, Allocator>::operator=(list&& other) noexcept {
    if (this != &other) {
        clear();
        if (!other.empty()) {
            head_.next = other.head_.next;
            head_.prev = other.head_.prev;
            head_.next->prev = head_.prev->next = &head_;
            other.head_.next = other.head_.prev = &other.head_;
            size_ = other.size_;
            other.size_ = 0;
        }
    }
    return *this;
}

template <typename T, typename Allocator>
list<T, Allocator>& list<T, Allocator>::operator=(std::initializer_list<T> init) {
    assign(init);
    return *this;
}

template <typename T, typename Allocator>
void list<T, Allocator>::assign(size_type count, const T& value) {
    clear();
    for (size_type i = 0; i < count; ++i) {
        link(&head_, create_node(value));
        ++size_;
    }
}

template <typename T, typename Allocator>
template <typename InputIt>
void list<T, Allocator>::assign(InputIt first, InputIt last) {
    clear();
    for (; first != last; ++first) {
        link(&head_, create_node(*first));
        ++size_;
    }
}

template <typename T, typename Allocator>
void list<T, Allocator>::assign(std::initializer_list<T> init) {
    clear();
    for (const auto& v : init) {
        link(&head_, create_node(v));
        ++size_;
    }
}

template <typename T, typename Allocator>
void list<T, Allocator>::clear() {
    while (!empty()) {
        node* p = static_cast<node*>(head_.next);
        unlink(p);
        destroy_node(p);
        --size_;
    }
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, const T& value) {
    node* n = create_node(value);
    link(const_cast<node_base*>(pos.base()), n);
    ++size_;
    return iterator(n);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, T&& value) {
    node* n = create_node(std::move(value));
    link(const_cast<node_base*>(pos.base()), n);
    ++size_;
    return iterator(n);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, size_type count, const T& value) {
    if (count == 0) return iterator(const_cast<node_base*>(pos.base()));
    iterator first = insert(pos, value);
    for (size_type i = 1; i < count; ++i) insert(pos, value);
    return first;
}

template <typename T, typename Allocator>
template <typename InputIt>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
    iterator result(const_cast<node_base*>(pos.base()));
    for (; first != last; ++first) {
        result = insert(pos, *first);
    }
    return result;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> init) {
    return insert(pos, init.begin(), init.end());
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator pos) {
    node_base* next = pos.base()->next;
    node* p = static_cast<node*>(const_cast<node_base*>(pos.base()));
    unlink(p);
    destroy_node(p);
    --size_;
    return iterator(next);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator first, const_iterator last) {
    iterator result(const_cast<node_base*>(last.base()));
    while (first != last) {
        iterator to_erase = iterator(const_cast<node_base*>(first.base()));
        ++first;
        erase(to_erase);
    }
    return result;
}

template <typename T, typename Allocator>
void list<T, Allocator>::push_back(const T& value) {
    link(&head_, create_node(value));
    ++size_;
}

template <typename T, typename Allocator>
void list<T, Allocator>::push_back(T&& value) {
    link(&head_, create_node(std::move(value)));
    ++size_;
}

template <typename T, typename Allocator>
void list<T, Allocator>::push_front(const T& value) {
    link(head_.next, create_node(value));
    ++size_;
}

template <typename T, typename Allocator>
void list<T, Allocator>::push_front(T&& value) {
    link(head_.next, create_node(std::move(value)));
    ++size_;
}

template <typename T, typename Allocator>
void list<T, Allocator>::pop_back() {
    node* p = static_cast<node*>(head_.prev);
    unlink(p);
    destroy_node(p);
    --size_;
}

template <typename T, typename Allocator>
void list<T, Allocator>::pop_front() {
    node* p = static_cast<node*>(head_.next);
    unlink(p);
    destroy_node(p);
    --size_;
}

template <typename T, typename Allocator>
void list<T, Allocator>::resize(size_type count, const value_type& value) {
    while (size_ > count) pop_back();
    while (size_ < count) push_back(value);
}

template <typename T, typename Allocator>
void list<T, Allocator>::swap(list& other) noexcept {
    std::swap(head_.next, other.head_.next);
    std::swap(head_.prev, other.head_.prev);
    head_.next->prev = head_.prev->next = &head_;
    other.head_.next->prev = other.head_.prev->next = &other.head_;
    std::swap(size_, other.size_);
}

} // namespace miniSTL

#endif // MINISTL_LIST_H
