#ifndef __SET_HPP
#define __SET_HPP

#include "../week_11 - AVL TRee/AVLTree.hpp"
#include <cstddef>
#include <stack>

// клас за множество, наследявайки от AVL дърво
template<typename T>
class Set : private AVLTree<T, bool> {
  using base = AVLTree<T, bool>;
  using position = typename base::position;

  class Iterator;
public:
  // интуиция какво всъщност прави този синтаксис
  // и защо полето m_size на обектите от тип Set
  // се копира правилно:
  // следният синтаксис казва на компилатора
  // да вземе дефинициите на Г4/Г6 от базовия
  // клас и да ги "внесе" в областта на класа
  // (bring into scope) - тоест, всичките методи
  // от Г4/Г6 стават достъпни в областта на класа.
  // тези методи от AVLTree НЕ засенчват
  // тези, които имаме по подразбиране за Set.
  // отделно от това компилаторът автоматично
  // генерира методи за Г6, като долният синтаксис
  // му казва как да създаде подобекта за AVLTree,
  // който се съдържа в обекта от тип Set.
  // в някакъв смисъл можем да си мислим, че подобектът
  // от тип AVLTree е някакъв вид поле на класа
  // (макар и не в каноничния смисъл), за което
  // имаме конструктор, за който знаем от долното твърдение.
  // тоест, все едно имаме две полета - подобектът за дървото
  // и същинското поле m_size, което само по себе си е тривиално
  // копируемо. по този начин компилаторът може автоматично да
  // създаде методите от Г6 за нас
  using typename base::AVLTree;

  using iterator = Iterator;

  bool empty() const { return base::empty(); }

  std::size_t size() const { return m_size; }

  iterator begin() { return iterator(this->root()); }
  iterator begin() const { return iterator(this->root()); } 

  iterator end() { return iterator{}; }
  iterator end() const { return iterator{}; }

  void insert(T const &el) {
    m_size++;
    return base::insert(el, true);
  }

  void remove(T const &el) {
    if (contains(el)) m_size--;
    return base::remove(el);
  }

  bool contains(T const &el) const {
    return base::lookup(el).has_value();
  }

  iterator find(T const &el) const {
    iterator iter = begin();

    while (iter != end() && *iter != el)
      ++iter;

    return iter;
  }

  friend bool operator==(Set const &s1, Set const &s2) {
    // return equal(s1.root(), s2.root());

    // това е валидно, защото самите обекти за множества
    // са сами по себе си AVL дървета и можем да приложим
    // т.нар. object slicing / upcasting
    return static_cast<base>(s1) == static_cast<base>(s2);
  }

private:
  class Iterator {
  public:
    Iterator()=default;

    Iterator(position pos) {
      pushAll(pos);
    }

    bool valid() const {
      return !iterStack.empty();
    }

    operator bool() const { return valid(); }

    T const &operator*() const {
      if (!valid())
        throw std::runtime_error("invalid iterator");

      return iterStack.top().key();
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

    bool operator==(Iterator const &other) const {
      return !valid() && !other.valid()
        || valid() && other.valid() && iterStack.top() == other.iterStack.top();
    }

    bool operator!=(Iterator const &other) const {
      return !(*this == other);
    }

  private:
    void pushAll(position pos) {
      if (!pos.valid()) return;

      pushAll(pos.right());
      iterStack.push(pos);
      pushAll(pos.left());
    }

  private:
    std::stack<position> iterStack;
  };

private:
  // размерът се копира правилно при копия
  // (дълбоко или плитко) на обекти!
  // обяснението е малко по-нагоре :)
  std::size_t m_size=0;
};

#endif // __SET_HPP
