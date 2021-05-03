#include <iostream>
#include"deque.h"
#include"vector.h"
#include"priorityqueue.h"

int main()
{
    PriorityQueue<int> pq;
    for (int x : {1, 3, 4, 2, 0, -5, 8, 25, -99, -123, 54, 124, 45})
        pq.push(x);
    while (!pq.empty()) {
        std::cout << pq.top() << ' ';
        pq.pop();
    }
    return 0;
}
