//#ifndef GRAYVE_MATRIX_H
//#define GRAYVE_MATRIX_H
//
//#include <compare>
//#include <initializer_list>
//#include <utility>
//#include <functional>
//#include <memory>
//
//template<typename T>
//class MatrixElement {
//private:
//    T data;
//    size_t x, y;
//    MatrixElement *up, *down, *prev, *next;
//};
//
//template<std::default_initializable T>
//class Matrix {
//private:
//    typedef MatrixElement<T> element_t;
//    element_t before_begin;
//    size_t height, width;
//public:
//    void link_horizontal(element_t *prev, element_t *next)
//    noexcept {
//        prev->next = next;
//        next->prev = prev;
//        next->x = prev->x + 1;
//        width = std::max(width, next->x);
//    }
//
//    void link_vertical(element_t *up, element_t *down)
//    noexcept {
//        up->down = down;
//        down->up = up;
//        down->y = up->y + 1;
//        height = std::max(height, down->y);
//    }
//
//    void erase_node(element_t* node) noexcept {
//        if (node->down != nullptr || node->next != nullptr)
//            return;
//        element_t* prev = node->prev;
//        element_t* up = node->up;
//        if (prev)
//            prev->next = nullptr;
//        if (up)
//            up->down = nullptr;
//
//        height = std::max(height, up->y);
//        width = std::max(width, up->y);
//    }
//
//    template<typename ...Args>
//    element_t* allocate(Args ... args) {
//        return new element_t{.data=
//        value_type(std::forward<Args>(args)...)};
//    }
//
//    void deallocate(element_t* node) noexcept {
//        delete node;
//    }
//
//};
//
//template<typename T, bool is_const>
//class MatrixIterator {
//    typedef std::conditional_t<is_const, const MatrixElement<T>, MatrixElement<T>> *element_ptr_t;
//    element_ptr_t element;
//
//    MatrixIterator(element_ptr_t element) : element(element) {};
//    friend Matrix<T>;
//    friend MatrixIterator<T, !is_const>;
//
//    typedef ptrdiff_t difference_type;
//    typedef T value_type;
//    typedef std::conditional_t<is_const, const T, T> *pointer;
//    typedef std::conditional_t<is_const, const T, T> &reference;
//    typedef std::bidirectional_iterator_tag iterator_category;
//
//    template<bool other_const>
//    MatrixIterator(MatrixIterator<T, other_const> &o)
//    noexcept requires (is_const >= other_const)
//            : element(o.element) {}
//
//    template<bool other_const>
//    MatrixIterator &operator=
//            (const MatrixIterator<T, other_const> &o)
//    noexcept requires (is_const >= other_const) {
//        element = o.element;
//        return *this;
//    }
//
//    MatrixIterator &operator++() noexcept {
//        element = element->next;
//        return *this;
//    }
//
//    MatrixIterator operator++(int) noexcept {
//        element = element->down;
//        return *this;
//    }
//
//    MatrixIterator &operator--() noexcept {
//        element = element->prev;
//        return *this;
//    }
//
//    MatrixIterator operator--(int) noexcept {
//        element = element->up;
//        return *this;
//    }
//
//    reference operator*() const noexcept {
//        return element->data;
//    }
//
//    pointer operator->() const noexcept {
//        return &element->data;
//    }
//
//    MatrixIterator() noexcept: element(nullptr) {}
//
//    template<bool other_const>
//    bool operator==(const MatrixIterator<T, other_const> &o)
//    const noexcept {
//        return element == o.element;
//    }
//
//    static_assert(std::bidirectional_iterator<MatrixIterator<int, false>>);
//    static_assert(std::bidirectional_iterator<MatrixIterator<int, true>>);
//};
//
//
//#endif //GRAYVE_MATRIX_H
