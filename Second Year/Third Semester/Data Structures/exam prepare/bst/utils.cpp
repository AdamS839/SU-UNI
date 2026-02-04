#include <iostream>
#include <vector>
#include <optional>
#include "bst.hpp"

    // sdp problem 3 BST
    template<typename T>
    T findNext(BST<T> const &t, T const &x){
        if (!t.root().valid()) return -1;
        std::vector<T> inordervec = t.inorder();
        bool found = false;
        for (T const &val : inordervec){
            if (found) return val;
            if (val == x) found = true;
        }
        return -1;
    }

    template<typename T>
    std::optional<T> findNext1(typename BST<T>::Position pos, T const &x, bool &found){
        if (!pos.valid()) return std::nullopt;

        auto lres = findNext1(pos.left(), x, found);
        if (lres) return lres;

        if (found) return *pos;
        
        if (*pos == x) found = true;

        return findNext1(pos.right(), x, found);
    }

    template<typename T>
    std::optional<T> findNext1(BST<T> const &t, T const &x){
        bool found = false;
        return findNext1(t.root(), x, found);
    }

    // sdp problem 4 BST
    template<typename T>
    BST<T> crateFromVector(std::vector<T> &begin){
        BST<T> create;
        for (T const &value : begin){
            create.insert(value);
        }
        return create;
    }

    // sdp problem 5 BST
    template<typename T>
    bool madeFromTwo(BST<T> const &t, T k){
        std::vector<T> vec = t.inorder();

        long long i=0;
        long long j=vec.size()-1;
        while(i<j){
            if (vec[i]+vec[j] == k) return true;
            else if (vec[i] + vec[j] < k){
                i++;
            }
            else j--;
        }
        return false;
    }

    // sdp problem 5 BST
    template<typename T>
    bool isBST(BST<T> const &t){
        if (t.empty()) return true;
        std::vector<T> ordered = t.inorder();
        for (std::size_t i = 1; i < ordered.size(); ++i){
            if (ordered[i] <= ordered[i-1]) return false;
        }
        return true;
    }
 
    // O(1) space complexity. Still O(n) total 
    template<typename T>
    bool isBSThelper(typename BST<T>::Position pos, T *&last){
        if (!pos.valid()) return true;

        if (!isBSThelper(pos.left(), last)) return false;

        if (last && *last >= *pos) return false;  // current node must be bigger than last
        last = &(*pos);  // update last visited

        return isBSThelper(pos.right(), last);
    }

    template<typename T>
    bool isBST1(BST<T> const &t){
        T *last = nullptr;
        return isBSThelper(t.root(), last);
    }

    template<typename T>
    bool isBST2help(typename BST<T>::Position pos){
        if (!pos.valid()) return true;

        bool bst = true;
        if (pos.left()){
            bst = bst && *pos > *pos.left() && isBST2help<T>(pos.left());
        }

        if (pos.right()){
            bst = bst && *pos < *pos.right() && isBST2help<T>(pos.right());
        }

        return bst;
    }
    
    template<typename T>
    bool isBST2(BST<T> const &t){
        return isBST2help<T>(t.root());
    }
    //---------------------------

    // sdp problem 7 BST
    template<typename T>
    std::optional<T> KthLargest(unsigned &k, typename BST<T>::Position pos){
        if (!pos.valid() || k == 0) return std::nullopt;
        
        std::optional<T> rres = KthLargest<T>(k, pos.right());
        if (rres.has_value()) return rres;

        k--;
        if (k == 0){
            return *pos;
        }

        return KthLargest<T>(k, pos.left());
    }

    template<typename T>
    std::optional<T> KthLargest(unsigned k, BST<T> const &t){
        return KthLargest<T>(k, t.root());
    }

    template<typename T>
    T sumKthLargest(T x, typename BST<T>::Position pos){
        if (!pos.valid()) return 0;

        T val = *pos;

        if (val > x){
            return sumKthLargest<T>(x, pos.left());
        }
        else return val + sumKthLargest<T>(x, pos.left()) + sumKthLargest<T>(x, pos.right());
    }

    template <typename T>
    T sumKthLargest(unsigned k, BST<T> const &t){
        auto kth = KthLargest(k, t);
        if (!kth) throw std::runtime_error("No k-th largest");
        return sumKthLargest(*kth, t.root());
    }

    // sdp problem 8 BST
    template<typename T>
    BST<T> transformedTree(typename BST<T>::Position pos, T &acc){
        if(!pos.valid()) return BST<T>();
        BST<T> rightTree = transformedTree(pos.right(), acc);
        acc += (*pos);

        BST<T> newTree;
        newTree.insert(acc);
        BST<T> leftTree = transformedTree(pos.left(), acc);
        for(auto p : leftTree.inorder()) newTree.insert(p);
        for(auto p : rightTree.inorder()) newTree.insert(p);

        return newTree;
    }

    template<typename T>
    BST<T> transformTree(BST<T> const &bst) {
        T acc = 0;
        return transformedTree(bst.root(), acc);
    }

    // sdp problem 9 BST
    template<typename T>
    std::vector<T> merged(std::vector<T> &vec1, std::vector<T> &vec2){
        std::vector<T> result(vec1.size() + vec2.size());
        std::size_t i = 0, j = 0, resIn = 0;

        while (i < vec1.size() && j < vec2.size()){
            if (vec1[i] <= vec2[j]){
                result[resIn] = vec1[i++];
            }
            else result[resIn] = vec2[j++];
            resIn++;
        }
        while(i < vec1.size()){
            result[resIn++] = vec1[i++];
        }
        while(j < vec2.size()){
            result[resIn++] = vec2[j++];
        }
        return result;
    }

    template<typename T>
    BST<T> merge(BST<T> const &t1, BST<T> const &t2){
        std::vector<T> vec1 = t1.preorder();
        std::vector<T> vec2 = t2.preorder();
        std::vector<T> result = merged<T>(vec1, vec2);
        BST<T> bst = crateFromVector<T>(result);
        return bst;
    }

int main() {
    BST<int> t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);
    t.insert(12);
    t.insert(18);

    // std::vector<int> vals = t.inorder();
    // for(int const &v : vals){
    //     std::cout << v << " ";
    // }
    // std::cout << "\n";

    // std::cout << findNext<int>(t, 15) << std::endl;
    std::optional<int> res = findNext1(t, 15);
    if (res) std::cout << *res << '\n';

    std::vector<int> vec1{6,3,1,4,8,7,10,9};
    std::vector<int> vec2{5,3,2,1,4,8,6,7,10,9};
    BST<int> t2 = crateFromVector(vec2);
    // std::vector<int> vals2 = t2.inorder();
    // for (int const &v : vals2){
    //     std::cout << v << " ";
    // }
    // std::cout << std::endl;

    // std::cout << isBST(t2) << std::endl;
    // std::cout << isBST1(t2) << std::endl;
    // std::cout << isBST2(t2) << std::endl;

    // std::cout << madeFromTwo<int>(t2, 7) << std::endl;

    // std::cout << sumKthLargest<int>(3, t2) << '\n';
    // auto res = KthLargest(3, t2);
    // if (res) std::cout << *res << '\n';

    BST<int> t3 = transformTree<int>(t2);
    // std::vector<int> vals3 = t3.preorder();
    // for (int const &v : vals3){
    //     std::cout << v << " ";
    // }
    // std::cout << std::endl;

    BST<int> t4 = merge<int>(t2, t3);
    std::vector<int> vals4 = t4.inorder();
    // for(int const &v : vals4){
    //     std::cout << v << " ";
    // }
    // std::cout << '\n';

    

    return 0;
}