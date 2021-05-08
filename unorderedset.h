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
    UnorderedSet(std::initializer_list<T> init);
    UnorderedSet(const UnorderedSet<T, Hash>&) = delete;
    ~UnorderedSet();
    UnorderedSet<T, Hash>& operator=(const UnorderedSet<T, Hash>&) = delete;

    void insert(const T& value);
    void erase(const T& value);
    void clear();

    bool isIn(const T& value) const;

    template<bool Const>
    class UnorderedSetIterator {
        friend class UnorderedSet;
        Node** data_ptr;
        Node* node_ptr = nullptr;
        size_t i = 0, size;
        explicit UnorderedSetIterator(Node**d, Node * p, size_t pos, size_t s);
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = std::conditional_t<Const, const value_type*, value_type*>;
        using reference = std::conditional_t<Const, const value_type&, value_type&>;
        using iterator_category = std::forward_iterator_tag;

        reference operator*() const;

        UnorderedSetIterator<Const>& operator++();

        UnorderedSetIterator<Const> operator++(int);

        template<bool R>
        bool operator==(const UnorderedSetIterator<R>& iter) const {
            return data_ptr == iter.data_ptr && node_ptr == iter.node_ptr;
        }
        template<bool R>
        bool operator!=(const UnorderedSetIterator<R>& iter) const {
            return !(this == iter);
        }
    };

    using iterator = UnorderedSetIterator<false>;
    using const_iterator = UnorderedSetIterator<true>;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    size_t bucket(const T& value) const;
    void rehash(size_t n);

    Hash hash;
    size_t bucket_count = 1000;
    size_t item_count = 0;
    size_t begin_pos = 1000;
    Node** data;

    static constexpr float max_load = 1.0;
};

#endif // UNORDEREDSET_H
