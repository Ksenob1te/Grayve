#ifndef GRAYVE_VECTOR_H
#define GRAYVE_VECTOR_H
#include <cstddef>
#include <cassert>
#include <iterator>
#include <limits>

namespace tmp {
    /**
     * @brief A basic Vector implementation similar to std::vector.
     * @tparam T The type of elements stored in the Vector.
     */
    template<typename T>
    class Vector;

    /**
     * @brief Iterator for the Vector class.
     * @tparam T The type of elements stored in the Vector.
     * @tparam is_const Whether the iterator is const or non-const.
     */
    template<typename T, bool is_const>
    class VecIterator {
    private:
        typedef std::conditional_t<is_const, const T, T> *node_itr_ptr; /**< Node pointer type based on constness. */
        node_itr_ptr node; /**< Pointer to the current node in the Vector. */

        /**
         * @brief Explicit constructor that initializes the iterator with a node pointer.
         * @param node Pointer to the node for the iterator.
         */
        explicit VecIterator(node_itr_ptr node) : node(node) {};

        friend Vector<T>;
        friend VecIterator<T, !is_const>;

    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef std::conditional_t<is_const, const T, T> *pointer;
        typedef std::conditional_t<is_const, const T, T> &reference;
        typedef std::random_access_iterator_tag iterator_category;

        VecIterator() noexcept: node(nullptr) {};

        template<bool other_const>
        explicit VecIterator(const VecIterator<T, other_const> &it)
        noexcept requires (is_const >= other_const)
                : node(it.node) {};


        template<bool other_const>
        explicit VecIterator(VecIterator<T, other_const> &&it)
        noexcept requires (is_const >= other_const)
                : node(it.node) { it.node = nullptr; }

        template<bool other_const>
        VecIterator &operator=(const VecIterator<T, other_const> &it)
        noexcept requires (is_const >= other_const) {
            node = it.node;
            return *this;
        }

        template<bool other_const>
        VecIterator &operator=(VecIterator<T, other_const> &&it)
        noexcept requires (is_const >= other_const) {
            node = it.node;
            it.node = nullptr;
            return *this;
        }

        reference operator*() const noexcept { return *(this->node); }

        template<bool other_const>
        bool operator==(const VecIterator<T, other_const> &it) const noexcept { return this->node == it.node; }

        template<bool other_const>
        bool operator!=(const VecIterator<T, other_const> &it) const noexcept { return this->node != it.node; }

        template<bool other_const>
        bool operator<(const VecIterator<T, other_const> &it) const noexcept { return this->node < it.node; }

        template<bool other_const>
        bool operator>(const VecIterator<T, other_const> &it) const noexcept { return this->node > it.node; }

        template<bool other_const>
        bool operator<=(const VecIterator<T, other_const> &it) const noexcept { return this->node <= it.node; }

        template<bool other_const>
        bool operator>=(const VecIterator<T, other_const> &it) const noexcept { return this->node >= it.node; }

        VecIterator &operator++() noexcept {
            (*this).node++;
            return *this;
        }

        VecIterator operator++(int) noexcept {
            VecIterator<T, is_const> old(*this);
            (*this).node++;
            return old;
        }

        VecIterator &operator--() noexcept {
            (*this).node--;
            return *this;
        }

        VecIterator operator--(int) noexcept {
            VecIterator<T, is_const> old(*this);
            (*this).node--;
            return old;
        }

        VecIterator operator+(difference_type n) const noexcept {
            VecIterator<T, is_const> iter(this->node + n);
            return iter;
        }

        VecIterator operator-(difference_type n) const noexcept {
            VecIterator<T, is_const> iter(this->node - n);
            return iter;
        }

        template<bool other_const>
        difference_type operator-(const VecIterator<T, other_const> &it) const {
            return this->node - it.node;
        }

        template<class n_type, bool is_const_n>
        friend VecIterator operator+(difference_type n, const VecIterator<n_type, is_const_n> &it) {
            it.ptr += n;
            return it;
        }

        reference operator[](difference_type n) const {
            auto tmp = this->ptr;
            tmp += n;
            return *tmp;
        }

        VecIterator &operator+=(difference_type n) {
            this->ptr += n;
            return *this;
        }

