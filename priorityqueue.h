#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include"vector.h"

template<class T>
class PriorityQueue
{
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue<T>&) = delete;
    PriorityQueue<T>& operator=(const PriorityQueue<T>&) = delete;
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
private:
    Vector<T> data;
};

#endif // PRIORITYQUEUE_H
