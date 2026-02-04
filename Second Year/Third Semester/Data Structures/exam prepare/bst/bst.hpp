#ifndef __BST_HPP
#define __BST_HPP

#include <stdexcept>
#include <utility>
#include <vector>

template<typename T>
class BST {
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node(T const &data, Node *l=nullptr, Node *r=nullptr)
            : data(data), left(l), right(r) {}
    };

public:
    class Position {
        friend class BST<T>;
        Node *pos;

        Position(Node *p) : pos(p) {}

    public:
        Position() : pos(nullptr) {}

        bool valid() const { return pos != nullptr; }

        operator bool() const { return valid(); }

        T &operator*() {
            if (!pos) throw std::runtime_error("invalid position");
            return pos->data;
        }

        T const &operator*() const {
            if (!pos) throw std::runtime_error("invalid position");
            return pos->data;
        }

        Position left() const {
            if (!pos) throw std::runtime_error("invalid position");
            return Position(pos->left);
        }

        Position right() const {
            if (!pos) throw std::runtime_error("invalid position");
            return Position(pos->right);
        }
    };

public:
    BST() : root_(nullptr) {}

    BST(BST const &other) : root_(copy(other.root_)) {}

    BST(BST &&other) noexcept : root_(other.root_) {
        other.root_ = nullptr;
    }

    BST &operator=(BST const &other) {
        if (this != &other) {
            clear(root_);
            root_ = copy(other.root_);
        }
        return *this;
    }

    BST &operator=(BST &&other) noexcept {
        if (this != &other) {
            clear(root_);
            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }

    ~BST() {
        clear(root_);
    }

    bool empty() const {
        return root_ == nullptr;
    }

    Position root() const {
        return Position(root_);
    }

    // 🔹 INSERT
    void insert(T const &x) {
        insert(root_, x);
    }

    // 🔹 SEARCH
    bool contains(T const &x) const {
        return contains(root_, x);
    }

    // sdp problem 2 BST
    std::vector<T> inorder() const {
        std::vector<T> result;
        inorder(this->root(), result);
        return result;
    }

    std::vector<T> preorder() const {
        std::vector<T> result;
        preorder(this->root(), result);
        return result;
    }

private:
    Node *root_;

private:

    static void preorder(Position pos, std::vector<T> &result){
        if (!pos.valid()) return;

        result.push_back(*pos);
        preorder(pos.left(), result);
        preorder(pos.right(), result);
    }

    // sdp problem 2 BST
    static void inorder(Position pos, std::vector<T> &result){
        if (!pos.valid()) return;

        inorder(pos.left(), result);
        result.push_back(*pos);
        inorder(pos.right(), result);
    }


    static void insert(Node *&node, T const &x) {
        if (!node) {
            node = new Node(x);
            return;
        }
        if (x < node->data)
            insert(node->left, x);
        else if (x > node->data)
            insert(node->right, x);
        // ако x == node->data → нищо (без дубликати)
    }

    static bool contains(Node *node, T const &x) {
        if (!node) return false;
        if (x == node->data) return true;
        if (x < node->data) return contains(node->left, x);
        return contains(node->right, x);
    }

    static Node *copy(Node *node) {
        if (!node) return nullptr;
        return new Node(
            node->data,
            copy(node->left),
            copy(node->right)
        );
    }

    static void clear(Node *node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

#endif // __BST_HPP
