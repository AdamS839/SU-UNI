#ifndef __BST_HPP
#define __BST_HPP

#include "BinTrees.hpp"
#include <optional>
#include <ostream>
#include <algorithm>
#include <vector>

template<typename T, typename U>
struct Pair {
  T first;
  U second;

  // по този начин създаваме типови синоними
  // за типовете, които подаваме като типови параметри.
  // позволяват ни да правим готини трикове с типовата система
  // и да метапрограмираме. полезни са за типовия синоним
  // в края на този файл ;)
  using first_type = T;
  using second_type = U;

  bool operator==(Pair const &other) const {
    return first == other.first;
  }

  bool operator!=(Pair const &other) const {
    return first != other.first;
  }

  // трябва ни за наредбата :)
  bool operator<(Pair const &other) const {
    return first < other.first;
  }

  bool operator<=(Pair const &other) const {
    return first <= other.first;
  }

  friend std::ostream &operator<<(std::ostream &os, Pair const &pair) {
    os << "(" << pair.first << "," << pair.second << ")";
    return os;
  }
};

template<typename K, typename V>
class BST : public BinaryTree<Pair<K, V> >  {
  using kvp = Pair<K,V>;
  using BT = BinaryTree<kvp>;
  using Node = typename BT::BTNode;

public:
  using position = typename BT::position;

  void insert(K const &key, V const &value) {
    // тук е важно да свържем резултата от search
    // с референция, вместо да правим копие (Node *)
    Node *&node = search(this->m_root, key);
    if (node != nullptr) {
      node->data.second = value;
    }
    else {
      node = new Node({key, value});
    }
  }

  bool remove(K const &key) {
    Node *&node = search(this->m_root, key);
    if (node == nullptr) {
      return false;
    }

    if (!node->right) {
      Node *save = node->left;
      delete node;
      node = save;
      return true;
    }

    Node *&in = inorderSuccessor(node);

    node->data = in->data;
    Node *toDelete = in;
    in = in->right;
    delete toDelete;

    return true;
  }

  // или връщаме стойност от тип V, или връщаме "нищо".
  // писали сме такъв клас по ООП ;)
  // аналогично на Maybe в Haskell
  std::optional<V> lookup(K const &key) const {
    Node *const &node = search(this->m_root, key);
    if (node == nullptr) {
      return std::nullopt;
    }
    else {
      return { node->data.second };
    }
  }

  std::vector<kvp> inorder() const {
    std::vector<kvp> result;
    inorder(this->m_root, result);
    return result;
  }

  // понеже инвариантът на двоичните дървета за търсене
  // е изпълнен за всяко поддърво, можем да вземем
  // инфиксното обхождане от произволен връх на поддърво
  std::vector<kvp> inorder(position pos) const {
    std::vector<kvp> result;
    inorder(pos, result);
    return result;
  }

  // това може да доведе до повторения на ключове,
  // ако в самия вектор има повторения
  static BST fromVector(std::vector<kvp> v) {
    std::sort(v.begin(), v.end());

    // затова можем да премахнем повторенията :)
    // по този начин запазваме първото срещане
    // на първия ключ, иначе бихме могли да напишем
    // своя функция, която да запазва последното.
    // бихме могли и да направим следното:
    // reverse -> unique + erase -> reverse
    v.erase(std::unique(v.begin(), v.end()));

    return fromVector(v, 0, v.size()-1);
  }

public:
  BST() : BT::BinaryTree() {}

  BST(BST const &other)
  : BT::BinaryTree(other) {}

  BST(BST &&other) noexcept
  : BT::BinaryTree(std::move(other)) {}

  BST &operator=(BST const &other) {
    return BT::operator=(other);
  }

  BST &operator=(BST &&other) noexcept {
    return BT::operator=(std::move(other));
  }

  ~BST()=default;

private:
  BST(K const &key, V const &value, BST const &left, BST const &right)
  : BT::BinaryTree({key,value}, left, right) {}

  BST(kvp const &pair, BST const &left, BST const &right)
  : BT::BinaryTree(pair, left, right) {}

private:
  static Node *&search(Node *&curr, K const &key) {
    Node **iter = &curr;
    while (*iter && (*iter)->data.first != key) {
      if ((*iter)->data.first < key) {
        iter = &(*iter)->right;
      }
      else {
        iter = &(*iter)->left;
      }
    }
    return *iter;
  }

  // константен overload на горната статична функция.
  // тази също трябваше да е статична (или да беше константен метод,
  // макар че в конретния случай е излишно, понеже тази функция по никакъв
  // начин не се обвързва с обекти на класа)
  static Node *const &search(Node *const &curr, K const &key) {
    Node *const *iter = &curr;
    while (*iter && (*iter)->data.first != key) {
      if ((*iter)->data.first < key) {
        iter = &(*iter)->right;
      }
      else {
        iter = &(*iter)->left;
      }
    }
    return *iter;
  }

  static void inorder(Node *curr, std::vector<kvp> &result) {
    if (!curr) return;

    inorder(curr->left, result);
    result.push_back(curr->data);
    inorder(curr->right, result);
  }

  // горното, но с позиция
  static void inorder(position pos, std::vector<kvp> &result) {
    if (!pos.valid()) return;

    inorder(pos.left(), result);
    result.push_back(*pos);
    inorder(pos.right(), result);
  }

  static BST fromVector(std::vector<Pair<K, V> > const &vec, int low, int high) {
    if (low > high) return BST{};

    int mid = low + (high - low) / 2;
    return BST(vec[mid],
                  fromVector(vec, low, mid-1),
                  fromVector(vec, mid+1, high));
  }

  // за дадена стойност във възела curr
  // inorderSuccessor връща възела в дървото,
  // който е с най-малката по-голяма или равна
  // на curr->data.first стойност.
  // иначе казано, това е следващият елемент
  // след curr->data в инфиксното обхождане
  static Node *&inorderSuccessor(Node *&curr) {
    // забележете, че тук не искаме да връщаме
    // nullptr директно, дори и долните възли да
    // имат тази стойност (а и е невъзможно,
    // понеже няма как rvalue стойност - nullptr,
    // да се свърже с lvalue референция)
    if (!curr) return curr;
    if (!curr->right) return curr->right;

    Node **tmp = &curr->right;
    while ((*tmp)->left) {
      // най-външните скоби са излишни,
      // но така е малко по-ясно какво се случва
      tmp = &((*tmp)->left);
    }

    return *tmp;
  }

  // за пълнота
  static Node *&inorderPredecessor(Node *&curr) {
    if (!curr) return curr;
    if (!curr->left) return curr->left;

    Node **tmp = &curr->left;
    while ((*tmp)->right) {
      tmp = &(*tmp)->right;
    }

    return *tmp;
  }
};

// тъй като искаме да използваме класа BinaryTreeUtil, който писахме миналия път,
// трябва да имаме типов конструктор за BST, който да приема единствен типов параметър
// (понеже BinaryTreeUtil очаква едноместен типов конструктор, а BST приема два типови
// параметъра - K и V). по този начин създаваме типов синоним за BST, който приема
// пълен тип (0-местен типов конструктор в някакъв смисъл) за наредена двойка
// (напр. PairType = Pair<int, std::string>) и създава типовия синоним BSTU,
// като конкретизира типовите параметри на BST. например, за PairType = Pair<int, std::string>,
// BSTU = BST<int, std::string>, където
// PairType::first_type = int, PairType::second_type = std::string
template<typename PairType>
using BSTU = BST<typename PairType::first_type, typename PairType::second_type>;

#endif // __BST_HPP