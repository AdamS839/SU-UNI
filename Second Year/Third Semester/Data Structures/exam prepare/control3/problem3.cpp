#include <iostream>
#include <vector>
#include <queue>

template<typename T>
struct BinTreeNode{
    T data;
    BinTreeNode *left, *right;

    BinTreeNode(T const &val=T(), BinTreeNode *l=nullptr, BinTreeNode *r=nullptr) : data(val), left(l), right(r) {}

};

// right
template<typename T>
int getLevels(BinTreeNode<T> *root){
    if (!root) return -1;
    if (root && !root->left && !root->right) return 0;
    return 1 + std::max(getLevels(root->left), getLevels(root->right));
}

template<typename T>
void levelshelper(BinTreeNode<T> *root, int currLvl, std::vector<T> &result){ // void
    if (!root) return;
    if (currLvl == 0){
        result.push_back(root->data);
        return;
    }
    levelshelper(root->left, currLvl - 1, result);
    levelshelper(root->right, currLvl - 1, result);
}

template<typename T> // right
T sumLevel(BinTreeNode<T> *root, int level){
    if (!root) std::runtime_error("No tree to get value from");
    std::vector<T> vals;
    T result = 0;
    levelshelper(root, level, vals);
    for (T const &v : vals){
        result += v;
    }
    return result;
}

template<typename T>
bool sameInside(std::vector<T> &v, T data){ // &v instead of just v
    for (T const &i : v){
        if (i == data) return true;
    }
    return false;
}

template<typename T>
bool sameValLevel(BinTreeNode<T> *root, std::vector<int> &levelsOutput){
    if (!root) return false;
    bool foundSame = false;
    int allLevels = getLevels(root);
    std::vector<T> sums;

    for (int i = 0; i <= allLevels; ++i) sums.push_back(sumLevel(root, i)); // wrong bubble sort
    for (int i = 0; i < sums.size(); ++i){
        for (int j = i + 1; j < sums.size(); ++j){
            if (sums[i] == sums[j]){                            // both ifs should be inside when sum[i] == sum[j]
                foundSame = true;       
                if (!sameInside(levelsOutput, i)) levelsOutput.push_back(i);
                if (!sameInside(levelsOutput, j)) levelsOutput.push_back(j);
            }
        }
    }
    return foundSame;
}

template<typename T>
bool sameVal(BinTreeNode<T> *root){
    std::vector<int> levels;
    bool done = sameValLevel(root, levels);
    if (done && !levels.empty()){
        for (int in : levels){
            std::cout << in << " ";
        }
        std::cout << std::endl;
    }
    return done;
}

//--------------------------------------------------

bool member(int x, std::vector<int> &vals){
    for (int const &g : vals){
        if (g == x) return true;
    }
    return false;
}

std::vector<int> getLevelSums(BinTreeNode<int>* root) {
    std::vector<int> levelSums;
    
    if (!root) return levelSums;
    
    std::queue<BinTreeNode<int>*> q;
    q.push(root);
    int level = 0;
    
    while (!q.empty()) {
        int size = q.size();
        int sum = 0;
        
        for (int i = 0; i < size; i++) {
            BinTreeNode<int>* node = q.front();
            q.pop();
            sum += node->data;
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        levelSums.push_back(sum);
        level++;
    }
    
    return levelSums;
}

bool sameSums(BinTreeNode<int> *root, std::vector<int> &levelindices){
    bool found = false;
    std::vector<int> levelSums = getLevelSums(root);

    for (int i = 0; i < levelSums.size(); i++) {
        for (int j = i + 1; j < levelSums.size(); j++) {
            if (levelSums[i] == levelSums[j]) {
                found = true;
                if(!member(i, levelindices)) levelindices.push_back(i);
                if(!member(j, levelindices)) levelindices.push_back(j);
            }
        }
    }
    return found;
}

void checkSame(BinTreeNode<int> *root){
    std::vector<int> res;
    bool found = sameSums(root, res);

    if (found){
        std::cout << std::boolalpha << found << " : ";
        for (int const &i : res){
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
    else std::cout << std::boolalpha << false << std::endl;
}

int main() {

    BinTreeNode<int>* root = new BinTreeNode<int>(
        4,
        new BinTreeNode<int>(
            3,
            new BinTreeNode<int>(1),
            new BinTreeNode<int>(2)
        ),
        new BinTreeNode<int>(
            7, 
            new BinTreeNode<int>(3),
            new BinTreeNode<int>(4)
        )
    );

    checkSame(root);
    // std::cout << std::boolalpha << sameVal<int>(root) << std::endl;

    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}