#include <iostream>
#include <vector>
#include <list>

// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main/G_4_F.cpp

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

bool verticalSentence(Node *tree, std::vector<std::string> const &ws, std::vector<std::string> &sentence){
    if (!tree){
        return ws == sentence;
    }
    sentence.push_back(tree->word);

    bool found = verticalSentence(tree->left, ws, sentence) || verticalSentence(tree->right, ws, sentence);
    sentence.pop_back();
    
    return found;
}

bool verticalSentence(Node *tree, std::string const &sentence){
    std::vector<std::string> ws = words(sentence);
    std::vector<std::string> matchSentence;

    bool hasSentence = false;
    hasSentence = hasSentence || verticalSentence(tree, ws, matchSentence);
    return hasSentence;
}

int main() {

    std::string s[] = {"is","it","bells","Christmas","pine", "star","holly","yet","cheer","gift"};
    int l[] = {1, 3,4,6,-1,8,-1,-1,-1,-1}; 
    int r[] = {2,-1,5,7,-1,9,-1,-1,-1,-1};   

    std::size_t n = sizeof(l) / sizeof(int); // n = 12

    Node *tree = buildTree(n, s, l, r);

    std::cout << std::boolalpha;
    std::cout << verticalSentence(tree, "is it Christmas yet") << '\n';
    std::cout << verticalSentence(tree, "holy pine gift Santa") << '\n';
    std::cout << verticalSentence(tree , "holy pine cheer") << '\n';

    return 0;
}