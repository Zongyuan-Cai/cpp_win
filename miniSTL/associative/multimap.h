#ifndef MINISTL_MULTIMAP_H
#define MINISTL_MULTIMAP_H

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <utility>
#include <stdexcept>
#include "../detail/bst.h"

namespace miniSTL {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class multimap {
public:
    using key_type    = Key;
    using mapped_type = T;
    using value_type  = std::pair<const Key, T>;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using size_type   = std::size_t;

    struct value_compare {
        Compare comp;
        value_compare(Compare c) : comp(c) {}
        bool operator()(const value_type& a, const value_type& b) const { return comp(a.first, b.first); }
    };

    using iterator       = typename detail::bst<value_type, value_compare, Allocator, true>::iterator;
    using const_iterator = typename detail::bst<value_type, value_compare, Allocator, true>::const_iterator;

    struct select_first {
        const Key& operator()(const value_type& p) const { return p.first; }
    };

    multimap() : tree_(value_compare(Compare()), Allocator()) {}
    explicit multimap(const Compare& comp, const Allocator& alloc = Allocator())
        : tree_(value_compare(comp), alloc) {}
    template <typename InputIt>
    multimap(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(value_compare(comp), alloc) {
        for (; first != last; ++first) tree_.insert_multi(*first);
    }
    multimap(const multimap& other) : tree_(value_compare(other.key_comp()), other.get_allocator()) {
        for (const_iterator it = other.begin(); it != other.end(); ++it) tree_.insert_multi(*it);
    }
    multimap(multimap&& other) noexcept = default;
    multimap(std::initializer_list<value_type> init, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(value_compare(comp), alloc) {
        for (const auto& v : init) tree_.insert_multi(v);
    }

    multimap& operator=(const multimap& other) {
        if (this != &other) { clear(); for (const_iterator it = other.begin(); it != other.end(); ++it) insert(*it); }
        return *this;
    }
    multimap& operator=(multimap&& other) noexcept = default;
    multimap& operator=(std::initializer_list<value_type> init) { clear(); insert(init); return *this; }

    allocator_type get_allocator() const { return tree_.get_allocator(); }
    key_compare key_comp() const { return tree_.value_comp().comp; }
    value_compare value_comp() const { return tree_.value_comp(); }

    iterator begin() { return tree_.begin(); }
    const_iterator begin() const { return tree_.begin(); }
    iterator end() { return tree_.end(); }
    const_iterator end() const { return tree_.end(); }

    bool empty() const { return tree_.empty(); }
    size_type size() const { return tree_.size(); }
    size_type max_size() const { return tree_.get_allocator().max_size(); }

    void clear() { tree_.clear(); }
    iterator insert(const value_type& value) { return tree_.insert_multi(value); }
    iterator insert(value_type&& value) { return tree_.insert_multi(std::move(value)); }
    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) tree_.insert_multi(*first);
    }
    void insert(std::initializer_list<value_type> init) {
        for (const auto& v : init) tree_.insert_multi(v);
    }
    iterator erase(const_iterator pos) {
        iterator next = pos;
        ++next;
        tree_.erase(pos);
        return next;
    }
    size_type erase(const key_type& key) {
        size_type n = 0;
        iterator it = find(key);
        while (it != end() && !key_comp()(key, it->first) && !key_comp()(it->first, key)) {
            iterator cur = it;
            ++it;
            tree_.erase(cur);
            ++n;
        }
        return n;
    }
    size_type count(const key_type& key) const {
        size_type n = 0;
        const_iterator it = find(key);
        while (it != end() && !key_comp()(key, it->first) && !key_comp()(it->first, key)) { ++n; ++it; }
        return n;
    }
    iterator find(const key_type& key) { return tree_.find_key(key, select_first()); }
    const_iterator find(const key_type& key) const { return tree_.find_key(key, select_first()); }
    void swap(multimap& other) noexcept { std::swap(tree_, other.tree_); }

private:
    detail::bst<value_type, value_compare, Allocator, true> tree_;
};

} // namespace miniSTL

#endif // MINISTL_MULTIMAP_H
