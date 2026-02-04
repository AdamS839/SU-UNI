#include <iostream>
#include <vector>
#include <list>
#include <queue>

struct Node{
    int data;
    Node *left, *right;

    Node(int val, Node *l=nullptr, Node *r=nullptr) : data(val), left(l), right(r) {}
};

void getPathsDfs(Node *tree, std::vector<int> &acc, std::vector<std::vector<int>> &result){
    if (!tree) return;

    acc.push_back(tree->data);

    if(!tree->left && !tree->right){
        result.push_back(acc);
    }
    else {
        getPathsDfs(tree->left, acc, result);
        getPathsDfs(tree->right, acc, result);
    }
    acc.pop_back();
}

std::vector<std::vector<int>> getPathsDfs(Node *tree){
    std::vector<std::vector<int>> result;
    std::vector<int> acc;
    getPathsDfs(tree, acc, result);
    return result;
}

int main() {

    Node *root = new Node(10,
                    new Node(4,
                        new Node(1),
                        new Node(2)),
                    new Node(5,
                        new Node(6),
                        new Node(7)));

    std::vector<std::vector<int>> paths = getPathsDfs(root);
    for (std::vector<int> vec : paths){
        std::cout << "[ ";
        for(int v : vec){
            std::cout << v << ' ';
        }
        std::cout << "] ";
    }
    std::cout << '\n';

    return 0;
}