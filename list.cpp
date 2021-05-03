#include "list.h"


template<class T>
List<T>::List()
{

}

template<class T>
List<T>::~List()
{
    clear();
}

template<class T>
void List<T>::deepCopy(const List<T> &l)
{
    clear();
    ListNode* ptr = l.head;

    while(ptr) {
        push_back(ptr->value);
        ptr = ptr->next;
    }
}

template<class T>
size_t List<T>::size() const
{
    return list_size;
}

template<class T>
bool List<T>::empty() const
{
    return size() == 0;
}

template<class T>
void List<T>::clear()
{
    while (head) {
        ListNode* ptr = head->next;
        delete head;
        head = ptr;
    }
    tail = nullptr;
}

template<class T>
void List<T>::push_back(const T &value)
{
    ListNode* ptr = new ListNode(value);
    if (list_size == 0) {
        head = ptr;
        tail = ptr;
    } else {
        tail->next = ptr;
        tail = tail->next;
    }
    ++list_size;
}

template<class T>
void List<T>::pop_back()
{
    ListNode* ptr = tail;
    if (list_size == 1)
        head = tail = nullptr;
    else
        tail = tail->prev;
    delete ptr;
    --list_size;
}

template<class T>
void List<T>::push_front(const T &value)
{
    ListNode* ptr = new ListNode(value);
    if (list_size == 0) {
        head = tail = ptr;
    } else {
        head->prev = ptr;
        head = head->prev;
    }
    ++list_size;
}

template<class T>
void List<T>::pop_front()
{
    ListNode* ptr = head;
    if (list_size == 1)
        head = tail = nullptr;
    else
        head = head->next;
    delete ptr;
    --list_size;
}

template<class T>
T& List<T>::front()
{
    return head->value;
}

template<class T>
const T& List<T>::front() const
{
    return head->value;
}

template<class T>
T& List<T>::back()
{
    return tail->value;
}

template<class T>
const T& List<T>::back() const
{
    return tail->value;
}

template class List<int>;
