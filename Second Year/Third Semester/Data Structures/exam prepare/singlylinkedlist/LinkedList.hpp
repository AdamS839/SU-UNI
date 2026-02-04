    #ifndef __LINKED_LIST_HPP
    #define __LINKED_LIST_HPP

    #include <cstddef>
    #include <stdexcept>

    template<typename T>
    class LinkedList {
    private:
    class Iterator;

    public:
    using iterator = Iterator;

    Iterator begin() { return Iterator(m_begin); }

    Iterator end() { return Iterator(nullptr); }

    bool empty() const {
        return !m_begin;
    }

    std::size_t size() const {
        return m_size;
    }

    void push_front(T const &data) {
        m_size++;
        Node *node = new Node(data);

        if (empty()) {
        m_begin = m_end = node;
        return;
        }

        node->next = m_begin;
        m_begin = node;
    }

    void push_back(T const &data) {
        m_size++;

        Node *node = new Node(data);
        if (empty()) {
        m_begin = m_end = node;
        return;
        }

        m_end->next = node;
        m_end = node;
    }

    T pop_front() {
        if (empty())
        throw std::runtime_error("empty list");

        m_size--;

        T result = m_begin->data;

        Node *save = m_begin->next;

        delete m_begin;
        m_begin = save;

        if (!m_begin)
        m_end = nullptr;

        return result;
    }

    T pop_back() {
        if (empty())
        throw std::runtime_error("empty list");

        if (size() == 1) {
        return pop_front();
        }

        m_size--;
        T result = m_end->data;

        // искаме tmp да съдържа предпоследния елемент в списъка
        Node *tmp = m_begin;
        while (tmp->next->next) {
        tmp = tmp->next;
        }

        delete m_end;
        m_end = tmp;

        m_end->next = nullptr;

        return result;
    }

    public:
    LinkedList()
    : m_begin(nullptr), m_end(nullptr), m_size(0) {}

    LinkedList(LinkedList const &other) : LinkedList() {
        copy(other);
    }

    LinkedList(LinkedList &&other) noexcept {
        move(std::move(other));
    }

    LinkedList &operator=(LinkedList const &other) {
        if (this != &other) {
        free();
        copy(other);
        }
        return *this;
    }

    LinkedList &operator=(LinkedList &&other) noexcept {
        if (this != &other) {
        free();
        move(std::move(other));
        }
        return *this;
    }

    ~LinkedList() {
        free();
    }



    private:
    struct Node {
        T data;
        Node *next;

        Node(T const &data, Node *next=nullptr)
        : data(data), next(next) {}
    };

    public:
    void reverse();
    bool isPalindrome();
    void rearrange();
    void reorder();
    
    private:
    class Iterator {
    public:
        Iterator(Node *it) : it(it) {}

        bool valid() const { return it; }

        operator bool() const { return valid(); }

        Iterator &operator++() {
        if (it)
            it = it->next;

        return *this;
        }

        T &operator*() const {
        if (!valid())
            throw std::runtime_error("invalid iterator");

        return it->data;
        }

        bool operator!=(Iterator const &other) const {
        return it != other.it;
        }

        bool operator==(Iterator const &other) const {
        return !(other != *this);
        }

    private:
        Node *it;
    };

    private:
    void copy(LinkedList const &other) {
        // push_back
        // push_front + reverse

        if (other.empty()) return;

        m_size = other.m_size;

        Node *tmp = new Node(other.m_begin->data);
        m_begin = tmp;

        Node *otmp = other.m_begin->next;

        while (otmp) {
        tmp->next = new Node(otmp->data);
        tmp = tmp->next;
        otmp = otmp->next;
        }

        m_end = tmp;
    }

    void move(LinkedList &&other) noexcept {
        m_begin = other.m_begin;
        m_end = other.m_end;
        m_size = other.m_size;

        other.m_begin = nullptr;
        other.m_end = nullptr;
        other.m_size = 0;
    }

    void free() {
        Node *tmp;
        while (m_begin) {
        tmp = m_begin->next;
        delete m_begin;
        m_begin = tmp;
        }
    }

    private:
    Node *m_begin;
    Node *m_end;
    std::size_t m_size;

    };

    #endif // __LINKED_LIST_HPP