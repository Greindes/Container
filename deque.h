#ifndef DEQUE_H
#define DEQUE_H

#include"vector.h"
#include<vector>

template<class T>
class Deque
{
private:
    static constexpr size_t CHUNK_SIZE = 100;
public:
    Deque();
    ~Deque();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void clear();

    size_t size() const;

    T& operator[](size_t i);
    const T& operator[](size_t i) const;


private:
    //c моим Vector<T*> почему-то не хочет работать
    std::vector<T*> data;
    size_t data_size = 0;
    size_t frontArrPos = 5, backArrPos = 5;
    size_t frontPos = CHUNK_SIZE / 2, backPos = CHUNK_SIZE / 2;
};

#endif // DEQUE_H
