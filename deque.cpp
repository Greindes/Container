#include "deque.h"


template<class T>
Deque<T>::Deque() : data(10, nullptr)
{
}

template<class T>
void Deque<T>::push_back(const T &value)
{
    if (size == 0) {
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
    ++size;
}

template<class T>
void Deque<T>::push_front(const T &value)
{
    if (size == 0) {
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
    ++size;
}

template<class T>
T &Deque<T>::operator[](size_t i)
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
