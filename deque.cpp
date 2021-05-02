#include "deque.h"


template<class T>
Deque<T>::Deque() : data(10, nullptr)
{
}

template<class T>
Deque<T>::~Deque()
{
    clear();
}

template<class T>
void Deque<T>::push_back(const T &value)
{
    if (data_size == 0) {
        backArrPos = data.size() / 2;
        backPos = CHUNK_SIZE / 2;
        frontArrPos = data.size() / 2;
        frontPos = (CHUNK_SIZE / 2);
        data[backArrPos] = new T[CHUNK_SIZE];
    }
    //нужно выделить память для чанка backArrPos + 1
    else if (backPos == CHUNK_SIZE) {
    //не забудь про backArrPos >= size
        ++backArrPos;
        backPos = 0;
        if (data.size() == backArrPos)
            data.push_back(nullptr);
        data[backArrPos] = new T[CHUNK_SIZE];
    }
    data[backArrPos][backPos++] = value;
    ++data_size;
}

template<class T>
void Deque<T>::push_front(const T &value)
{
    if (data_size == 0) {
        push_back(value);
        return;
    }
    //нужно ли выделить память для чанка в max(frontArrPos - 1, 0)
    if (frontPos == 0) {
        frontPos = CHUNK_SIZE;
        //при fronArrPos == 0 необходимо сдвинуть все указатели на чанки для места новому указателю первого чанка
        if (frontArrPos == 0) {
            data.push_back(nullptr);
            for (size_t i = data.size() - 1; i > 0; --i)
                data[i] = data[i - 1];
        } else {
            --frontArrPos;
        }
        data[frontArrPos] = new T[CHUNK_SIZE];
    }
    data[frontArrPos][--frontPos] = value;
    ++data_size;
}

template<class T>
void Deque<T>::pop_back()
{
    if (data_size == 1) {
        clear();
        return;
    }
    if (backPos == 1) {
        delete data[backArrPos--];
        backPos = CHUNK_SIZE;
    } else
        --backPos;
    --data_size;
}

template<class T>
void Deque<T>::pop_front()
{
    if (data_size == 1) {
        clear();
        return;
    }
    if (frontPos == CHUNK_SIZE - 1) {
        delete data[frontArrPos++];
        frontPos = 0;
    } else
        ++frontPos;
    --data_size;
}

template<class T>
void Deque<T>::clear()
{
    if (data_size > 0) {
        for (size_t i = frontArrPos; i <= backArrPos; ++i)
            delete data[i];
    }
    data_size = 0;
}

template<class T>
size_t Deque<T>::size() const
{
    return data_size;
}

template<class T>
T& Deque<T>::operator[](size_t i)
{
    size_t arrPos = i / CHUNK_SIZE;
    i = (i % CHUNK_SIZE) + frontPos;
    if (i >= CHUNK_SIZE) {
        i %= CHUNK_SIZE;
        ++arrPos;
    }
    return data[frontArrPos + arrPos][i];
}

template<class T>
const T& Deque<T>::operator[](size_t i) const
{
    size_t arrPos = i / CHUNK_SIZE;
    i = (i % CHUNK_SIZE) + frontPos;
    if (i >= CHUNK_SIZE) {
        i %= CHUNK_SIZE;
        ++arrPos;
    }
    return data[frontArrPos + arrPos][i];
}

template class Deque<int>;
