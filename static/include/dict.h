//#ifndef GRAYVE_DICT_H
//#define GRAYVE_DICT_H
//#include <compare>
//#include <initializer_list>
//#include <utility>
//#include <functional>
//#include <memory>
//#include "bits/stl_tree.h"
//#include <bits/functexcept.h>
//#include <bits/concept_check.h>
//
//
//// ListIterator<T, false> -> iterator
//// ListIterator<T, true> -> const_iterator
//template<typename T, bool is_const>
//class DictIterator {
//
//private:
//    typedef std::conditional_t<is_const, const T, T> *node_ptr_t;
//    node_ptr_t node;
//
//    friend DictIterator<T, !is_const>;
//public:
//    using difference_type           = std::ptrdiff_t;
//    using value_type                = T;
//    using pointer                   = std::conditional_t<is_const, const T, T>*;
//    using reference                 = std::conditional_t<is_const, const T, T>&;
//    using iterator_category         = std::bidirectional_iterator_tag;
//
//    inline DictIterator(node_ptr_t currentPosition): node(node) {}
//
//    // copy constructor
//    template<bool other_const>
//    inline DictIterator(DictIterator<T, other_const>& other)
//        noexcept
//        requires (is_const >= other_const)
//        : DictIterator(other.currentPosition) {};
//
//    template<bool other_const>
//    inline DictIterator& operator= (const DictIterator<T, other_const>& other)
//    noexcept
//    requires (is_const >= other_const) {
//        node = other.node;
//        return *this;
//    }
//    // move constructor
//    inline DictIterator(BidirectionalIterator&& iterator) noexcept
//    :DictIterator(iterator.currentPosition, iterator.begin, iterator.end) {}
//};
//
//
//template<class Key, class T, class Compare = std::less<Key>,
//        class Allocator = std::allocator<std::pair<const Key, T>>>
//class Dict {
//    using key_type                  = Key;
//    using mapped_type               = T;
//    using value_type                = std::pair<const Key, T>;
//    using key_compare               = Compare;
//    using allocator_type            = Allocator;
//    using pointer                   = typename std::allocator_traits<Allocator>::pointer;
//    using const_pointer             = typename std::allocator_traits<Allocator>::const_pointer;
//    using reference                 = value_type&;
//    using const_reference           = const value_type&;
//    using size_type                 = std::size_t;
//    using difference_type           = std::ptrdiff_t;
//    using iterator                  = typename _Rep_type::iterator ;
//    using const_iterator            = /* implementation-defined */;
//    using reverse_iterator          = std::reverse_iterator<iterator>;
//    using const_reverse_iterator    = std::reverse_iterator<const_iterator>;
////    using node_type                 = /* unspecified */;
//    using insert_return_type        = __insert_return_type<iterator, node_type>;
//};
//
//#endif //GRAYVE_DICT_H