        VecIterator &operator-=(difference_type n) {
            this->ptr -= n;
            return *this;
        }
    };

    /**
     * @brief A basic Vector implementation similar to std::vector.
     * @tparam T The type of elements stored in the Vector.
     */
    template<typename T>
    class Vector {
    private:
        size_t size; /**< Current number of elements in the Vector. */
        size_t capacity; /**< Current capacity of the Vector. */
        T *arr; /**< Pointer to the underlying array. */

    public:
        using value_type = T; /**< Type of elements stored in the Vector. */
        using reference = T &; /**< Reference to an element in the Vector. */
        using const_reference = const T &; /**< Const reference to an element in the Vector. */
        using iterator = VecIterator<T, false>; /**< Iterator type for non-const Vector. */
        using const_iterator = VecIterator<T, true>; /**< Iterator type for const Vector. */
        using difference_type = std::ptrdiff_t; /**< Type to represent the difference between iterators. */
        using size_type = std::size_t; /**< Type to represent sizes and indices. */

        /**
         * @brief Iterator to the beginning of the Vector.
         * @return An iterator pointing to the first element.
         */
        iterator begin() noexcept                   { return iterator(this->arr); }

        /**
         * @brief Iterator to the end of the Vector.
         * @return An iterator pointing to the past-the-end element.
         */
        iterator end() noexcept                     { return iterator(this->arr + this->size); }

        /**
         * @brief Begins iteration through the Vector (const version).
         * @return A const iterator pointing to the first element of the Vector.
         */
        const_iterator begin() const noexcept       { return const_iterator(this->arr); }

        /**
         * @brief Ends iteration through the Vector (const version).
         * @return A const iterator pointing to the past-the-end element of the Vector.
         */
        const_iterator end() const noexcept         { return const_iterator(this->arr + this->size); }

        /**
         * @brief Default constructor.
         */
        Vector() : size(0), capacity(0), arr(nullptr) {};

        /**
         * @brief Constructs the Vector with a specified size.
         * @param size The initial size of the Vector.
         */
        explicit Vector(size_type size): size(size), capacity(size) {
            this->arr = new T[size];
            if (this->arr == nullptr)
                throw std::bad_alloc();
        }

        /**
         * @brief Constructs the Vector with a specified size and value.
         * @param size The initial size of the Vector.
         * @param val The value to initialize elements.
         */
        Vector(size_type size, const_reference val) requires std::copy_constructible<T>: size(size), capacity(size) {
            this->arr = new T[size];
            if (this->arr == nullptr) throw std::bad_alloc();
            for (size_t i = 0; i < size; i++)
                this->arr[i] = val;
        }

        /**
         * @brief Constructs the Vector from an initializer list.
         * @param il The initializer list to initialize elements.
         */
        Vector(const std::initializer_list<T> &il): size(il.size()), capacity(il.size()) {
            this->arr = new T[il.size()];
            if (this->arr == nullptr) throw std::bad_alloc();
            for (size_t i = 0; i < il.size(); ++i)
                this->arr[i] = *(il.begin() + i);
        }

        /**
         * @brief Copy constructor.
         * @param other The Vector to copy from.
         */
        Vector(Vector const &other): size(other.size), capacity(other.size) {
            this->arr = new T[other.size];
            if (this->arr == nullptr)
                throw std::bad_alloc();
            std::copy(other.arr, other.arr + other.size, this->arr);
        }

        /**
         * @brief Move constructor.
         * @param other The Vector to move from.
         */
        Vector(Vector &&other) noexcept: size(other.size), capacity(other.capacity), arr(other.arr) {
            other.size = 0;
            other.capacity = 0;
            other.arr = nullptr;
        }

