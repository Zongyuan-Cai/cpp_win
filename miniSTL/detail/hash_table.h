#ifndef MINISTL_DETAIL_HASH_TABLE_H
#define MINISTL_DETAIL_HASH_TABLE_H

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

namespace miniSTL {
namespace detail {

template <typename Key, typename Value, typename KeyOfValue, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>, typename Allocator = std::allocator<Value>>
class hash_table {
public:
    using key_type    = Key;
    using value_type  = Value;
    using size_type   = std::size_t;
    using hasher      = Hash;
    using key_equal   = KeyEqual;
    using allocator_type = Allocator;

    struct node {
        value_type value;
        node* next;
        node(const value_type& v, node* n = nullptr) : value(v), next(n) {}
        node(value_type&& v, node* n = nullptr) : value(std::move(v)), next(n) {}
    };
    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<node>;

    class iterator {
    public:
        using value_type        = Value;
        using difference_type   = std::ptrdiff_t;
        using pointer           = Value*;
        using reference         = Value&;
        using iterator_category = std::forward_iterator_tag;

        iterator() : cur_(nullptr), ht_(nullptr) {}
        iterator(node* n, hash_table* ht) : cur_(n), ht_(ht) {}

        reference operator*() const { return cur_->value; }
        pointer operator->() const { return &cur_->value; }
        iterator& operator++() {
            if (cur_->next) cur_ = cur_->next;
            else {
                size_type i = ht_->bucket_index(cur_) + 1;
                for (; i < ht_->buckets_.size() && !ht_->buckets_[i]; ++i) {}
                cur_ = i < ht_->buckets_.size() ? ht_->buckets_[i] : nullptr;
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++*this; return tmp; }
        bool operator==(const iterator& other) const { return cur_ == other.cur_; }
        bool operator!=(const iterator& other) const { return cur_ != other.cur_; }
        node* base() const { return cur_; }

    private:
        node* cur_;
        hash_table* ht_;
    };

    class const_iterator {
    public:
        using value_type        = Value;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const Value*;
        using reference         = const Value&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() : cur_(nullptr), ht_(nullptr) {}
        const_iterator(const node* n, const hash_table* ht) : cur_(n), ht_(ht) {}
        const_iterator(const iterator& it) : cur_(it.base()), ht_(it.ht_) {}

        reference operator*() const { return cur_->value; }
        pointer operator->() const { return &cur_->value; }
        const_iterator& operator++() {
            if (cur_->next) cur_ = cur_->next;
            else {
                size_type i = ht_->bucket_index(cur_) + 1;
                for (; i < ht_->buckets_.size() && !ht_->buckets_[i]; ++i) {}
                cur_ = i < ht_->buckets_.size() ? ht_->buckets_[i] : nullptr;
            }
            return *this;
        }
        const_iterator operator++(int) { const_iterator tmp = *this; ++*this; return tmp; }
        bool operator==(const const_iterator& other) const { return cur_ == other.cur_; }
        bool operator!=(const const_iterator& other) const { return cur_ != other.cur_; }
        const node* base() const { return cur_; }
        hash_table* mutable_ht() const { return const_cast<hash_table*>(ht_); }

    private:
        const node* cur_;
        const hash_table* ht_;
    };

    hash_table() : size_(0), load_factor_max_(1.0f), key_of_value_(), hash_(), eq_(), alloc_(), alloc_wrapper_() {
        buckets_.resize(11, nullptr);
    }
    explicit hash_table(size_type n, const Hash& hash = Hash(), const KeyEqual& eq = KeyEqual(),
                       const Allocator& alloc = Allocator(), const KeyOfValue& kv = KeyOfValue())
        : size_(0), load_factor_max_(1.0f), key_of_value_(kv), hash_(hash), eq_(eq), alloc_(alloc), alloc_wrapper_(alloc) {
        buckets_.resize(next_prime(n), nullptr);
    }

    ~hash_table() { clear(); }

    size_type size() const { return size_; }
    bool empty() const { return size_ == 0; }
    allocator_type get_allocator() const { return alloc_wrapper_; }
    key_equal key_eq() const { return eq_; }
    iterator begin() {
        for (size_type i = 0; i < buckets_.size(); ++i)
            if (buckets_[i]) return iterator(buckets_[i], this);
        return end();
    }
    const_iterator begin() const {
        for (size_type i = 0; i < buckets_.size(); ++i)
            if (buckets_[i]) return const_iterator(buckets_[i], this);
        return end();
    }
    iterator end() { return iterator(nullptr, this); }
    const_iterator end() const { return const_iterator(nullptr, this); }

