#ifndef SET_H
#define SET_H

template<class T>
class Set
{
private:
    enum class Color { RED, BLACK };
    struct Node {
        T value;
        Color color;
        Node * parent = nullptr;
        Node * left = nullptr;
        Node * right = nullptr;
        Node(const T& val, Color col) : value(val), color(col) {}
    };

    Node* root = nullptr;
public:
    Set();

    void insert(const T& key);
    void erase(const T& key);
    bool isIn(const T& key);
};

#endif // SET_H
