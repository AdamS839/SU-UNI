#include <iostream>
#include "AVLTree.hpp"

int main(){

    AVLTree<int> at1;
    at1.insert(1);
    at1.insert(2);
    at1.insert(3);
    at1.insert(4);
    at1.insert(5);
    at1.insert(6);
    at1.insert(7);
    at1.insert(8);
    at1.insert(9);
    at1.insert(10);

    at1.remove(6);

    std::vector<int> res = at1.preorder();
    for (int const &v : res){
        std::cout << v << " ";
    }
    std::cout << '\n';

    return 0;
}