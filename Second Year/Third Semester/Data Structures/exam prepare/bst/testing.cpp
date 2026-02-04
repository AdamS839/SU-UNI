#include <iostream>
#include <vector>
#include <queue>

struct Node{
    int data;
    Node *left, *right;

    Node(int val, Node *l=nullptr, Node *r=nullptr) : data(val), left(l), right(r) {}
};


std::vector<std::vector<int>> bfs(Node *root){
    std::vector<std::vector<int>> result;

    if(!root) return {};

    std::queue<Node *> q;
    q.push(root);

    while(!q.empty()){
        int level = q.size();
        std::vector<int> currLevel;

        for(int i = 0; i < level; ++i){
            Node *curr = q.front();
            q.pop();

            currLevel.push_back(curr->data);

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        result.push_back(currLevel);
    }

    return result;
}