#ifndef __AVLTree_HPP
#define __AVLTree_HPP
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <vector>


template<typename T>
class AVLTree{
    class Position;
public:
    using position = Position;

    bool empty() const{
        return m_root == nullptr;
    }

    operator bool() const { return !empty(); }

    position root() { return position(m_root); }
    position root() const { return position(m_root); }

    void insert(T const &val){
        m_root = insertRec(m_root, val);
    }

    void remove(T const &val){
        m_root = removeRec(m_root, val);
    }

    std::optional<T> lookup(T const &val){
        position pos = root();

        while (pos.valid() && pos.value() != val){
            if (pos.value() < val){
                pos = pos.right();
            }
            else pos = pos.left();
        }
        return pos.valid() ? std::optional<T>(*pos) : std::nullopt;
    }

    std::vector<T> preorder() const{
        std::vector<T> result;
        preorder(root(), result);
        return result;
    }

public:

AVLTree() : m_root(nullptr) {}
AVLTree(AVLTree const &other) : m_root(copy(other.m_root)) {}
AVLTree(AVLTree &&other) : m_root(std::exchange(other.m_root, nullptr)) {}

AVLTree &operator==(AVLTree const &other){
    if (this != &other){
        free(m_root);
        m_root = copy(other.m_root);
    }
    return *this;
}
AVLTree &operator==(AVLTree &&other){
    if (this != &other){
        free(m_root);
        m_root = std::exchange(other.m_root, nullptr);
    }
    return *this;
}

~AVLTree() { free(m_root); }

private:
    struct Node{
        T data;
        Node *left, *right;
        int height;

        Node(T const &val=T(), Node *l=nullptr, Node *r=nullptr, int h=1) : data(val), left(l), right(r), height(h) {}
    };

    class Position{
    public:
        Position(Node *nodePos) : nodePos(nodePos) {}
        
        bool valid() const{
            return nodePos;
        }

        operator bool() const { return valid(); }

        bool operator==(Position const &other) const{
            return other.nodePos == this->nodePos;
        }

        bool operator!=(Position const &other) const{
            return nodePos != other.nodePos;
        }

        Position left() const{
            if (!valid()) throw std::runtime_error("invalid pos");
            return Position(nodePos->left);
        }

        Position right() const{
            if (!valid()) throw std::runtime_error("invalid pos");
            return Position(nodePos->right);
        }

        T &value() {return nodePos->data; }
        T const &value() const { return nodePos->data; }

        T &operator*() {return value(); }
        T const &operator*() const { return value(); }

    private:
        Node *nodePos;
    };
private:

    static void preorder(Position pos, std::vector<T> &res){
        if (!pos.valid()) return;

        res.push_back(*pos);
        preorder(pos.left(), res);
        preorder(pos.right(), res);
    }

    static int getHeight(Node *curr){
        if (!curr) return 0;

        return curr->height;
    }

    static void updateHeight(Node *curr){
        if (!curr) return;

        curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));
    }

    static Node *copy(Node *curr){
        if (!curr) return curr;
        return new Node(curr->data, copy(curr->left), copy(curr->right), curr->height);
    }

    static void free(Node *curr){
        if (!curr) return;

        free(curr->left);
        free(curr->right);
        delete curr;
    }

    static void rotateLeft(Node *&curr){
        Node *temp = curr->right;
        curr->right = temp->left;
        temp->left = curr;

        updateHeight(curr);
        updateHeight(temp);

        curr = temp;
    }

    static void rotateRight(Node *&curr){
        Node *temp = curr->left;
        curr->left = temp->right;
        temp->right = curr;

        updateHeight(curr);
        updateHeight(temp);

        curr = temp;
    }

    static int balanceFactor(Node *curr){
        if (!curr) return 0;

        return getHeight(curr->left) - getHeight(curr->right);
    }

    static void balance(Node *&curr){
        
        int bf = balanceFactor(curr);

        if (bf == 2){
            if (balanceFactor(curr->left) >= 0){
                rotateRight(curr);
            }
            else{
                rotateLeft(curr->left);
                rotateRight(curr);
            }
        }
        else if(bf == -2){
            if (balanceFactor(curr->right) <= 0){
                rotateLeft(curr);
            }
            else{
                rotateRight(curr->right);
                rotateLeft(curr);
            }
        }
    }

    static Node *insertRec(Node *curr, T const &val){
        if (!curr) return new Node(val);

        if (curr->data > val){
            curr->left = insertRec(curr->left, val);
        }
        else{
            curr->right = insertRec(curr->right, val);
        }

        updateHeight(curr);
        balance(curr);

        return curr;
    }

    static Node *removeRec(Node *curr, T const &val){
        if (!curr) return curr;

        if (curr->data < val){
            curr->right = removeRec(curr->right, val);
        }
        else if (curr->data > val){
            curr->left = removeRec(curr->left, val);
        }
        else{
            if (!curr->right){
                Node *save = curr->left;
                delete curr;
                curr = save;
            }
            else{
                Node *in = inorderSuccessor(curr->right);

                curr->data = in->data;

                curr->right = removeRec(curr->right, in->data);
            }
        }

        if (!curr) return curr;
    
        updateHeight(curr);
        balance(curr);

        return curr;
    }

    static Node *inorderSuccessor(Node *curr){
        if (!curr) return curr;
        if (!curr->left) return curr;

        return inorderSuccessor(curr->left);
    }

private:
Node *m_root;
};

#endif