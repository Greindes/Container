#include "priorityqueue.h"

template<class T>
PriorityQueue<T>::PriorityQueue()
{

}

template<class T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<T> init)
{
    for (auto p = init.begin(); p != init.end(); ++p)
        push(*p);
}

template<class T>
void PriorityQueue<T>::push(const T &value)
{
    data.push_back(value);
    size_t child = data.size() - 1;
    while (child > 0) {
        size_t parent = (child - 1) / 2;
        if (data[parent] >= data[child])
            return;
        std::swap(data[child], data[parent]);
        child = parent;
    }
}

template<class T>
void PriorityQueue<T>::pop()
{
    if (data.size() == 1) {
        data.pop_back();
        return;
    }
    std::swap(data[0], data[data.size() - 1]);
    data.pop_back();
    size_t parent = 0, size = data.size();
    while (parent * 2 + 2 < size && (data[parent] < data[2*parent + 1] || data[parent] < data[2*parent + 2])) {
           size_t child = data[2*parent + 1] > data[2*parent + 2] ? (2*parent + 1) : (2*parent + 2);
           std::swap(data[parent], data[child]);
           parent = child;
    }
    //случай когда есть только 1 "потомок" для сравнения
    if (parent * 2 + 2 == size && data[parent] < data[2*parent + 1])
        std::swap(data[parent], data[2*parent + 1]);
}

template<class T>
const T &PriorityQueue<T>::top() const
{
    return data[0];
}

template<class T>
bool PriorityQueue<T>::empty() const
{
    return data.empty();
}

template class PriorityQueue<int>;
