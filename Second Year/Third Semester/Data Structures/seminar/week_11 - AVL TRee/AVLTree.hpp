#ifndef __AVL_TREE_HPP
#define __AVL_TREE_HPP

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <optional>

template<typename K, typename V> class AVLTree;

// забележете, че няма да е коректно да overload-нем оператор ==
// за позиции, понеже вече сме го направили в класа за позиция
template<typename K, typename V>
inline bool equal(typename AVLTree<K, V>::position p1, typename AVLTree<K, V>::position p2) {
  return !p1.valid() && !p2.valid()
      ||
         p1.valid() && p2.valid()
           && p1.key() == p2.key()
           && p1.value() == p2.value()
             && equal<K, V>(p1.left(), p2.left())
             && equal<K, V>(p1.right(), p2.right());
}

template<typename K, typename V>
inline bool operator==(AVLTree<K, V> const &t1, AVLTree<K, V> const &t2) {
  return equal<K, V>(t1.root(), t2.root());
}

template<typename K, typename V>
class AVLTree {
  class Position;
public:
  using position = Position;

  bool empty() const {
    return m_root == nullptr;
  }

  operator bool() const { return !empty(); }

  position root() { return position(m_root); }
  position root() const { return position(m_root); }

  void insert(K const &key, V const &value) {
    m_root = insertRec(m_root, key, value);
  }

  // ако искаме да връщаме булева стойност, бихме могли
  // да си създадем локален флаг, който да подаваме на
  // removeRec по референция, понеже няма как да връщаме
  // директно bool от removeRec
  void remove(K const &key) {
    m_root = removeRec(m_root, key);
  }

  std::optional<V> lookup(K const &key) const {
    position pos = root();

    while (pos.valid() && pos.key() != key) {
      if (pos.key() < key) {
        pos = pos.right();
      }
      else {
        pos = pos.left();
      }
    }

    return pos.valid() ? std::optional<V>{ *pos } : std::nullopt;
  }

public:
  AVLTree() : m_root(nullptr) {}

  AVLTree(AVLTree const &other)
  : m_root(copy(other.m_root)) {}

  AVLTree(AVLTree &&other) noexcept
  : m_root(std::exchange(other.m_root, nullptr)) {}

  AVLTree &operator=(AVLTree const &other) {
    if (this != &other) {
      free(m_root);
      m_root = copy(other.m_root);
    }
    return *this;
  }
  AVLTree &operator=(AVLTree &&other) noexcept {
    if (this != &other) {
      free(m_root);
      m_root = std::exchange(other.m_root, nullptr);
    }
    return *this;
  }

  ~AVLTree() { free(m_root); }

private:
  struct Node {
    K key; V value;
    Node *left, *right;
    int height;

    Node(K const &key, V const &value, Node *left=nullptr, Node *right=nullptr, int height=1)
    : height(height), key(key), value(value), left(left), right(right) {}
  };

  class Position {
  public:
    Position(Node *nodePos)
    : nodePos(nodePos) {}

    bool valid() const {
      return nodePos;
    }

    operator bool() const { return valid(); }

    bool operator==(Position const &other) const {
      return nodePos == other.nodePos;
    }

    bool operator!=(Position const &other) const {
      return nodePos != other.nodePos;
    }

    Position left() const {
      if (!valid()) {
        throw std::runtime_error("invalid position");
      }

      return Position(nodePos->left);
    }

    Position right() const {
      if (!valid()) {
        throw std::runtime_error("invalid position");
      }

      return Position(nodePos->right);
    }

    K const &key() const { return nodePos->key; }

    V &value() { return nodePos->value; }
    V const &value() const { return nodePos->value; }

    V &operator*() { return value(); }
    V const &operator*() const { return value(); }

  private:
    Node *nodePos;
  };

private:
  static int getHeight(Node *curr) {
    if (!curr) return 0;

    return curr->height;
  }

  static void updateHeight(Node *curr) {
    if (!curr) return;

    curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));
  }

  static Node *copy(Node *curr) {
    if (!curr) return curr;

    return new Node(curr->key, curr->value,
                    copy(curr->left),
                    copy(curr->right),
                    curr->height);
  }

  static void free(Node *curr) {
    if (!curr) return;

    free(curr->left);
    free(curr->right);

    delete curr;
  }

  static void rotateLeft(Node *&curr) {
    Node *tmp = curr->right;
    curr->right = tmp->left;
    tmp->left = curr;

    updateHeight(curr);
    updateHeight(tmp);

    curr = tmp;
  }

  static void rotateRight(Node *&curr) {
    Node *tmp = curr->left;
    curr->left = tmp->right;
    tmp->right = curr;

    updateHeight(curr);
    updateHeight(tmp);

    curr = tmp;
  }

  static int balanceFactor(Node *curr) {
    if (!curr) return 0;

    return getHeight(curr->left) - getHeight(curr->right);
  }

  static void balance(Node *&curr) {
    int bf = balanceFactor(curr);

    if (bf == 2) {
      if (balanceFactor(curr->left) >= 0) {
        rotateRight(curr);
      }
      else {
        rotateLeft(curr->left);
        rotateRight(curr);
      }
    }
    else if (bf == -2) {
      if (balanceFactor(curr->right) <= 0) {
        rotateLeft(curr);
      }
      else {
        rotateRight(curr->right);
        rotateLeft(curr);
      }
    }
  }

  static Node *insertRec(Node *curr, K const &key, V const &value) {
    if (!curr) return new Node(key, value);

    if (curr->key == key) {
      curr->value = value;
    }
    else if (curr->key < key) {
      curr->right = insertRec(curr->right, key, value);
    }
    else {
      curr->left = insertRec(curr->left, key, value);
    }

    updateHeight(curr);
    balance(curr);

    return curr;
  }

  static Node *removeRec(Node *curr, K const &key) {
    if (!curr) return curr;

    if (curr->key < key) {
      curr->right = removeRec(curr->right, key);
    }
    else if (curr->key > key) {
      curr->left = removeRec(curr->left, key);
    }
    else {
      if (!curr->right) {
        Node *save = curr->left;
        delete curr;
        curr = save;
      }
      else {
        Node *in = inorderSuccessor(curr->right);

        curr->key = in->key; curr->value = in->value;

        curr->right = removeRec(curr->right, in->key);
      }
    }

    updateHeight(curr);
    balance(curr);

    return curr;
  }

  static Node *inorderSuccessor(Node *curr) {
    if (!curr) return curr;
    if (!curr->left) return curr;

    return inorderSuccessor(curr->left);
  }

private:
  Node *m_root;
};

// това пак е подобно на онзи "хак" от миналия път,
// за да можем директно да използваме BinaryTreeUtils
template<typename PairType>
using AVL = AVLTree<typename PairType::first_type, typename PairType::second_type>;

#endif // __AVL_TREE_HPP