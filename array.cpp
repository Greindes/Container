#include "array.h"



template<class T, unsigned int N>
Array<T, N>::Array()
{
    createData();
}

template<class T, size_t N>
Array<T, N>::Array(const Array<T, N> &arr)
{
    createData();
    for (size_t i = 0; i < N; ++i)
        data[i] = arr[i];
}

template<class T, size_t N>
Array<T, N>::Array(std::initializer_list<T> init)
{
    createData();
    size_t i = 0;
    for (auto p = init.begin(); p != init.end(); ++p)
        data[i++] = *p;
}

template<class T, unsigned int N>
Array<T, N>::~Array()
{
    delete[] data;
}

template<class T, size_t N>
T& Array<T, N>::operator[](size_t n)
{
    return data[n];
}

template<class T, size_t N>
Array<T, N>& Array<T, N>::operator=(const Array<T, N> arr)
{
    for (size_t i = 0; i < N; ++i)
        data[i] = arr[i];
    return *this;
}

template<class T, size_t N>
size_t Array<T, N>::size() const
{
    return N;
}

template<class T, size_t N>
const T& Array<T, N>::operator[](size_t n) const
{
    return data[n];
}


template<class T, unsigned int N>
void Array<T, N>::createData()
{
    data = new T[N];
}


template class Array<int, 100>;
