#ifndef __BINARY_TREE_HPP
#define __BINARY_TREE_HPP

#include <stdexcept>
#include <utility>

template<typename T>
class BinaryTree {
  class Position;
public:
  using position = Position;

  bool empty() const {
    return !m_root;
  }

  operator bool() const {
    return !empty();
  }

  position root()       { return position(m_root); }

  position root() const { return position(m_root); }

  // тези ги закоментирахме, защото BST наследява този клас ;)
  // поведението им е лесно за симулация чрез конструкторите
  // BinaryTree(T const &, BinaryTree const &, BinaryTree const &) и
  // BinaryTree(T const &, BinaryTree &&, BinaryTree &&)

  // void addLeftSubtree(position treePos, BinaryTree const &subtree) {
    // if (!treePos.valid())
      // throw std::runtime_error("invalid position");

    // if (treePos.left().valid()) {
      // free(treePos.pos->left);
    // }
    // treePos.pos->left = copy(subtree.m_root);
  // }

  // void addLeftSubtree(position treePos, BinaryTree &&subtree) {
    // if (!treePos.valid())
      // throw std::runtime_error("invalid position");

    // if (treePos.left().valid()) {
      // free(treePos.pos->left);
    // }
    // treePos.pos->left = std::exchange(subtree.m_root, nullptr);
  // }

  // void addRightSubtree(position treePos, BinaryTree const &subtree) {
    // if (!treePos.valid())
      // throw std::runtime_error("invalid position");

    // if (treePos.right().valid()) {
      // free(treePos.pos->right);
    // }
    // treePos.pos->right = copy(subtree.m_root);
  // }

  // void addRightSubtree(position treePos, BinaryTree &&subtree) {
    // if (!treePos.valid())
      // throw std::runtime_error("invalid position");

    // if (treePos.right().valid()) {
      // free(treePos.pos->right);
    // }
    // treePos.pos->right = std::exchange(subtree.m_root, nullptr);
  // }

public:
  BinaryTree() : m_root(nullptr) {}

  BinaryTree(T const &root)
  : m_root(new Node(root)) {}

  BinaryTree(T const &root, 
             BinaryTree const &left,
             BinaryTree const &right)
  : m_root(new Node(root)) {
    m_root->left = copy(left.m_root);
    m_root->right = copy(right.m_root);
  }

  BinaryTree(T const &root, BinaryTree &&left, BinaryTree &&right)
  : m_root(new Node(root, left.m_root, right.m_root)) {
    left.m_root = nullptr;
    right.m_root = nullptr;
  }

  BinaryTree(BinaryTree const &other)
  : m_root(copy(other.m_root)) {}

  BinaryTree(BinaryTree &&other) noexcept
  : m_root(std::exchange(other.m_root, nullptr)) {}

  BinaryTree &operator=(BinaryTree const &other) {
    if (this != &other) {
      free(m_root);
      m_root = copy(other.m_root);
    }
    return *this;
  }

  BinaryTree &operator=(BinaryTree &&other) noexcept {
    if (this != &other) {
      free(m_root);
      m_root = std::exchange(other.m_root, nullptr);
    }
    return *this;
  }

  ~BinaryTree() { free(m_root); }

private:
  struct Node {
    T data;
    Node *left, *right;

    Node(T const &data, Node *left=nullptr, Node *right=nullptr)
    : data(data), left(left), right(right) {}
  };

  class Position {
    friend class BinaryTree<T>;
  public:
    Position(Node *pos) : pos(pos) {}

    bool valid() const {
      return pos;
    }

    operator bool() const {
      return valid();
    }

    bool operator!=(Position const &other) const {
      return pos != other.pos;
    }

    bool operator==(Position const &other) const {
      return pos == other.pos;
    }

    T &operator*() {
      if (!valid())
        throw std::runtime_error("invalid position");

      return pos->data;
    }

    T const &operator*() const {
      if (!valid())
        throw std::runtime_error("invalid position");

      return pos->data;
    }

    Position left() const {
      if (!valid())
        throw std::runtime_error("invalid position");

      return Position(pos->left);
    }

    Position right() const {
      if (!valid())
        throw std::runtime_error("invalid position");

      return Position(pos->right);
    }

    Position operator-() const {
      return left();
    }

    Position operator+() const {
      return right();
    }

    Position &operator--() {
      return *this = left();
    }

    Position &operator++() {
      return *this = right();
    }

    Position operator--(int) {
      Position save = *this;
      --(*this);
      return save;
    }

    Position operator++(int) {
      Position save = *this;
      ++(*this);
      return save;
    }

    // RAII е идиом, според който всеки клас/структура/функция,
    // които заделят някакви ресурси, са длъжни след това
    // (след края на функцията, с разрушаването на обект от клас),
    // да освободят тези ресурси. в случая Position класът не заделя
    // памет за Node *pos, така че няма нужда да пишем деструктор,
    // в който да освобождаваме паметта, която се сочи от pos
    // ~Position() { delete pos; }

  private:
    Node *pos;
  };

private:
  Node *copy(Node *pos) {
    if (!pos) return pos;

    Node *root = new Node(pos->data);
    root->left = copy(pos->left);
    root->right = copy(pos->right);

    return root;
  }

  void free(Node *pos) {
    if (!pos) return;

    free(pos->left);
    free(pos->right);
    delete pos;
    pos = nullptr;
  }

protected:
  Node *m_root;

  // типов синоним за типа Node, който е в protected секция,
  // понеже така няма нужда да правим целия Node клас protected
  using BTNode = Node;
};

#endif // __BINARY_TREE_HPP
