#include "vector.h"


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
        set_size(vec.mem_size);
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
        set_size(mem_size * 2);
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
void Vector<T>::clear()
{
    data_size = 0;
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
void Vector<T>::set_size(size_t s)
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

