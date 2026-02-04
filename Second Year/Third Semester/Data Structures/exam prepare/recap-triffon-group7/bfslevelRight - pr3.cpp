#include <iostream>
#include <vector>
#include <queue>

template<typename T>
struct Node{
    T data;
    Node *left, *right;

    Node(T const &val, Node *l=nullptr, Node *r=nullptr) : data(val), left(l), right(r) {}
};

template<typename T>
void levelCheck(Node<T> *tree, std::queue<T> &q, int curr, int level){
    if (!tree) return;
    if (curr == level){
        if (!q.empty() && tree->data == q.front()) q.pop();
        return;
    }

    levelCheck(tree->right, q, curr + 1, level);
    levelCheck(tree->left, q, curr + 1, level);
}

template<typename T>
bool levelCheck(Node<T> *tree, std::queue<T> q, int level){
    levelCheck(tree, q, 0, level);
    return q.empty();
}

int main() {
    std::cout << std::boolalpha;

    Node<int> *root = 
    new Node<int>(1,
            new Node<int>(2, 
                        new Node<int>(4),
                        new Node<int>(5)),
            new Node<int>(3,
                        new Node<int>(6),
                        new Node<int>(7)));

    std::queue<int> q;
    q.push(7); q.push(6); q.push(5); q.push(4);

    std::cout << levelCheck(root, q, 2) << '\n';

    return 0;
}