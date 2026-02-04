#include <iostream>
#include <vector>
#include <list>
#include <queue>

// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main/G_1_F.cpp

struct Node{
std::string word;
Node *left, *right;

Node(std::string const &val, Node *l=nullptr, Node *r=nullptr) : word(val), left(l), right(r) {}
};

Node *buildTree(int i, std::size_t n, std::string s[], int l[], int r[]){
    if (i == -1) return nullptr;
    if (i >= n) return nullptr;

    Node *left = buildTree(l[i], n, s, l, r);
    Node *right = buildTree(r[i], n, s, l, r);

    return new Node(s[i], left, right);
}

Node *buildTree(std::size_t n, std::string s[], int l[], int r[]){
    return buildTree(0, n, s, l, r);
}

bool isWhitespace(char const &c){
    return c == ' ' || c == '\n' || c == '\t';
}

std::vector<std::string> words(std::string const &str){
    std::vector<std::string> result;
    std::string acc;

    for (char c : str){
        if (isWhitespace(c)){
            if (!acc.empty()){
                result.push_back(acc);
                acc.clear();
            }
        }
        else{
            acc += c;
        }
    }
    if (!acc.empty()){
        result.push_back(acc);
    }
    return result;
}

bool horizontalSentence(Node const *tree, std::string const &s){
    std::vector<std::string> ws = words(s);

    if (!tree) return ws.empty();

    std::queue<Node const*> q;
    q.push(tree);

    while (!q.empty()){
        std::size_t qsize = q.size();
        bool hasSentence = ws.size() == qsize;
        for (std::size_t i = 0; i < qsize; ++i){
            Node const *front = q.front(); q.pop();

            hasSentence = hasSentence && front->word == ws[i];

            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
        if (hasSentence) return true;
    }
    return false;
}

int main() {

    std::string s[] = {"mistletoe","snow","bells","is","it","Christmas",
                   	     "yet","holly","pine","cheer","gift","Santa"};
    int l[] = {1,3,5,7,9,10,-1,-1,-1,-1,-1,-1}, r[] = {2,4,6,8,-1,11,-1,-1,-1,-1,-1,-1};

    std::size_t n = sizeof(l) / sizeof(int); // n = 12

    Node *tree = buildTree(12, s, l, r);

    std::cout << std::boolalpha;
    std::cout << horizontalSentence(tree, "is it Christmas yet") << '\n';
    std::cout << horizontalSentence(tree, "holy pine gift Santa") << '\n';
    std::cout << horizontalSentence(tree, "holy pine cheer") << '\n';

    return 0;
}