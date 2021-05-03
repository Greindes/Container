#ifndef LIST_H
#define LIST_H

#include<type_traits>
#include<iterator>

template<class T>
class List
{
private:
    struct ListNode {
        T value;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        ListNode(const T& v) : value(v) {}
    };
public:
    List();
    List(const List<T>& l);
    ~List();
    List<T>& operator=(const List<T>& l);
    void deepCopy(const List<T>& l);
    size_t size() const;
    bool empty() const;
    void clear();

    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    template<bool Const>
    class ListIterator {
        friend class List;
        List<T>::ListNode* ptr;
        explicit ListIterator(List<T>::ListNode* p) : ptr(p) {}
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = typename std::conditional<Const, const value_type*, value_type*>::type;
        using reference = typename std::conditional<Const, const value_type&, value_type&>::type;
        using iterator_category = std::bidirectional_iterator_tag;

        reference operator*() const { return ptr->value; }
        ListIterator<Const>& operator++() { ptr = ptr->next; return *this; }
        ListIterator<Const> operator++(int) { auto res = *this; ++(*this); return res; }
        ListIterator<Const>& operator--() { ptr = ptr->prev; return *this; }
        ListIterator<Const> operator--(int) { auto res = *this; --(*this); return res; }

        template<bool C>
        bool operator==(const ListIterator<C>& iter) { return ptr == iter.ptr; }
        template<bool C>
        bool operator!=(const ListIterator<C>& iter) { return ptr != iter.ptr; }
    };

    using iterator = ListIterator<false>;
    using const_iterator = ListIterator<true>;

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
    const_iterator cbegin() const { return const_iterator(head); }
    const_iterator cend() const { return const_iterator(nullptr); }

private:
    size_t list_size = 0;
    ListNode * head = nullptr;
    ListNode * tail = nullptr;
};

#endif // LIST_H
