#ifndef VECTOR_H
#define VECTOR_H

#include<type_traits>
#include<iterator>

template<class T>
class Vector
{
public:
    Vector();
    Vector(size_t N, const T& val);
    Vector(const Vector<T>& vec);
    ~Vector();
    Vector<T>& operator=(const Vector<T>& vec);

    void push_back(const T& val);
    void pop_back();
    size_t size() const;
    void clear();

    T& operator[](size_t n);
    const T& operator[](size_t n) const;

    template<bool Const>
    class VectorIterator {
        friend class Vector;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = typename std::conditional<Const, const value_type*, value_type*>::type;
        using reference = typename std::conditional<Const, const value_type&, value_type&>::type;
        using iterator_category = std::random_access_iterator_tag;
        reference operator*() const { return *ptr; }
        VectorIterator<Const>& operator++() { ++ptr; return *this; }
        VectorIterator<Const> operator++(int) { auto res = *this; ++(*this); return res; }
        VectorIterator<Const>& operator--() { --ptr; return *this; }
        VectorIterator<Const> operator--(int) { auto res = *this; --(*this); return res; }

        VectorIterator<Const> operator+(const difference_type& dif) const {
            VectorIterator<Const> res(ptr + dif);
            return res;
        }
        VectorIterator<Const> operator-(const difference_type& dif) const {
            VectorIterator<Const> res(ptr - dif);
            return res;
        }
        template<bool C>
        difference_type operator-(const VectorIterator<C>& iter) const {
            return ptr - iter.ptr;
        }
        VectorIterator<Const>& operator+=(const difference_type& dif) {
            ptr += dif;
        }
        VectorIterator<Const>& operator-=(const difference_type& dif) {
            ptr -= dif;
        }

        VectorIterator<Const>& operator[](const difference_type& dif) {
            ptr += dif;
        }

        template<bool R>
        bool operator==(const VectorIterator<R>& iter) const { return ptr == iter.ptr; }
        template<bool R>
        bool operator!=(const VectorIterator<R>& iter) const { return ptr != iter.ptr; }
        template<bool R>
        bool operator<(const VectorIterator<R>& iter) const { return ptr < iter.ptr; }
        template<bool R>
        bool operator>(const VectorIterator<R>& iter) const { return ptr > iter.ptr; }
        template<bool R>
        bool operator<=(const VectorIterator<R>& iter) const { return ptr <= iter.ptr; }
        template<bool R>
        bool operator>=(const VectorIterator<R>& iter) const { return ptr >= iter.ptr; }

    private:
        explicit VectorIterator(pointer p) : ptr(p) {};
        pointer ptr;
    };

    using iterator = VectorIterator<false>;
    using const_iterator = VectorIterator<true>;
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size()); }
    const_iterator cbegin() const { return const_iterator(data); }
    const_iterator cend() const { return const_iterator(data + size()); }

private:
    void set_size(size_t s);

private:
    T* data;
    size_t data_size;
    size_t mem_size = 1000;


};

#endif // VECTOR_H
