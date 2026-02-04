#include <iostream>
#include "BinTree.hpp"
#include <queue>
#include <vector>
#include <cstddef>
#include <algorithm>

template<typename T>
long long height(typename BinaryTree<T>::position pos){
    if (!pos.valid()) return -1;
    if (!pos.left().valid() && !pos.right().valid()) return 0;

    long long lh = height<T>(pos.left());
    long long rh = height<T>(pos.right());
    return 1 + std::max(lh, rh);
}

template<typename T>
long long diameter(typename BinaryTree<T>::position pos){
    if (!pos.valid()) return -1;

    long long diam = height<T>(pos.left()) + height<T>(pos.right());
    return 2 + std::max({diam, diameter<T>(pos.left()), diameter<T>(pos.right())});
}

template<typename T>
void inorder(typename BinaryTree<T>::position pos){
    std::vector<T> result;
    inorder(pos, result);

    for(T const &t : result){
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void inorder(typename BinaryTree<T>::position pos, std::vector<T> &result){
    if (!pos.valid()) return;

    inorder<T>(pos.left(), result);
    result.push_back(*pos);
    inorder<T>(pos.right(), result);
}

template<typename T>
void preorder(typename BinaryTree<T>::position pos){
    std::vector<T> result;
    preorder(pos, result);

    for(T const &t : result){
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void preorder(typename BinaryTree<T>::position pos, std::vector<T> &result){
    if (!pos.valid()) return;

    result.push_back(*pos);
    preorder<T>(pos.left(), result);
    preorder<T>(pos.right(), result);
}

template<typename T>
std::vector<std::vector<T>> levels(typename BinaryTree<T>::position tree){
    std::vector<std::vector<T>> result;

    if (!tree.valid()) return result;

    std::queue<typename BinaryTree<T>::position> q;
    q.push(tree);
    
    while(!q.empty()){
        std::size_t levelSize = q.size();

        std::vector<T> level;
        for (std::size_t i = 0; i < levelSize; ++i){
            auto currPos = q.front();
            q.pop();
            if (!currPos.valid()) continue;

            level.push_back(*currPos);

            q.push(currPos.left());
            q.push(currPos.right());
        }
        result.push_back(level);
    }
    return result;
}

template<typename T>
void printVecvec(std::vector<std::vector<T>> res){
    for (std::vector<T> vec : res){
        std::cout << '[';
        for (T const &t : vec){
            std::cout << t << " ";
        }
        std::cout << ']';
    }
    std::cout << std::endl;
}

template<typename T>
std::vector<std::vector<T>> paths(typename BinaryTree<T>::position pos){
    std::vector<std::vector<T>> result;
    std::vector<T> acc;
    paths(pos, acc, result);
    return result;
}

template<typename T>
void paths(typename BinaryTree<T>::position pos, std::vector<T> &acc, std::vector<std::vector<T>> &result){
    if (!pos.valid()) return;

    acc.push_back(*pos);
    if (!pos.left().valid() && !pos.right().valid()){
        result.push_back(acc);
    }
    else{
        paths(pos.left(), acc, result);
        paths(pos.right(), acc, result);
    }
    acc.pop_back();
}


template<typename T>
bool mark(typename BinaryTree<T>::position pos, std::vector<bool> &seen) {
    if (!pos.valid()) return true;

    int val = *pos;
    if (0 <= val && val <= (int)seen.size()) {
        if (seen[val]) return false; // дубликат!
        seen[val] = true;
    }

    return mark<T>(pos.left(), seen) && mark<T>(pos.right(), seen);
}


template<typename T>
bool contains0toN(typename BinaryTree<T>::position pos, unsigned n){
    std::vector<bool> seen(n+2, false);
    if (!mark<T>(pos, seen)) return false;
    for(bool b : seen){
        if (!b) return false;
    }
    return true;
}

int main() {

    BinaryTree<int> tree1 = BinaryTree<int>{
    10,
    BinaryTree<int>{5,
                     BinaryTree<int>{1},
                     BinaryTree<int>{7}},
    BinaryTree<int>{20,
                     BinaryTree<int>{15},
                     BinaryTree<int>{30}}
    };

    BinaryTree<int> tree2 = BinaryTree<int>{
    1,
    BinaryTree<int>{2,
                     BinaryTree<int>{5},
                     BinaryTree<int>{7}},
    BinaryTree<int>{0,
                     BinaryTree<int>{3},
                     BinaryTree<int>{4}}
    };

    // std::cout << diameter<int>(tree1.root()) << std::endl;

    // preorder<int>(tree1.root());

    // std::vector<std::vector<int>> res = levels<int>(tree1.root());
    // printVecvec(res);

    // std::vector<std::vector<int>> res = paths<int>(tree1.root());
    // printVecvec(res);

    std::cout << std::boolalpha << contains0toN<int>(tree2.root(), 4) << std::endl;

    return 0;
}