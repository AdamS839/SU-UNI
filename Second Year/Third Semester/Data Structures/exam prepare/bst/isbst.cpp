#include <iostream>
#include <vector>

struct Node{
    int data;
    Node *left, *right;

    Node(int data, Node *l=nullptr, Node *r=nullptr) : data(data), left(l), right(r) {}
};


bool inorderCheck(Node *node, Node *&prev) {
    if (!node) return true;

    if (!inorderCheck(node->left, prev))
        return false;

    if (prev && node->data <= prev->data)
        return false;

    prev = node;

    return inorderCheck(node->right, prev);
}

bool isBST(Node *root) {
    Node *prev = nullptr;
    return inorderCheck(root, prev);
}

int main() {

    Node *root = new Node(10,
                    new Node(8,
                        new Node(4),
                        new Node(9)),
                    new Node(13,
                        new Node(11),
                        new Node(16)));

    std::cout << std::boolalpha << isBST(root) << '\n';

    return 0;
}