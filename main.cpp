#include <iostream>
#include"deque.h"
#include"vector.h"

int main()
{
    std::cout << "Hello, world";
    Deque<int> deq;
    for (int i = 100; i < 200; ++i)
        deq.push_back(i);
    for (int i = 0; i < 100; ++i)
        deq.push_front(i);
    while (deq.size() > 0) {
        deq.pop_back();
        deq.pop_front();
        std::cout << deq.size() << ' ';
    }
    return 0;
}
