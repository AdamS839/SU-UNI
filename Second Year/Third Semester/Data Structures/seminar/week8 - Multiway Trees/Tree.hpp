#ifndef __TREE_HPP
#define __TREE_HPP

#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Tree {
public:
  Tree(T const &root, std::vector<Tree<T> > children=std::vector<Tree<T> >{})
  : m_root(root), m_children(std::move(children)) {}

  void addSubtree(Tree const &t) {
    m_children.push_back(t);
  }

  void addSubtree(Tree &&t) {
    m_children.push_back(std::move(t));
  }

  T &root() { return m_root; }
  T const &root() const { return m_root; }

  std::vector<Tree<T> > const &children() const { return m_children; }

  bool leaf() const {
    return m_children.empty();
  }

  void print(std::ostream &os=std::cout) {
    print(*this, "", false, os);
  }

private:
  void print(Tree const &t, std::string const &prefix, bool isLeft, std::ostream &os) {
    os << prefix;

    os << (isLeft ? "+-- " : "|-- ");

    os << t.root() << std::endl;

    std::vector<Tree<T> > const& cs = t.children();
    for (std::size_t i = 0; i < cs.size(); ++i) {
        bool lastChild = i == cs.size() - 1;
        print(cs[i],
              prefix + (isLeft ? "    " : "|   "),
              lastChild,
              os);
    }
  }

private:
  T m_root;
  std::vector<Tree<T> > m_children;
};

#endif // __TREE_HPP
