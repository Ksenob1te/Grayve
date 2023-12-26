#ifndef GRAYVE_VECTOR_H
#define GRAYVE_VECTOR_H
#include <cstddef>
#include <cassert>
#include <iterator>
#include <limits>

namespace tmp {
    template<typename T>
    class Vector;

    template<typename T, bool is_const>
    class VecIterator {
    private:
        typedef std::conditional_t<is_const, const T, T> *node_itr_ptr;
        node_itr_ptr node;

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

    template<typename T>
    class Vector {
    private:
        size_t size;
        size_t capacity;
        T *arr;

    public:
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef VecIterator<T, false> iterator;
        typedef VecIterator<T, true> const_iterator;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        iterator begin() noexcept                   { return iterator(this->arr); }
        iterator end() noexcept                     { return iterator(this->arr + this->size); }
        const_iterator begin() const noexcept       { return const_iterator(this->arr); }
        const_iterator end() const noexcept         { return const_iterator(this->arr + this->size); }
//        const_iterator cbegin() const noexcept  {return const_iterator(this->arr);}
//        const_iterator cend() const noexcept    {return const_iterator(this->arr + this->size);}

        Vector() : size(0), capacity(0), arr(nullptr) {};

        explicit Vector(size_type size): size(size), capacity(size) {
            this->arr = new T[size];
            if (this->arr == nullptr)
                throw std::bad_alloc();
        }

        Vector(size_type size, const_reference val) requires std::copy_constructible<T>: size(size), capacity(size) {
            this->arr = new T[size];
            if (this->arr == nullptr) throw std::bad_alloc();
            for (size_t i = 0; i < size; i++)
                this->arr[i] = val;
        }

        Vector(const std::initializer_list<T> &il): size(il.size()), capacity(il.size()) {
            this->arr = new T[il.size()];
            if (this->arr == nullptr) throw std::bad_alloc();
            for (size_t i = 0; i < il.size(); ++i)
                this->arr[i] = *(il.begin() + i);
        }

        Vector(Vector const &other): size(other.size), capacity(other.size) {
            this->arr = new T[other.size];
            if (this->arr == nullptr)
                throw std::bad_alloc();
            std::copy(other.arr, other.arr + other.size, this->arr);
        }

        Vector(Vector &&other) noexcept: size(other.size), capacity(other.capacity), arr(other.arr) {
            other.size = 0;
            other.capacity = 0;
            other.arr = nullptr;
        }

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

        reference operator[](size_type pos)                     { return this->arr[pos]; }
        const_reference operator[](size_type pos) const         { return this->arr[pos]; }
        [[nodiscard]] size_type get_size() const noexcept       { return this->size; }
        [[nodiscard]] size_type get_capacity() const noexcept   { return this->capacity; }
        [[nodiscard]] size_type max_size() const noexcept       { return std::numeric_limits<size_type>::max(); }
        [[nodiscard]] bool empty() const noexcept               { return this->size == 0; }

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

        void shrink_to_fit() requires std::move_constructible<T> {
            if (this->capacity == this->size) return;
            this->reserve(this->size);
        }

        reference at(size_type pos) {
            if (pos >= this->size)
                throw std::out_of_range("position_out_of_range");
            else
                return this->arr[pos];
        }

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

        void push_back(const T &val) { this->insert(this->end(), val); }

        void pop_back() { this->erase(this->end() - 1); }

        void clear() {
            for (T *ptr = this->arr; ptr != this->arr + this->size; ptr++)
                ptr->~Type();
            this->size = 0;
        }

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

        ~Vector() { delete[] this->arr; };

        iterator insert(iterator position, const T &val);

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
