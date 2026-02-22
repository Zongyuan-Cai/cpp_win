#ifndef MINISTL_UNORDERED_MAP_H
#define MINISTL_UNORDERED_MAP_H

#include <cstddef>
#include <functional>
#include <memory>
#include <initializer_list>
#include <utility>
#include <stdexcept>
#include "../detail/hash_table.h"

namespace miniSTL {

template <typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class unordered_map {
public:
    using key_type    = Key;
    using mapped_type = T;
    using value_type  = std::pair<const Key, T>;
    using hasher      = Hash;
    using key_equal   = KeyEqual;
    using allocator_type = Allocator;
    using size_type   = std::size_t;

    struct select_first {
        const Key& operator()(const value_type& p) const { return p.first; }
    };
    using iterator       = typename detail::hash_table<Key, value_type, select_first, Hash, KeyEqual, Allocator>::iterator;
    using const_iterator = typename detail::hash_table<Key, value_type, select_first, Hash, KeyEqual, Allocator>::const_iterator;

    unordered_map() : table_() {}
    explicit unordered_map(size_type n, const Hash& hash = Hash(), const KeyEqual& eq = KeyEqual(),
                            const Allocator& alloc = Allocator())
        : table_(n, hash, eq, alloc, select_first()) {}
    template <typename InputIt>
    unordered_map(InputIt first, InputIt last, size_type n = 0, const Hash& hash = Hash(),
                  const KeyEqual& eq = KeyEqual(), const Allocator& alloc = Allocator())
        : table_(n ? n : 11, hash, eq, alloc, select_first()) {
        for (; first != last; ++first) table_.insert_unique(*first);
    }
    unordered_map(std::initializer_list<value_type> init, size_type n = 0, const Hash& hash = Hash(),
                   const KeyEqual& eq = KeyEqual(), const Allocator& alloc = Allocator())
        : table_(n ? n : 11, hash, eq, alloc, select_first()) {
        for (const auto& v : init) table_.insert_unique(v);
    }

    iterator begin() { return table_.begin(); }
    const_iterator begin() const { return table_.begin(); }
    iterator end() { return table_.end(); }
    const_iterator end() const { return table_.end(); }
    bool empty() const { return table_.empty(); }
    size_type size() const { return table_.size(); }
    void clear() { table_.clear(); }
    std::pair<iterator, bool> insert(const value_type& value) { return table_.insert_unique(value); }
    std::pair<iterator, bool> insert(value_type&& value) { return table_.insert_unique(std::move(value)); }
    template <typename P>
    std::pair<iterator, bool> insert(P&& value) { return insert(value_type(std::forward<P>(value))); }
    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) table_.insert_unique(*first);
    }
    void insert(std::initializer_list<value_type> init) {
        for (const auto& v : init) table_.insert_unique(v);
    }
    iterator erase(const_iterator pos) {
        iterator next = pos;
        ++next;
        table_.erase(pos);
        return next;
    }
    size_type erase(const key_type& key) { return table_.erase_key(key); }
    size_type count(const key_type& key) const { return find(key) != end() ? 1 : 0; }
    iterator find(const key_type& key) { return table_.find_key(key); }
    const_iterator find(const key_type& key) const { return table_.find_key(key); }
    T& operator[](const key_type& key) {
        iterator it = find(key);
        if (it != end()) return it->second;
        auto p = insert(value_type(key, T()));
        return p.first->second;
    }
    T& at(const key_type& key) {
        iterator it = find(key);
        if (it == end()) throw std::out_of_range("unordered_map::at");
        return it->second;
    }
    const T& at(const key_type& key) const {
        const_iterator it = find(key);
        if (it == end()) throw std::out_of_range("unordered_map::at");
        return it->second;
    }
    void swap(unordered_map& other) noexcept { std::swap(table_, other.table_); }

private:
    detail::hash_table<Key, value_type, select_first, Hash, KeyEqual, Allocator> table_;
};

} // namespace miniSTL

#endif // MINISTL_UNORDERED_MAP_H
