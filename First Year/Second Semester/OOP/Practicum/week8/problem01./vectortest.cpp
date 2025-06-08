#include "Vector.hpp"
#include "Set.hpp"

int main() {

    Vector<int> v1(10, 5);
    
    Vector<int> v2 = v1;

    Vector<int> v3(6, 1);

    Vector<int>::iterator it = v1.begin();

    Vector<int> v4{1,2,3,4,5,6,7,8,91,0};

    // for (int el : v4){
    //     std::cout << el << " ";
    // }
    // std::cout << std::endl;

    // for (Vector<int>::iterator it = v4.begin(); it != v4.end(); ++it){
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    // for (Vector<int>::reverseiterator it = v4.rbegin(); it != v4.rend(); ++it){
    //     std::cout << *it << " ";
    // }

    // Set from here

    Set<int> s1{1,2,3,4,5,6,7,8,9};
    Set<int> s2{43,23,23,54,54,32,1,1,6,7};

    // for (int el : s1){
    //     std::cout << el << " ";
    // }
    // std::cout << std::endl;

    for (Set<int>::iterator it = s1.begin(); it != s1.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}