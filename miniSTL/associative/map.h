#ifndef MINISTL_MAP_H
#define MINISTL_MAP_H

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <utility>
#include <stdexcept>
#include "../detail/bst.h"

namespace miniSTL {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class map {
public:
    using key_type    = Key;
    using mapped_type = T;
    using value_type  = std::pair<const Key, T>;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using size_type   = std::size_t;
    using reference   = value_type&;
    using const_reference = const value_type&;
    using pointer     = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    struct value_compare {
        Compare comp;
        value_compare(Compare c) : comp(c) {}
        bool operator()(const value_type& a, const value_type& b) const { return comp(a.first, b.first); }
    };

    using iterator       = typename detail::bst<value_type, value_compare, Allocator, false>::iterator;
    using const_iterator = typename detail::bst<value_type, value_compare, Allocator, false>::const_iterator;

    struct select_first {
        const Key& operator()(const value_type& p) const { return p.first; }
    };

    map() : tree_(value_compare(Compare()), Allocator()) {}
    explicit map(const Compare& comp, const Allocator& alloc = Allocator())
        : tree_(value_compare(comp), alloc) {}
    explicit map(const Allocator& alloc) : tree_(value_compare(Compare()), alloc) {}
    template <typename InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(value_compare(comp), alloc) {
        for (; first != last; ++first) tree_.insert_unique(*first);
    }
    map(const map& other) : tree_(value_compare(other.key_comp()), other.get_allocator()) {
        for (const_iterator it = other.begin(); it != other.end(); ++it) tree_.insert_unique(*it);
    }
    map(map&& other) noexcept = default;
    map(std::initializer_list<value_type> init, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(value_compare(comp), alloc) {
        for (const auto& v : init) tree_.insert_unique(v);
    }

    map& operator=(const map& other) {
        if (this != &other) { clear(); for (const_iterator it = other.begin(); it != other.end(); ++it) insert(*it); }
        return *this;
    }
    map& operator=(map&& other) noexcept = default;
    map& operator=(std::initializer_list<value_type> init) { clear(); insert(init); return *this; }

    allocator_type get_allocator() const { return tree_.get_allocator(); }
    key_compare key_comp() const { return tree_.value_comp().comp; }
    value_compare value_comp() const { return tree_.value_comp(); }

    iterator begin() { return tree_.begin(); }
    const_iterator begin() const { return tree_.begin(); }
    const_iterator cbegin() const { return tree_.begin(); }
    iterator end() { return tree_.end(); }
    const_iterator end() const { return tree_.end(); }
    const_iterator cend() const { return tree_.end(); }

    bool empty() const { return tree_.empty(); }
    size_type size() const { return tree_.size(); }
    size_type max_size() const { return tree_.get_allocator().max_size(); }

    void clear() { tree_.clear(); }
    std::pair<iterator, bool> insert(const value_type& value) {
        auto p = tree_.insert_unique(value);
        return {p.first, p.second};
    }
    std::pair<iterator, bool> insert(value_type&& value) {
        auto p = tree_.insert_unique(std::move(value));
        return {p.first, p.second};
    }
    template <typename P>
    std::pair<iterator, bool> insert(P&& value) {
        return insert(value_type(std::forward<P>(value)));
    }
    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) tree_.insert_unique(*first);
    }
    void insert(std::initializer_list<value_type> init) {
        for (const auto& v : init) tree_.insert_unique(v);
    }
    iterator erase(const_iterator pos) {
        iterator next = pos;
        ++next;
        tree_.erase(pos);
        return next;
    }
    size_type erase(const key_type& key) {
        iterator it = find(key);
        if (it == end()) return 0;
        tree_.erase(it);
        return 1;
    }
    size_type count(const key_type& key) const {
        return find(key) != end() ? 1 : 0;
    }
    iterator find(const key_type& key) {
        return tree_.find_key(key, select_first());
    }
    const_iterator find(const key_type& key) const {
        return tree_.find_key(key, select_first());
    }
    T& operator[](const key_type& key) {
        iterator it = find(key);
        if (it != end()) return it->second;
        auto p = insert(value_type(key, T()));
        return p.first->second;
    }
    T& at(const key_type& key) {
        iterator it = find(key);
        if (it == end()) throw std::out_of_range("map::at");
        return it->second;
    }
    const T& at(const key_type& key) const {
        const_iterator it = find(key);
        if (it == end()) throw std::out_of_range("map::at");
        return it->second;
    }
    void swap(map& other) noexcept { std::swap(tree_, other.tree_); }

private:
    detail::bst<value_type, value_compare, Allocator, false> tree_;
};

} // namespace miniSTL

#endif // MINISTL_MAP_H
