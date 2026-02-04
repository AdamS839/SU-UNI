#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "BinSearchTree.hpp"
#include "BinTrees.hpp"

std::optional<int> kthLargest(unsigned &k, BST<int, bool>::Position pos){
    if (!pos.valid() || k == 0) return std::nullopt;
    std::optional<int> lres = kthLargest(k, pos.left());
    if (lres.has_value()) return lres;
    k--;
    if (k == 0) return std::optional<int>((*pos).first);
    return kthLargest(k, pos.right());
}
std::optional<int> kthLargest(unsigned k, BST<int, bool> const &bst){
     return kthLargest(k, bst.root());
}

template<typename T, typename U>
U foldr(std::function<U(T,U)> const &op, U nv, typename BinaryTree<T>::Position pos){
    if (!pos.valid()) return nv;
    U rres = (pos, *pos, foldr(op, nv, pos.right()));
    return foldr(op, rres, pos.left());
}

template<typename T, typename U>
U foldr(std::function<U(T,U)> const &op, U nv, BinaryTree<T> const &tree){

}

int kthLargestSum(unsigned &k, BST<int, bool>::Position pos){
    if (!pos.valid() || k == 0) return 0;
    int lres = kthLargestSum(k, pos.left());
    lres += (*pos).first;
    k--;
    if (k == 0) return lres;
    return lres + kthLargestSum(k, pos.right());
}
int kthLargestSum(unsigned k, BST<int, bool> const &bst){
     return kthLargestSum(k, bst.root());
}