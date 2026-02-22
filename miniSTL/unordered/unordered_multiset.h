#ifndef MINISTL_UNORDERED_MULTISET_H
#define MINISTL_UNORDERED_MULTISET_H

#include <cstddef>
#include <functional>
#include <memory>
#include <initializer_list>
#include "../detail/hash_table.h"

namespace miniSTL {

template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<Key>>
class unordered_multiset {
public:
    using key_type    = Key;
    using value_type  = Key;
    using hasher      = Hash;
    using key_equal   = KeyEqual;
    using allocator_type = Allocator;
    using size_type   = std::size_t;

    struct identity {
        const Key& operator()(const Key& x) const { return x; }
    };
    using iterator       = typename detail::hash_table<Key, Key, identity, Hash, KeyEqual, Allocator>::const_iterator;
    using const_iterator = typename detail::hash_table<Key, Key, identity, Hash, KeyEqual, Allocator>::const_iterator;

    unordered_multiset() : table_() {}
    explicit unordered_multiset(size_type n, const Hash& hash = Hash(), const KeyEqual& eq = KeyEqual(),
                                const Allocator& alloc = Allocator())
        : table_(n, hash, eq, alloc, identity()) {}
    template <typename InputIt>
    unordered_multiset(InputIt first, InputIt last, size_type n = 0, const Hash& hash = Hash(),
                       const KeyEqual& eq = KeyEqual(), const Allocator& alloc = Allocator())
        : table_(n ? n : 11, hash, eq, alloc, identity()) {
        for (; first != last; ++first) table_.insert_multi(*first);
    }
    unordered_multiset(std::initializer_list<value_type> init, size_type n = 0, const Hash& hash = Hash(),
                        const KeyEqual& eq = KeyEqual(), const Allocator& alloc = Allocator())
        : table_(n ? n : 11, hash, eq, alloc, identity()) {
        for (const auto& v : init) table_.insert_multi(v);
    }

    iterator begin() { return table_.begin(); }
    const_iterator begin() const { return table_.begin(); }
    iterator end() { return table_.end(); }
    const_iterator end() const { return table_.end(); }
    bool empty() const { return table_.empty(); }
    size_type size() const { return table_.size(); }
    void clear() { table_.clear(); }
    iterator insert(const value_type& value) { return table_.insert_multi(value); }
    iterator insert(value_type&& value) { return table_.insert_multi(std::move(value)); }
    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) table_.insert_multi(*first);
    }
    void insert(std::initializer_list<value_type> init) {
        for (const auto& v : init) table_.insert_multi(v);
    }
    iterator erase(const_iterator pos) {
        iterator next = pos;
        ++next;
        table_.erase(pos);
        return next;
    }
    size_type erase(const key_type& key) {
        size_type n = 0;
        iterator it = find(key);
        while (it != end() && table_.key_eq()(*it, key)) {
            iterator cur = it;
            ++it;
            table_.erase(cur);
            ++n;
        }
        return n;
    }
    size_type count(const key_type& key) const {
        size_type n = 0;
        for (const_iterator it = find(key); it != end() && table_.key_eq()(*it, key); ++it) ++n;
        return n;
    }
    iterator find(const key_type& key) { return table_.find_key(key); }
    const_iterator find(const key_type& key) const { return table_.find_key(key); }
    void swap(unordered_multiset& other) noexcept { std::swap(table_, other.table_); }

private:
    detail::hash_table<Key, Key, identity, Hash, KeyEqual, Allocator> table_;
};

} // namespace miniSTL

#endif // MINISTL_UNORDERED_MULTISET_H
