#ifndef MINISTL_UNORDERED_SET_H
#define MINISTL_UNORDERED_SET_H

#include <cstddef>
#include <functional>
#include <memory>
#include <initializer_list>
#include "../detail/hash_table.h"

namespace miniSTL {

struct identity {
    template <typename T>
    const T& operator()(const T& x) const { return x; }
};

template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<Key>>
class unordered_set {
public:
    using key_type    = Key;
    using value_type  = Key;
    using hasher      = Hash;
    using key_equal   = KeyEqual;
    using allocator_type = Allocator;
    using size_type   = std::size_t;
    using reference   = const value_type&;
    using const_reference = const value_type&;

    using iterator       = typename detail::hash_table<Key, Key, identity, Hash, KeyEqual, Allocator>::const_iterator;
    using const_iterator = typename detail::hash_table<Key, Key, identity, Hash, KeyEqual, Allocator>::const_iterator;

    unordered_set() : table_() {}
    explicit unordered_set(size_type n, const Hash& hash = Hash(), const KeyEqual& eq = KeyEqual(),
                          const Allocator& alloc = Allocator())
        : table_(n, hash, eq, alloc, identity()) {}
    template <typename InputIt>
    unordered_set(InputIt first, InputIt last, size_type n = 0, const Hash& hash = Hash(),
                  const KeyEqual& eq = KeyEqual(), const Allocator& alloc = Allocator())
        : table_(n ? n : 11, hash, eq, alloc, identity()) {
        for (; first != last; ++first) table_.insert_unique(*first);
    }
    unordered_set(const unordered_set& other) = default;
    unordered_set(unordered_set&& other) noexcept = default;
    unordered_set(std::initializer_list<value_type> init, size_type n = 0, const Hash& hash = Hash(),
                  const KeyEqual& eq = KeyEqual(), const Allocator& alloc = Allocator())
        : table_(n ? n : 11, hash, eq, alloc, identity()) {
        for (const auto& v : init) table_.insert_unique(v);
    }

    unordered_set& operator=(const unordered_set& other) = default;
    unordered_set& operator=(unordered_set&& other) noexcept = default;
    unordered_set& operator=(std::initializer_list<value_type> init) {
        clear();
        insert(init);
        return *this;
    }

    iterator begin() { return table_.begin(); }
    const_iterator begin() const { return table_.begin(); }
    iterator end() { return table_.end(); }
    const_iterator end() const { return table_.end(); }
    bool empty() const { return table_.empty(); }
    size_type size() const { return table_.size(); }
    size_type max_size() const { return table_.get_allocator().max_size(); }

    void clear() { table_.clear(); }
    std::pair<iterator, bool> insert(const value_type& value) { return table_.insert_unique(value); }
    std::pair<iterator, bool> insert(value_type&& value) { return table_.insert_unique(std::move(value)); }
    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) table_.insert_unique(*first);
    }
    void insert(std::initializer_list<value_type> init) {
        for (const auto& v : init) table_.insert_unique(v);
    }
    iterator erase(const_iterator pos) {
        iterator it = pos;
        ++it;
        table_.erase(pos);
        return it;
    }
    size_type erase(const key_type& key) { return table_.erase_key(key); }
    size_type count(const key_type& key) const {
        return find(key) != end() ? 1 : 0;
    }
    iterator find(const key_type& key) { return table_.find_key(key); }
    const_iterator find(const key_type& key) const { return table_.find_key(key); }
    void swap(unordered_set& other) noexcept { std::swap(table_, other.table_); }

private:
    detail::hash_table<Key, Key, identity, Hash, KeyEqual, Allocator> table_;
};

} // namespace miniSTL

#endif // MINISTL_UNORDERED_SET_H
