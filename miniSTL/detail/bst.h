#ifndef MINISTL_DETAIL_BST_H
#define MINISTL_DETAIL_BST_H

#include <cstddef>
#include <memory>

namespace miniSTL {
namespace detail {

template <typename T, typename Compare, typename Allocator, bool AllowDuplicate>
class bst {
public:
    using value_type     = T;
    using size_type      = std::size_t;
    using value_compare  = Compare;
    using allocator_type = Allocator;

    struct node {
        node* left;
        node* right;
        node* parent;
        value_type value;
        node(const value_type& v) : left(nullptr), right(nullptr), parent(nullptr), value(v) {}
        node(value_type&& v) : left(nullptr), right(nullptr), parent(nullptr), value(std::move(v)) {}
    };

    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<node>;

    class iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() : ptr_(nullptr) {}
        explicit iterator(node* p) : ptr_(p) {}

        reference operator*() const { return ptr_->value; }
        pointer operator->() const { return &ptr_->value; }
        node* base() const { return ptr_; }

        iterator& operator++() {
            if (ptr_->right) {
                ptr_ = ptr_->right;
                while (ptr_->left) ptr_ = ptr_->left;
            } else {
                node* p = ptr_->parent;
                while (p && ptr_ == p->right) { ptr_ = p; p = p->parent; }
                ptr_ = p;
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++*this; return tmp; }
        iterator& operator--() {
            if (ptr_->left) {
                ptr_ = ptr_->left;
                while (ptr_->right) ptr_ = ptr_->right;
            } else {
                node* p = ptr_->parent;
                while (p && ptr_ == p->left) { ptr_ = p; p = p->parent; }
                ptr_ = p;
            }
            return *this;
        }
        iterator operator--(int) { iterator tmp = *this; --*this; return tmp; }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

    private:
        node* ptr_;
    };

    class const_iterator {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator() : ptr_(nullptr) {}
        explicit const_iterator(const node* p) : ptr_(p) {}
        const_iterator(const iterator& it) : ptr_(it.base()) {}

        reference operator*() const { return ptr_->value; }
        pointer operator->() const { return &ptr_->value; }

        const_iterator& operator++() {
            if (ptr_->right) {
                ptr_ = ptr_->right;
                while (ptr_->left) ptr_ = ptr_->left;
            } else {
                const node* p = ptr_->parent;
                while (p && ptr_ == p->right) { ptr_ = p; p = p->parent; }
                ptr_ = p;
            }
            return *this;
        }
        const_iterator operator++(int) { const_iterator tmp = *this; ++*this; return tmp; }
        const_iterator& operator--() {
            if (ptr_->left) {
                ptr_ = ptr_->left;
                while (ptr_->right) ptr_ = ptr_->right;
            } else {
                const node* p = ptr_->parent;
                while (p && ptr_ == p->left) { ptr_ = p; p = p->parent; }
                ptr_ = p;
            }
            return *this;
        }
        const_iterator operator--(int) { const_iterator tmp = *this; --*this; return tmp; }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
        const node* base() const { return ptr_; }

    private:
        const node* ptr_;
    };

    bst() : root_(nullptr), size_(0), comp_(), alloc_() {}
    explicit bst(const Compare& comp, const Allocator& alloc = Allocator())
        : root_(nullptr), size_(0), comp_(comp), alloc_(alloc) {}

    ~bst() { clear(); }

    bst(const bst&) = delete;
    bst& operator=(const bst&) = delete;

    size_type size() const { return size_; }
    bool empty() const { return size_ == 0; }
    allocator_type get_allocator() const { return alloc_; }
    value_compare value_comp() const { return comp_; }

    iterator begin() {
        if (!root_) return iterator(nullptr);
        node* p = root_;
        while (p->left) p = p->left;
        return iterator(p);
    }
    const_iterator begin() const {
        if (!root_) return const_iterator(nullptr);
        const node* p = root_;
        while (p->left) p = p->left;
        return const_iterator(p);
    }
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }

    std::pair<iterator, bool> insert_unique(const value_type& value) {
        node* parent = nullptr;
        node* cur = root_;
        while (cur) {
            parent = cur;
            if (comp_(value, cur->value)) cur = cur->left;
            else if (comp_(cur->value, value)) cur = cur->right;
            else return {iterator(cur), false};
        }
        node* z = create_node(value);
        z->parent = parent;
        if (!parent) root_ = z;
        else if (comp_(value, parent->value)) parent->left = z;
        else parent->right = z;
        ++size_;
        return {iterator(z), true};
    }

    std::pair<iterator, bool> insert_unique(value_type&& value) {
        node* parent = nullptr;
        node* cur = root_;
        while (cur) {
            parent = cur;
            if (comp_(value, cur->value)) cur = cur->left;
            else if (comp_(cur->value, value)) cur = cur->right;
            else return {iterator(cur), false};
        }
        node* z = create_node(std::move(value));
        z->parent = parent;
        if (!parent) root_ = z;
        else if (comp_(z->value, parent->value)) parent->left = z;
        else parent->right = z;
        ++size_;
        return {iterator(z), true};
    }

