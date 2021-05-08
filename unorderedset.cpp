#include "unorderedset.h"

#include<iostream>

template<class T, class Hash>
UnorderedSet<T, Hash>::UnorderedSet()
{
    data = new Node*[bucket_count];
    for (size_t i = 0; i < bucket_count; ++i)
        data[i] = nullptr;
}

template<class T, class Hash>
UnorderedSet<T, Hash>::UnorderedSet(std::initializer_list<T> init)
{
    bucket_count = std::max(bucket_count, init.size() * 2);
    begin_pos = bucket_count;
    data = new Node*[bucket_count];
    for (size_t i = 0; i < bucket_count; ++i)
        data[i] = nullptr;
    for (auto p = init.begin(); p != init.end(); ++p)
        insert(*p);
}

template<class T, class Hash>
UnorderedSet<T, Hash>::~UnorderedSet()
{
    clear();
    delete [] data;
}


template<class T, class Hash>
void UnorderedSet<T, Hash>::insert(const T &value)
{
    /*проверка общей загруженности бакетов
      и увеличение их количества при высокой загруженности
      (высокой вероятности не константного времени выполнения основных операций)*/
    if (float(item_count) / bucket_count > max_load)
        rehash(bucket_count * 2);

    size_t i = bucket(value);
    begin_pos = std::min(begin_pos, i);
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
    begin_pos = bucket_count;
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
typename UnorderedSet<T, Hash>::iterator UnorderedSet<T, Hash>::begin()
{
    //хэш пуст
    if (begin_pos == bucket_count)
        return end();
    return iterator(data, data[begin_pos], begin_pos, bucket_count);
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::iterator UnorderedSet<T, Hash>::end()
{
    return iterator(data, nullptr, bucket_count, bucket_count);
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::const_iterator UnorderedSet<T, Hash>::cbegin() const
{
    //хэш пуст
    if (begin_pos == bucket_count)
        return cend();
    return const_iterator(data, data[begin_pos], begin_pos, bucket_count);
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::const_iterator UnorderedSet<T, Hash>::cend() const
{
    return const_iterator(data, nullptr, bucket_count, bucket_count);
}

template<class T, class Hash>
size_t UnorderedSet<T, Hash>::bucket(const T &value) const
{
    return hash(value) % bucket_count;
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::rehash(size_t n)
{
    size_t old_size = bucket_count;
    Node ** old_data = data;
    bucket_count = n;
    begin_pos = bucket_count;
    data = new Node*[bucket_count];
    for (size_t i = 0; i < bucket_count; ++i)
        data[i] = nullptr;
    //перемещение данных в новый массив указателей из старого
    //с обновлением бакетов каждого элемента
    for (size_t i = 0; i < old_size; ++i) {
        while (old_data[i] != nullptr) {
            Node * ptr = old_data[i];
            old_data[i] = ptr->next;
            ptr->next = nullptr;
            //позиция текущего элемента при новом количестве бакетов
            size_t new_pos = bucket(ptr->value);
            begin_pos = std::min(begin_pos, new_pos);
            if (data[new_pos] != nullptr)
                ptr->next = data[new_pos];
            data[new_pos] = ptr;
        }
    }

    delete [] old_data;
}


template class UnorderedSet<int>;


template<class T, class Hash>
template<bool Const>
UnorderedSet<T, Hash>::UnorderedSetIterator<Const>::UnorderedSetIterator(UnorderedSet<T, Hash>::Node **d, UnorderedSet<T, Hash>::Node *p, size_t pos, size_t s)
    : data_ptr(d), node_ptr(p), i(pos), size(s) {}

template<class T, class Hash>
template<bool Const>
typename UnorderedSet<T, Hash>::template UnorderedSetIterator<Const>::reference UnorderedSet<T, Hash>::UnorderedSetIterator<Const>::operator*() const
{
    return node_ptr->value;
}


template<class T, class Hash>
template<bool Const>
typename UnorderedSet<T, Hash>::template UnorderedSetIterator<Const>& UnorderedSet<T, Hash>::UnorderedSetIterator<Const>::operator++()
{
    //ищет первый указатель в следующих бакетах если
    //в текущем бакете их больше нет (node_ptr->next is null)
    node_ptr = node_ptr->next;
    if (node_ptr == nullptr) {
        while (++i < size && data_ptr[i] == nullptr)
            continue;
    }
    if (i < size)
        node_ptr = data_ptr[i];
    else
        node_ptr = nullptr;
    return *this;
}

template<class T, class Hash>
template<bool Const>
typename UnorderedSet<T, Hash>::template UnorderedSetIterator<Const> UnorderedSet<T, Hash>::UnorderedSetIterator<Const>::operator++(int)
{
    auto res = *this;
    ++(*this);
    return res;
}
