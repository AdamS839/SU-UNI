#ifndef __DICTIONARY_HPP
#define __DICTIONARY_HPP

#include "avltree.hpp"
#include <optional>
#include <stack>
#include <stdexcept>

// имплементация на речник чрез балансирано (AVL) дърво,
// където операциите са със сложности O(logn)
template<typename K, typename V>
class Dictionary {
  class Iterator;
public:
  using iterator = Iterator;

  iterator begin() { return Iterator(tree.root()); }
  iterator begin() const { return Iterator(tree.root()); }

  iterator end() { return Iterator(); }
  iterator end() const { return Iterator(); }

  bool empty() const { return tree.empty(); }

  iterator find(K const &key) const {
    iterator iter = begin();

    while (iter != end() && iter.key() != key)
      ++iter;

    return iter;
  }

  void insert(K const &key, V const &value) {
    m_size++;
    tree.insert(key, value);
  }

  void remove(K const &key) {
    if (lookup(key).has_value()) m_size--;
    tree.remove(key);
  }

  std::optional<V> lookup(K const &key) const {
    return tree.lookup(key);
  }

  // забележете, че lookup НЯМА да работи тук,
  // понеже копира стойността, а тук връщаме референция,
  // т.е. ще имаме висяща референция
  V &operator[](K const &key) {
    typename AVLTree<K, V>::position pos = tree.root();

    while (pos.valid() && pos.key() != key) {
      if (pos.key() < key) {
        pos = pos.right();
      }
      else {
        pos = pos.left();
      }
    }

    return pos.value();
  }

  V const &operator[](K const &key) const {
    typename AVLTree<K, V>::position pos = tree.root();

    while (pos.valid() && pos.key() != key) {
      if (pos.key() < key) {
        pos = pos.right();
      }
      else {
        pos = pos.left();
      }
    }

    return pos.value();
  }

private:
  using position = typename AVLTree<K,V>::position;
  class Iterator {
  public:
    // трябва ни за end()
    Iterator()=default;
    // забележете, че създаването на итератор тук
    // е линейно по сложност и по памет
    Iterator(position pos) {
      makeStack(pos, iterStack);
    }

    bool valid() const { return !iterStack.empty(); }

    K const &key() const {
      if (!valid())
        throw std::runtime_error("invalid iterator");

      return iterStack.top().key(); 
    }

    // това изглежда странно, но веднъж взимаме
    // текущия обект, като дереференцираме this -
    // ~> *this, след което извикваме operator*
    // за същия този обект - *(*this)
    V &value() { return **this; }
    V const &value() const { return **this; }

    V &operator*() {
      if (!valid())
        throw std::runtime_error("invalid iterator");

      return *iterStack.top();
    }

    V const &operator*() const {
      if (!valid())
        throw std::runtime_error("invalid iterator");

      return *iterStack.top();
    }

    bool operator==(Iterator const &other) const {
      return iterStack.empty() && other.iterStack.empty()
          || !iterStack.empty() && !other.iterStack.empty()
              && iterStack.top() == other.iterStack.top();
    }

    bool operator!=(Iterator const &other) const {
      return !(*this == other);
    }

    Iterator &operator++() {
      if (!valid())
        throw std::runtime_error("invalid iterator");

      iterStack.pop();
      return *this;
    }

    Iterator operator++(int) {
      Iterator cpy = *this;
      ++*this;
      return cpy;
    }

  private:
    static void makeStack(position pos, std::stack<position> &stack) {
      if (!pos.valid())
        return;

      makeStack(pos.right(), stack);
      stack.push(pos);
      makeStack(pos.left(), stack);
    }

  private:
    std::stack<position> iterStack;
  };

private:
  AVLTree<K, V> tree;
  size_t m_size=0;
};

#endif // __DICTIONARY_HPP