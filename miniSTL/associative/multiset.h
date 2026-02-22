#ifndef MINISTL_MULTISET_H
#define MINISTL_MULTISET_H

#include <cstddef>
#include <memory>
#include <initializer_list>
#include "../detail/bst.h"

namespace miniSTL {

template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
class multiset {
public:
    using key_type        = Key;
    using value_type      = Key;
    using key_compare    = Compare;
    using value_compare  = Compare;
    using allocator_type = Allocator;
    using size_type      = std::size_t;
    using reference      = const value_type&;
    using const_reference = const value_type&;
    using pointer        = typename std::allocator_traits<Allocator>::const_pointer;
    using const_pointer  = typename std::allocator_traits<Allocator>::const_pointer;

    using iterator       = typename detail::bst<Key, Compare, Allocator, true>::const_iterator;
    using const_iterator = typename detail::bst<Key, Compare, Allocator, true>::const_iterator;

    multiset() : tree_(Compare(), Allocator()) {}
    explicit multiset(const Compare& comp, const Allocator& alloc = Allocator()) : tree_(comp, alloc) {}
    explicit multiset(const Allocator& alloc) : tree_(Compare(), alloc) {}
    template <typename InputIt>
    multiset(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(comp, alloc) {
        for (; first != last; ++first) tree_.insert_multi(*first);
    }
    multiset(const multiset& other) : tree_(other.key_comp(), other.get_allocator()) {
        for (const_iterator it = other.begin(); it != other.end(); ++it) tree_.insert_multi(*it);
    }
    multiset(multiset&& other) noexcept = default;
    multiset(std::initializer_list<value_type> init, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(comp, alloc) {
        for (const auto& v : init) tree_.insert_multi(v);
    }

    multiset& operator=(const multiset& other) {
        if (this != &other) { clear(); for (const_iterator it = other.begin(); it != other.end(); ++it) insert(*it); }
        return *this;
    }
    multiset& operator=(multiset&& other) noexcept = default;
    multiset& operator=(std::initializer_list<value_type> init) { clear(); insert(init); return *this; }

    allocator_type get_allocator() const { return tree_.get_allocator(); }
    key_compare key_comp() const { return tree_.value_comp(); }
    value_compare value_comp() const { return tree_.value_comp(); }

    iterator begin() const { return tree_.begin(); }
    const_iterator cbegin() const { return tree_.begin(); }
    iterator end() const { return tree_.end(); }
    const_iterator cend() const { return tree_.end(); }

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
        while (it != end() && !key_comp()(key, *it) && !key_comp()(*it, key)) {
            iterator next = it;
            ++next;
            tree_.erase(it);
            it = next;
            ++n;
        }
        return n;
    }
    size_type count(const key_type& key) const { return tree_.count(key); }
    iterator find(const key_type& key) { return tree_.find(key); }
    const_iterator find(const key_type& key) const { return tree_.find(key); }
    void swap(multiset& other) noexcept { std::swap(tree_, other.tree_); }

private:
    detail::bst<Key, Compare, Allocator, true> tree_;
};

} // namespace miniSTL

#endif // MINISTL_MULTISET_H