        /**
         * @brief Copy assignment operator.
         * @param other The Vector to copy assign from.
         * @return Reference to the assigned Vector.
         */
        Vector &operator=(const Vector &other) {
            if (this == &other) return *this;
            T *new_data = new T[other.size];
            if (new_data == nullptr) throw std::bad_alloc();
            for (int i = 0; i < other.size; ++i)
                new_data[i] = other[i];
            delete[] this->arr;
            this->arr = new_data;
            this->size = other.size;
            this->capacity = other.size;
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * @param other The Vector to move assign from.
         * @return Reference to the assigned Vector.
         */
        Vector &operator=(Vector &&other) noexcept {
            delete[] this->arr;
            this->size = other.size;
            this->capacity = other.capacity;
            this->arr = other.arr;

            other.size = 0;
            other.capacity = 0;
            other.arr = nullptr;
            return *this;
        }

        Vector &operator=(const std::initializer_list<T> &il) {
            T *new_data = new T[il.size()];
            if (new_data == nullptr) throw std::bad_alloc();
            for (int i = 0; i < il.size(); ++i)
                new_data[i] = *(il.begin() + i);
            delete[] this->arr;
            this->arr = new_data;
            this->size = il.size();
            this->capacity = il.size();
            return *this;
        }

        bool operator==(Vector const &other) const {
            if (this->size != other.size) return false;

            for (size_t i = 0; i < this->size; i++)
                if (this->arr[i] != other[i]) return false;
            return true;
        }

        /**
         * @brief Accesses the element at the specified position in the Vector.
         * @param pos The position of the element.
         * @return Reference to the element at the specified position.
         */
        reference operator[](size_type pos)                     { return this->arr[pos]; }

        /**
         * @brief Accesses the element at the specified position in the Vector (const version).
         * @param pos The position of the element.
         * @return Const reference to the element at the specified position.
         */
        const_reference operator[](size_type pos) const         { return this->arr[pos]; }

        /**
         * @brief Returns the current size of the Vector.
         * @return The current size of the Vector.
         */
        [[nodiscard]] size_type get_size() const noexcept       { return this->size; }

        /**
         * @brief Returns the current capacity of the Vector.
         * @return The current capacity of the Vector.
         */
        [[nodiscard]] size_type get_capacity() const noexcept   { return this->capacity; }

        /**
         * @brief Returns the maximum possible size of the Vector.
         * @return The maximum possible size of the Vector.
         */
        [[nodiscard]] size_type max_size() const noexcept       { return std::numeric_limits<size_type>::max(); }

        /**
         * @brief Checks whether the Vector is empty.
         * @return True if the Vector is empty, false otherwise.
         */
        [[nodiscard]] bool empty() const noexcept               { return this->size == 0; }

        /**
         * @brief Reserves storage for the Vector.
         * @param new_capacity The new capacity to reserve.
         * @details If the new capacity is greater than the current capacity,
         * it allocates storage to fit at least that many elements.
         */
        void reserve(size_type new_capacity) requires std::move_constructible<T> {
            if (new_capacity < this->capacity) return;

            T *buf_arr = new T[new_capacity];
            T *ptr = buf_arr, *src = arr;
            for (size_t i = 0; i < this->size; i++, ptr++, src++)
                new(static_cast<void *>(ptr)) T{std::move(*src)};

            delete[] arr;
            this->arr = buf_arr;
            this->capacity = new_capacity;
        }

        /**
         * @brief Reduces the capacity of the Vector to fit its size.
         * @details Reduces the capacity of the Vector to match its size.
         * If the capacity is larger than the current size, it does nothing.
         */
        void shrink_to_fit() requires std::move_constructible<T> {
            if (this->capacity == this->size) return;
            this->reserve(this->size);
        }

        /**
         * @brief Accesses the element at the specified position with bounds checking.
         * @param pos The position of the element.
         * @return Reference to the element at the specified position.
         * @throw std::out_of_range if pos is out of range.
         */
        reference at(size_type pos) {
            if (pos >= this->size)
                throw std::out_of_range("position_out_of_range");
            else
                return this->arr[pos];
        }

        /**
         * @brief Accesses the element at the specified position with bounds checking (const version).
         * @param pos The position of the element.
         * @return Const reference to the element at the specified position.
         * @throw std::out_of_range if pos is out of range.
         */
        const_reference at(size_type pos) const     { this->at(pos); }
        reference front()                           { return this->arr[0]; }
        const_reference front() const               { return this->arr[0]; }
        reference back()                            { return this->arr[this->size - 1]; }
        const_reference back() const                { return this->arr[this->size - 1]; }
        T *data() noexcept                          { return this->arr; }
        const T *data() const noexcept              { return this->arr; }

        void assign(size_type new_size, const T &val) {
            T *new_data = new T[new_size]{val};
            if (new_data == nullptr) throw std::bad_alloc();
            delete[] this->arr;
            this->arr = new_data;
            this->size = new_size;
            this->capacity = new_size;
        }

        /**
         * @brief Adds an element to the end of the Vector.
         * @param val The value to be added.
         */
        void push_back(const T &val) { this->insert(this->end(), val); }

        /**
         * @brief Removes the last element from the Vector.
         */
        void pop_back() { this->erase(this->end() - 1); }

        /**
         * @brief Clears the contents of the Vector.
         * @details Removes all elements from the Vector and sets its size to 0.
         */
        void clear() {
            for (T *ptr = this->arr; ptr != this->arr + this->size; ptr++)
                ptr->~Type();
            this->size = 0;
        }

        /**
         * @brief Resizes the Vector to the specified size.
         * @param new_size The new size of the Vector.
         * @details If the new size is greater than the current size,
         * new elements are added with their default-initialized value.
         * If the new size is smaller, the Vector is truncated.
         */
        void resize(size_type new_size) {
            if (this->size == new_size)
                return;

            size_t copy_size;
            if (this->size < new_size)
                copy_size = this->size;

            if (this->size > new_size)
                copy_size = new_size;
            T *buf_arr = new T[new_size];
            T *ptr = buf_arr, *src = arr;
            for (size_t i = 0; i < copy_size; i++, ptr++, src++) {
                new(static_cast<void *>(ptr)) T{std::move(*src)};
            }
            delete[] arr;
            this->arr = buf_arr;
            this->capacity = new_size;
            this->size = new_size;
        }

        /**
         * @brief Destructor.
         */
        ~Vector() { delete[] this->arr; };

        /**
         * @brief Inserts an element at a specified position in the Vector.
         * @param position The position where the new element will be inserted.
         * @param val The value of the element to be inserted.
         * @return An iterator pointing to the inserted element.
         */
        iterator insert(iterator position, const T &val);

        /**
         * @brief Erases an element at a specified position from the Vector.
         * @param position The position of the element to be erased.
         * @return An iterator pointing to the element following the erased element.
         */
        iterator erase(iterator position);
    };

