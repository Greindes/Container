#ifndef UNORDEREDSET_H
#define UNORDEREDSET_H

#include<functional>
//#include"vector.h"

template<class T, class Hash = std::hash<T>>
class UnorderedSet
{
private:
    struct Node {
        T value;
        Node * next = nullptr;
        Node(const T& val) : value(val) {}
    };
public:
    UnorderedSet();
    UnorderedSet(const UnorderedSet<T, Hash>&) = delete;
    ~UnorderedSet();
    UnorderedSet<T, Hash>& operator=(const UnorderedSet<T, Hash>&) = delete;

    void insert(const T& value);
    void erase(const T& value);
    void clear();

    bool isIn(const T& value) const;

private:
    size_t bucket(const T& value) const;
    void rehash(size_t n);

    Hash hash;
    size_t bucket_count = 1000;
    size_t item_count = 0;
    Node** data;

    static constexpr float max_load = 1.0;
};

#endif // UNORDEREDSET_H
