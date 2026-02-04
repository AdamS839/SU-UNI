#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

struct Node{
    char symbol;
    Node *left, *middle, *right;

    Node(char symbol, Node *l=nullptr, Node *m=nullptr, Node *r=nullptr) : symbol(symbol), left(l), middle(m), right(r) {}
};

void paths(Node *root, std::string &acc, std::set<std::string> &result){
    if (!root) return;

    acc += root->symbol;

    if (!root->left && !root->middle && !root->right){
        result.insert(acc);
    }
    else {
        paths(root->left, acc, result);
        paths(root->middle, acc, result);
        paths(root->right, acc, result);
    }
    acc.pop_back();
}

bool compareReverse(std::string const &a, std::string const &b){
    return a > b;
}

std::vector<std::string> paths(Node *root){
    std::set<std::string> uniqueRes;
    std::string acc;

    paths(root, acc, uniqueRes);

    std::vector<std::string> result(uniqueRes.begin(), uniqueRes.end());
    std::sort(result.begin(), result.end(), compareReverse);

    return result;
}

int main() {

    Node *tree1 = new Node(
    'a',
    new Node('b',
        new Node('c'),
        new Node('d')),
    new Node('c',
        new Node('a', 
            new Node('d')),
        new Node('b'))
    );

    std::vector<std::string> res = paths(tree1);
    for (std::string const &c : res){
        std:: cout << c << " ";
    }
    std::cout << '\n';

    return 0;
}