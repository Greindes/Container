#include "unorderedset.h"

#include<iostream>

template<class T, class Hash>
UnorderedSet<T, Hash>::UnorderedSet()
{
    data.resize(bucket_count, nullptr);
}

template<class T, class Hash>
UnorderedSet<T, Hash>::~UnorderedSet()
{
    clear();
}


template<class T, class Hash>
void UnorderedSet<T, Hash>::insert(const T &value)
{
    size_t i = bucket(value);
    std::cout << "Bucket for " << value << " is " << i << '\n';
    Node * ptr = data[i];
    data[i] = new Node(value);
    data[i]->next = ptr;
    ++item_count;
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::erase(const T &value)
{
    size_t i = bucket(value);
    if (data[i] == nullptr)
        return;
    Node * ptr = data[i];
    //удаляемый элемент является первым в текущем бакете
    if (value == ptr->value) {
        data[i] = ptr->next;
        delete ptr;
        --item_count;
        return;
    }
    //вторым или далее
    while (ptr->next != nullptr && value != ptr->next->value)
        ptr = ptr->next;
    if (ptr->next != nullptr) {
        Node * del = ptr->next;
        ptr->next = del->next;
        delete del;
        --item_count;
    }
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::clear()
{
    for (size_t i = 0; i < bucket_count; ++i) {
        while (data[i] != nullptr) {
            Node * ptr = data[i];
            data[i] = ptr->next;
            delete ptr;
        }
    }
}

template<class T, class Hash>
bool UnorderedSet<T, Hash>::isIn(const T &value) const
{
    size_t i = bucket(value);
    Node * ptr = data[i];
    while (ptr != nullptr && value != ptr->value)
        ptr = ptr->next;
    return ptr != nullptr;
}

template<class T, class Hash>
size_t UnorderedSet<T, Hash>::bucket(const T &value) const
{
    return hash(value) % bucket_count;
}



template class UnorderedSet<int>;