    void clear() {
        for (size_type i = 0; i < buckets_.size(); ++i) {
            node* p = buckets_[i];
            while (p) {
                node* next = p->next;
                destroy_node(p);
                p = next;
            }
            buckets_[i] = nullptr;
        }
        size_ = 0;
    }

    std::pair<iterator, bool> insert_unique(const value_type& value) {
        rehash_if_needed();
        size_type i = bucket(key_of_value_(value));
        for (node* p = buckets_[i]; p; p = p->next)
            if (eq_(key_of_value_(p->value), key_of_value_(value))) return {iterator(p, this), false};
        node* n = create_node(value);
        n->next = buckets_[i];
        buckets_[i] = n;
        ++size_;
        return {iterator(n, this), true};
    }
    iterator insert_multi(const value_type& value) {
        rehash_if_needed();
        size_type i = bucket(key_of_value_(value));
        node* n = create_node(value);
        n->next = buckets_[i];
        buckets_[i] = n;
        ++size_;
        return iterator(n, this);
    }
    iterator find_key(const Key& key) {
        size_type i = bucket(key);
        for (node* p = buckets_[i]; p; p = p->next)
            if (eq_(key_of_value_(p->value), key)) return iterator(p, this);
        return end();
    }
    const_iterator find_key(const Key& key) const {
        size_type i = bucket(key);
        for (const node* p = buckets_[i]; p; p = p->next)
            if (eq_(key_of_value_(p->value), key)) return const_iterator(p, this);
        return end();
    }
    size_type erase_key(const Key& key) {
        size_type i = bucket(key);
        node* prev = nullptr;
        node* p = buckets_[i];
        while (p) {
            if (eq_(key_of_value_(p->value), key)) {
                if (prev) prev->next = p->next;
                else buckets_[i] = p->next;
                node* to_del = p;
                p = p->next;
                destroy_node(to_del);
                --size_;
                return 1;
            }
            prev = p;
            p = p->next;
        }
        return 0;
    }
    void erase(const_iterator pos) {
        erase(iterator(const_cast<node*>(pos.base()), pos.mutable_ht()));
    }
    void erase(iterator pos) {
        node* n = pos.base();
        size_type i = bucket_index(n);
        node* prev = nullptr;
        node* p = buckets_[i];
        while (p != n) { prev = p; p = p->next; }
        if (prev) prev->next = n->next;
        else buckets_[i] = n->next;
        destroy_node(n);
        --size_;
    }

    size_type bucket_count() const { return buckets_.size(); }
    size_type bucket(const Key& key) const { return hash_(key) % buckets_.size(); }

private:
    std::vector<node*> buckets_;
    size_type size_;
    float load_factor_max_;
    KeyOfValue key_of_value_;
    hasher hash_;
    key_equal eq_;
    node_allocator alloc_;
    allocator_type alloc_wrapper_;

    size_type bucket_index(node* n) const {
        return hash_(key_of_value_(n->value)) % buckets_.size();
    }
    static size_type next_prime(size_type n) {
        if (n <= 11) return 11;
        n |= 1;
        while (true) {
            bool ok = true;
            for (size_type i = 3; i * i <= n; i += 2) if (n % i == 0) { ok = false; break; }
            if (ok) return n;
            n += 2;
        }
    }
    void rehash_if_needed() {
        if (size_ + 1 <= buckets_.size() * load_factor_max_) return;
        size_type new_cap = next_prime(buckets_.size() * 2);
        std::vector<node*> new_buckets(new_cap, nullptr);
        for (size_type i = 0; i < buckets_.size(); ++i) {
            node* p = buckets_[i];
            while (p) {
                node* next = p->next;
                size_type j = hash_(key_of_value_(p->value)) % new_cap;
                p->next = new_buckets[j];
                new_buckets[j] = p;
                p = next;
            }
        }
        buckets_ = std::move(new_buckets);
    }
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
};

} // namespace detail
} // namespace miniSTL

#endif // MINISTL_DETAIL_HASH_TABLE_H
