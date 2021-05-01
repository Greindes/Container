#ifndef ARRAY_H
#define ARRAY_H

#include<type_traits>
#include<iterator>

using size_t = unsigned int;

template<class T, size_t N>
class Array
{
public:
    Array();
    Array(const Array<T, N>& arr);
    ~Array();

    size_t size() const;

    T& operator[](size_t n);
    const T& operator[](size_t n) const;

    Array<T, N>& operator=(const Array<T, N> arr);

    template<bool Const>
    class ArrayIterator {
        friend class Array;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = typename std::conditional<Const, const value_type*, value_type*>::type;
        using reference = typename std::conditional<Const, const value_type&, value_type&>::type;
        using iterator_category = std::random_access_iterator_tag;

        reference operator*() const { return *ptr; }
        ArrayIterator<Const>& operator++() { ++ptr; return *this; }
        ArrayIterator<Const> operator++(int) { auto res = *this; ++(*this); return res; }
        ArrayIterator<Const>& operator--() { --ptr; return *this; }
        ArrayIterator<Const> operator--(int) { auto res = *this; --(*this); return res; }

        ArrayIterator<Const> operator+(const difference_type& dif) const {
            ArrayIterator<Const> res(ptr + dif);
            return res;
        }
        ArrayIterator<Const> operator-(const difference_type& dif) const {
            ArrayIterator<Const> res(ptr - dif);
            return res;
        }
        template<bool C>
        difference_type operator-(const ArrayIterator<C>& iter) const {
            return ptr - iter.ptr;
        }
        ArrayIterator<Const>& operator+=(const difference_type& dif) {
            ptr += dif;
        }
        ArrayIterator<Const>& operator-=(const difference_type& dif) {
            ptr -= dif;
        }

        ArrayIterator<Const>& operator[](const difference_type& dif) {
            ptr += dif;
        }

        template<bool R>
        bool operator==(const ArrayIterator<R>& iter) const { return ptr == iter.ptr; }
        template<bool R>
        bool operator!=(const ArrayIterator<R>& iter) const { return ptr != iter.ptr; }
        template<bool R>
        bool operator<(const ArrayIterator<R>& iter) const { return ptr < iter.ptr; }
        template<bool R>
        bool operator>(const ArrayIterator<R>& iter) const { return ptr > iter.ptr; }
        template<bool R>
        bool operator<=(const ArrayIterator<R>& iter) const { return ptr <= iter.ptr; }
        template<bool R>
        bool operator>=(const ArrayIterator<R>& iter) const { return ptr >= iter.ptr; }

    private:
        explicit ArrayIterator(pointer p) : ptr(p) {};
        pointer ptr;
    };

    using iterator = ArrayIterator<false>;
    using const_iterator = ArrayIterator<true>;
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + N); }
    const_iterator cbegin() const { return const_iterator(data); }
    const_iterator cend() const { return const_iterator(data + N); }

private:
    void createData();
    T* data;
};

#endif // ARRAY_H
