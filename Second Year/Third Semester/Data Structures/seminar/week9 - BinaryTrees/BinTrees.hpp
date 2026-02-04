#ifndef __BINARY_TREES_HPP
#define __BINARY_TREES_HPP

template<class T>
class BinaryTree{
public:
    bool empty() const{
        return !m_root;
    }
    operator bool() const {
        return !empty();
    }

    void addLeftSubtree(BinaryTree const &other);
    void addRightSubtree(BinaryTree const &other);

    Position root()       { return Position(m_root); }

    Position root() const { return Position(m_root); }

public:
BinaryTree() : m_root(nullptr) {}

BinaryTree(T const &root, BinaryTree const &left, BinaryTree const &right) : m_root(new Node(root)){
    m_root->left = copy(left.m_root);
    m_root->right = copy(right.m_root);
}

BinaryTree(T const &root, BinaryTree &&left, BinaryTree &&right) : m_root(new Node(root, left.m_root, right.m_root)){
    left.m_root = nullptr;
    right.m_root = nullptr; 
}

BinaryTree(BinaryTree const &other) : m_root(copy(other.m_root)) {}
BinaryTree(BinaryTree &&other) noexcept : m_root(std::exchange(other.m_root, nullptr)) {}

BinaryTree &operator=(BinaryTree const &other){
    if(this != &other){
        free(m_root);
        copy(other.m_root);
    }
    return *this;
}
BinaryTree &operator=(BinaryTree &&other) noexcept{
    if(this != &other){
        free(m_root);
        m_root = std::exchange(other.m_root, nullptr);
    }
    return *this;
}

~BinaryTree() { free m_root; }

class Position{
public:
Position(Node *pos) : pos(pos) {}

bool valid() const{
    return pos;
}

operator bool() const{
    return valid();
}

bool operator!=(Position const &other) const{
    return pos != other.pos;
}

bool operator==(Position const &other) const{
    return pos == other.pos;
}

T &operator*(){
    if(!valid()) throw std::runtime_error("Invalid position");
    return pos->data;
}

T const &operator*() const{
    if(!valid()) throw std::runtime_error("Invalid position");
    return pos->data;
}

Position left() const{
    if(!valid()) throw std::runtime_error("Invalid position");
    return Position(pos->left); 
}

Position right() const{
    if(!valid()) throw std::runtime_error("Invalid position");
    return Position(pos->right); 
}

Position operator-() const{
    return left();
}

Position operator+() const{
    return right();
}

Position operator--(){
    *this = left();
    return *this;
}

Position operator++(){
    *this = right();
    return *this;
}

Position operator--(int){
    Position save = *this;
    --(*this);
    return save;
}

Position operator++(int){
    Position save = *this;
    ++(*this);
    return save;
}

private:
Node *pos;
};

private:
struct Node{
    T data;
    Node *left, *right;
};

private:
Node copy(Node *pos){
    if (!pos) return pos;
    Node *root = new Node(pos->data);
    root->left = copy(pos->left);
    root->right = copy(pos->right);
    return root;
}

void free(Node *pos){
    if (!pos) return;
    free(pos->left);
    free(pos->right);
    delete pos;
    pos = nullptr;
}

private:
Node *m_root;
};

#endif