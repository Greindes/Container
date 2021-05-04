#include "vector.h"
#include "unorderedset.h"

template<class T>
Vector<T>::Vector()
{
    data = new T[mem_size];
}

template<class T>
Vector<T>::Vector(const Vector<T> &vec) : mem_size(vec.mem_size)
{
    data = new T[mem_size];
    size_t s = vec.size();
    for (size_t i = 0; i < s; ++i)
        data[i] = vec[i];
    data_size = s;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] data;
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vec)
{
    clear();
    if (vec.size() >= mem_size)
        reserve(vec.mem_size);
    size_t s = vec.size();
    for (size_t i = 0; i < s; ++i)
        data[i] = vec[i];
    data_size = s;
    return *this;
}

template<class T>
void Vector<T>::push_back(const T &val)
{
    if (size() == mem_size)
        reserve(mem_size * 2);
    data[data_size++] = val;
}

template<class T>
void Vector<T>::pop_back()
{
    --data_size;
}

template<class T>
size_t Vector<T>::size() const
{
    return data_size;
}

template<class T>
bool Vector<T>::empty() const
{
    return size() == 0;
}

template<class T>
void Vector<T>::clear()
{
    data_size = 0;
}

template<class T>
void Vector<T>::resize(size_t n, const T &val)
{
    if (n <= size()) {
        data_size = n;
        return;
    }
    if (n > mem_size) {
        size_t new_size = mem_size * 2;
        while (new_size < n)
            new_size *= 2;
        reserve(new_size);
    }
    for (size_t i = size(); i < n; ++i)
        data[i] = val;
}

template<class T>
T& Vector<T>::operator[](size_t n)
{
    return data[n];
}

template<class T>
const T& Vector<T>::operator[](size_t n) const
{
    return data[n];
}

template<class T>
void Vector<T>::reserve(size_t s)
{
    mem_size = s;
    T * temp = new T[mem_size];
    size_t cur_size = size();
    for (size_t i = 0; i < cur_size; ++i)
        temp[i] = data[i];
    delete data;
    data = temp;
}




template class Vector<int>;
template class Vector<int*>;
template class Vector<UnorderedSet<int, std::hash<int>>::Node*>;
