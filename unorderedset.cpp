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

template<class T, class Hash>
void UnorderedSet<T, Hash>::rehash(size_t n)
{
    size_t old_size = bucket_count;
    Node ** old_data = data;
    bucket_count = n;
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
            if (data[new_pos] != nullptr)
                ptr->next = data[new_pos];
            data[new_pos] = ptr;
        }
    }

    delete [] old_data;
}



template class UnorderedSet<int>;
