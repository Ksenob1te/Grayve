#ifndef GRAYVE_DICT_H
#define GRAYVE_DICT_H
#include <compare>
#include <initializer_list>

template<class Key, class T, class Compare = less<Key>,
        class Allocator = allocator<pair<const Key, T>>>
class Dict {
    using key_type               = Key;
    using mapped_type            = T;
    using value_type             = pair<const Key, T>;
    using key_compare            = Compare;
    using allocator_type         = Allocator;
    using pointer                = typename allocator_traits<Allocator>::pointer;
    using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using size_type              = /* implementation-defined */;
    using difference_type        = /* implementation-defined */;
    using iterator               = /* implementation-defined */;
    using const_iterator         = /* implementation-defined */;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using node_type              = /* unspecified */;
    using insert_return_type     = __insert_return_type<iterator, node_type>;
};

#endif //GRAYVE_DICT_H