    iterator insert_multi(const value_type& value) {
        node* parent = nullptr;
        node* cur = root_;
        while (cur) {
            parent = cur;
            if (comp_(value, cur->value)) cur = cur->left;
            else cur = cur->right;
        }
        node* z = create_node(value);
        z->parent = parent;
        if (!parent) root_ = z;
        else if (comp_(value, parent->value)) parent->left = z;
        else parent->right = z;
        ++size_;
        return iterator(z);
    }

    iterator insert_multi(value_type&& value) {
        node* parent = nullptr;
        node* cur = root_;
        while (cur) {
            parent = cur;
            if (comp_(value, cur->value)) cur = cur->left;
            else cur = cur->right;
        }
        node* z = create_node(std::move(value));
        z->parent = parent;
        if (!parent) root_ = z;
        else if (comp_(z->value, parent->value)) parent->left = z;
        else parent->right = z;
        ++size_;
        return iterator(z);
    }

    iterator find(const value_type& value) {
        node* cur = root_;
        while (cur) {
            if (comp_(value, cur->value)) cur = cur->left;
            else if (comp_(cur->value, value)) cur = cur->right;
            else return iterator(cur);
        }
        return end();
    }
    const_iterator find(const value_type& value) const {
        const node* cur = root_;
        while (cur) {
            if (comp_(value, cur->value)) cur = cur->left;
            else if (comp_(cur->value, value)) cur = cur->right;
            else return const_iterator(cur);
        }
        return end();
    }
    template <typename K, typename KeyOfValue>
    iterator find_key(const K& key, KeyOfValue key_of_value) {
        node* cur = root_;
        while (cur) {
            if (comp_(key, key_of_value(cur->value))) cur = cur->left;
            else if (comp_(key_of_value(cur->value), key)) cur = cur->right;
            else return iterator(cur);
        }
        return end();
    }
    template <typename K, typename KeyOfValue>
    const_iterator find_key(const K& key, KeyOfValue key_of_value) const {
        const node* cur = root_;
        while (cur) {
            if (comp_(key, key_of_value(cur->value))) cur = cur->left;
            else if (comp_(key_of_value(cur->value), key)) cur = cur->right;
            else return const_iterator(cur);
        }
        return end();
    }
    template <typename K, typename KeyOfValue>
    iterator find_key(const K& key, KeyOfValue key_of_value) {
        node* cur = root_;
        while (cur) {
            if (comp_(key, key_of_value(cur->value))) cur = cur->left;
            else if (comp_(key_of_value(cur->value), key)) cur = cur->right;
            else return iterator(cur);
        }
        return end();
    }
    template <typename K, typename KeyOfValue>
    const_iterator find_key(const K& key, KeyOfValue key_of_value) const {
        const node* cur = root_;
        while (cur) {
            if (comp_(key, key_of_value(cur->value))) cur = cur->left;
            else if (comp_(key_of_value(cur->value), key)) cur = cur->right;
            else return const_iterator(cur);
        }
        return end();
    }

    size_type count(const value_type& value) const {
        size_type n = 0;
        const node* cur = root_;
        while (cur) {
            if (comp_(value, cur->value)) cur = cur->left;
            else if (comp_(cur->value, value)) cur = cur->right;
            else { ++n; cur = cur->right; }
        }
        return n;
    }

    void erase(const_iterator pos) {
        if (pos == end()) return;
        erase(iterator(const_cast<node*>(pos.base())));
    }
    void erase(iterator pos) {
        if (pos == end()) return;
        node* z = pos.base();
        node* y = z;
        node* x = nullptr;
        if (!z->left) x = z->right;
        else if (!z->right) x = z->left;
        else {
            y = z->right;
            while (y->left) y = y->left;
            x = y->right;
        }
        if (y != z) {
            z->value = std::move(y->value);
            if (y->parent->left == y) y->parent->left = x;
            else y->parent->right = x;
            if (x) x->parent = y->parent;
            destroy_node(y);
        } else {
            if (z->parent) {
                if (z->parent->left == z) z->parent->left = x;
                else z->parent->right = x;
            } else root_ = x;
            if (x) x->parent = z->parent;
            destroy_node(z);
        }
        --size_;
    }

    size_type erase(const value_type& value) {
        iterator it = find(value);
        if (it == end()) return 0;
        erase(it);
        return 1;
    }

    void clear() {
        clear_sub(root_);
        root_ = nullptr;
        size_ = 0;
    }

private:
    node* root_;
    size_type size_;
    Compare comp_;
    node_allocator alloc_;

    node* create_node(const value_type& value) {
        node* p = alloc_.allocate(1);
        alloc_.construct(p, value);
        return p;
    }
    node* create_node(value_type&& value) {
        node* p = alloc_.allocate(1);
        alloc_.construct(p, std::move(value));
        return p;
    }
    void destroy_node(node* p) {
        alloc_.destroy(p);
        alloc_.deallocate(p, 1);
    }
    void clear_sub(node* p) {
        if (!p) return;
        clear_sub(p->left);
        clear_sub(p->right);
        destroy_node(p);
    }
};

} // namespace detail
} // namespace miniSTL

#endif // MINISTL_DETAIL_BST_H
