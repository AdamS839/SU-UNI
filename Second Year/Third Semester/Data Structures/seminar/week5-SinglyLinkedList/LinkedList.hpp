
#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class LinkedList {
private:
  struct Node {
    T data;
    Node* next;

    Node(const T& data, Node* next = nullptr)
      : data(data), next(next) {}
  };

  class Iterator {
  public:
    explicit Iterator(Node* it) : it(it) {}

    bool valid() const { return it != nullptr; }

    operator bool() const { return valid(); }

    Iterator& operator++() {
      if (it)
        it = it->next;
      return *this;
    }

    T& operator*() const {
      if (!valid())
        throw std::runtime_error("invalid iterator dereference");
      return it->data;
    }

    bool operator!=(const Iterator& other) const {
      return it != other.it;
    }

    bool operator==(const Iterator& other) const {
      return it == other.it;
    }

  private:
    Node* it;
    friend class LinkedList;
  };

public:
void rearrange();
void reorder();
void reverseConst();

public:
  using iterator = Iterator;

  // Constructors and assignment
  LinkedList() : m_begin(nullptr), m_end(nullptr), m_size(0) {}

  LinkedList(const LinkedList& other) : LinkedList() {
    copy(other);
  }

  LinkedList(LinkedList&& other) noexcept : LinkedList() {
    move(std::move(other));
  }

  LinkedList& operator=(const LinkedList& other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  LinkedList& operator=(LinkedList&& other) noexcept {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }

  ~LinkedList() {
    free();
  }

  // Iterators
  iterator begin() { return Iterator(m_begin); }
  iterator end() { return Iterator(nullptr); }

  // Capacity
  bool empty() const { return m_size == 0; }
  std::size_t size() const { return m_size; }

  // Modifiers
  void push_front(const T& data) {
    Node* node = new Node(data, m_begin);
    m_begin = node;
    if (!m_end) // list was empty
      m_end = node;
    ++m_size;
  }

  void push_back(const T& data) {
    Node* node = new Node(data);
    if (empty()) {
      m_begin = m_end = node;
    } else {
      m_end->next = node;
      m_end = node;
    }
    ++m_size;
  }

  T pop_front() {
    if (empty())
      throw std::runtime_error("pop_front from empty list");

    Node* old = m_begin;
    T data = old->data;

    m_begin = old->next;
    delete old;
    --m_size;

    if (!m_begin)
      m_end = nullptr;

    return data;
  }

  T pop_back() {
    if (empty())
      throw std::runtime_error("pop_back from empty list");

    if (m_begin == m_end)
      return pop_front();

    Node* tmp = m_begin;
    while (tmp->next != m_end)
      tmp = tmp->next;

    T data = m_end->data;
    delete m_end;
    m_end = tmp;
    m_end->next = nullptr;
    --m_size;

    return data;
  }

private:
  void copy(const LinkedList& other) {
    if (other.empty())
      return;

    Node* current = other.m_begin;
    while (current) {
      push_back(current->data);
      current = current->next;
    }
  }

  void move(LinkedList&& other) noexcept {
    m_begin = other.m_begin;
    m_end = other.m_end;
    m_size = other.m_size;

    other.m_begin = nullptr;
    other.m_end = nullptr;
    other.m_size = 0;
  }

  void free() {
    while (m_begin) {
      Node* tmp = m_begin->next;
      delete m_begin;
      m_begin = tmp;
    }
    m_end = nullptr;
    m_size = 0;
  }

private:
  Node* m_begin;
  Node* m_end;
  std::size_t m_size;
};

#endif // __LINKED_LIST_HPP