    static_assert(std::random_access_iterator<VecIterator<int, false>>);
    static_assert(std::random_access_iterator<VecIterator<int, true>>);

    template<typename T>
    Vector<T>::iterator Vector<T>::insert(Vector<T>::iterator position, const T &val) {
        if (this->size == this->capacity) {
            if (this->size == 0)
                this->capacity = 1;
            else
                this->capacity *= 2;

            T *buf_arr = new T[this->capacity];
            T *ptr = buf_arr, *src = this->arr;

            Vector<T>::iterator it;
            for (it = this->begin(); it != position; it++, ptr++, src++)
                new(static_cast<void *>(ptr)) T{std::move(*src)};

            Vector<T>::iterator return_iter(ptr);
            *ptr = val;
            ++ptr;

            for (; it != this->end(); it++, ptr++, src++)
                new(static_cast<void *>(ptr)) T{std::move(*src)};

            delete[] arr;
            this->arr = buf_arr;
            ++this->size;
            return return_iter;
        } else {
            Vector<T>::iterator it;
            for (it = this->end(); it != position; --it)
                *it = *(it - 1);
            *it = val;
            ++this->size;
            return it;
        }
    }

    template<typename T>
    Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator position) {
        size_t diff = position - begin();
        for (iterator it = position + 1; it != this->end(); it++)
            *(it - 1) = *(it);

        if (this->size - 1 == this->capacity / 2) {
            this->capacity /= 2;

            T *buf_arr = new T[this->capacity];
            T *ptr = buf_arr, *src = arr;
            for (size_t i = 0; i < this->size - 1; i++, ptr++, src++)
                new(static_cast<void *>(ptr)) T{std::move(*src)};

            delete[] arr;
            this->arr = buf_arr;
            this->size--;
        } else
            this->size--;
        return iterator(this->arr + diff);
    }
}

#endif //GRAYVE_VECTOR_H
