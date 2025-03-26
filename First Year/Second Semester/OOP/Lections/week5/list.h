#include <iostream>

template<class T>
struct box{
    T data;
    box *next;
};

template<class T>
class List{
public:
    List();

    // 12.2
    List(int x, int y);

    // 12.14
    ~List();
    List(const List<T> &other);

    void copyFrom(box<T> *other);

    List<T>& operator=(const List<T>& other);

    bool empty() const;
    unsigned count() const;
    void push(T);

    void clear();

    // 12.3
    void push_back(T);

    void insertAfter(T x, unsigned i);
    T& operator[](unsigned i);

    // 12.4
    List& operator+=(T);

    // 12.7
    void append(const List &other);

    void print() const;

    bool operator==(const List &other) const;
private:
    box<T> *first = nullptr;
    box<T> *pointerTo(unsigned i);
};