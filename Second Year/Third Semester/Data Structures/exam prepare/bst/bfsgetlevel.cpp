#include <iostream>
#include <vector>
#include <list>
#include <queue>

struct Node{
    int data;
    Node *left, *right;

    Node(int val, Node *l=nullptr, Node *r=nullptr) : data(val), left(l), right(r) {}
};

void getLevelBFS(Node *tree, int target, int curr, std::vector<int> &result){
    if (!tree) return;
    std::queue<Node *> q;
    q.push(tree);

    while (!q.empty()){
        int qsize = q.size();
        for (int i = 0; i < qsize; ++i){
            Node *front = q.front(); q.pop();

            if (curr == target) result.push_back(front->data);

            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
        curr++;
    }
}

std::vector<int> getLevelBFS(Node *tree, int target){
    std::vector<int> result;
    getLevelBFS(tree, target, 0, result);
    return result;
}

void getBFS(Node *tree, std::vector<int> &result){
    if (!tree) return;

    std::queue<Node *> q;
    q.push(tree);

    while(!q.empty()){
        int qsize = q.size();
        for (int i = 0; i < qsize; ++i){
            Node *front = q.front(); q.pop();

            result.push_back(front->data);

            if(front->left) q.push(front->left);
            if(front->right) q.push(front->right);
        }
    }
}

std::vector<int> getBFS(Node *tree){
    std::vector<int> result;
    getBFS(tree, result);
    return result;
}

std::vector<std::vector<int>> getLevels(Node *tree){
    std::vector<std::vector<int>> result;
    std::queue<Node *>q;
    q.push(tree);

    while (!q.empty()){
        int qsize = q.size();
        std::vector<int> curr;
        for (int i = 0; i < qsize; ++i){
            Node *front = q.front(); q.pop();

            curr.push_back(front->data);

            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
        result.push_back(curr);
    }
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

    // std::vector<int> level = getLevelBFS(root, 6);
    // for (int v : level){
    //     std::cout << v << ' ';
    // }
    // std::cout << '\n';

    // std::vector<int> allLvl = getBFS(root);
    // for (int v : allLvl){
    //     std::cout << v << ' ';
    // }
    // std::cout << '\n';

    std::vector<std::vector<int>> levels = getLevels(root);
    for(std::vector<int> vec : levels){
        std::cout << '[';
        for(int v : vec){
            std::cout << v << ' ';
        }
        std::cout << ']';
    }
    std::cout << '\n';

    return 0;
}