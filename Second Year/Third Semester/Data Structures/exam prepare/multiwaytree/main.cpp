#include <iostream>
#include "Tree.hpp"

template<typename T>
std::pair<int,int> maxSumHelper(Tree<T> const &node) {
    int include_root = node.root();
    int exclude_root = 0;

    for (Tree<T> const &child : node.children()) {
        std::pair<int,int> childRes = maxSumHelper(child);
        include_root += childRes.second;
        exclude_root += std::max(childRes.first, childRes.second);
    }

    return {include_root, exclude_root};
}

template<typename T>
int maxSumOfNonAdjacent(Tree<T> const &tree) {
    std::pair<int,int> res = maxSumHelper(tree);
    return std::max(res.first, res.second);
}

int main() {

    Tree<int> tree1 = Tree<int>{
        1,
        {
        Tree<int>{2,
                    { Tree<int>{5} }},
        Tree<int>{3},
        Tree<int>{4,
                    { Tree<int>{6} }}
        }
    };


    Tree<int> tree2 = 
        Tree<int>{10,
        {
            Tree<int>{5,
                    { Tree<int>{1,
                                    { Tree<int>{0} }},
                        Tree<int>{3} }},
            Tree<int>{7,
                    { Tree<int>{6},
                        Tree<int>{8,
                                    { Tree<int>{-2,
                                                { Tree<int>{9} }}}}}},
            Tree<int>{20,
                        { Tree<int>{15},
                        Tree<int>{30} }}
        }
    };

    // std::cout << std::boolalpha;
    // std::cout << tree1.contains(1) << '\n';
    // std::cout << tree1.contains(4) << '\n';
    // std::cout << tree1.contains(5) << '\n';
    // std::cout << tree1.contains(7) << '\n';

    // std::cout << tree1.leaves() << '\n';

    // for (int el : tree1.level(0)) {
    //     std::cout << el << ' ';
    // }
    // std::cout << '\n';

    // for (int el : tree1.level(1)) {
    //     std::cout << el << ' ';
    // }
    // std::cout << '\n';

    // for (int el : tree1.level(2)) {
    //     std::cout << el << ' ';
    // }
    // std::cout << '\n';

    // std::cout << tree2.isSubtreeOf(tree1) << '\n';

    // std::cout << "Tree1 max sum: " << maxSumOfNonAdjacent(tree1) << "\n"; // 14
    // std::cout << "Tree2 max sum: " << maxSumOfNonAdjacent(tree2) << "\n"; // 82

  return 0;
}