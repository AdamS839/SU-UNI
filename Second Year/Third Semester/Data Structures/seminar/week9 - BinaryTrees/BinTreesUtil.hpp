#ifndef __BINARY_TREES_UTIL_HPP
#define __BINARY_TREES_UTIL_HPP
#include "BinTrees.hpp"

#include <algorithm>
#include <vector>
#include <queue>

template<typename T, template<typename> class BinaryTreeType>
class BinaryTreesUtil{
public:
    static int height(BinaryTreeType<T> const &tree){
        if (tree.empty()) return -1;
        return height(tree.root());
    }

    static int diameter(BinaryTreeType<T> const &tree){
        return diameter(tree.root());
    }

    static std::vector<T> preorder(BinaryTreeType<T> const &tree){
        std::vector<T> result;
        preorder(tree.root(), result);
        return result;
    }

    static std::vector<T> inorder(BinaryTreeType<T> const &tree){
        std::vector<T> result;
        inorder(tree.root(), result);
        return result;
    }

    static std::vector<std::vector<T>> levels(BinaryTreeType<T> const &tree){
        std::vector<std::vector<T>> result;
        if(tree.empty()) return result;
        
        std::queue<typename BinaryTreeType<T>::Position> q;
        q.push(tree.root());
        while(!q.empty()){
            std::size_t levelsize = q.size();
            
            std::vector<T> level;
            for(std::size_t i = 0; i<levelsize; ++i){
                auto currPos = q.front();
                q.pop();
                level.push_back(*currPos);

                if(currPos.left().valid()) q.push(currPos.left());
                if(currPos.right().valid()) q.push(currPos.right());
            }
            result.push_back(level);
        }
        return result;
    }

    static std::vector<std::vector <T>> paths(BinaryTreeType<T> const &tree){
        if(tree.empty()) return {};
        std::vector<T> path;
        std::vector<std::vector<T>> result;
        paths(tree.root(),path, result);
        return result;
    }

private:
    static void paths(typename BinaryTreeType<T>::Position pos, std::vector<T> &acc, std::vector<std::vector<T>> &res){
        if(!pos.left().valid() && !pos.right().valid()){
            acc.push_back(*pos);
            res.push_back(acc);
            acc.pop_back();
            return;
        }
        acc.push_back(*pos);
        paths(pos.left(), acc, res);
        paths(pos.right(), acc, res);
        acc.pop_back();
    }


    static int height(typename BinaryTree<T>::Position pos){
        if (!pos.valid()) return -1;
        if (!pos.left().valid() && !pos.right().valid()) return 0;
        return 1 + std::max(height(pos.left()), height(pos.right()));
    }

    static int diameter(typename BinaryTreeType<T>::Position pos){
        if(!pos.valid()) return 0;
        // int acc = 0;
        // if (pos.left().valid()) acc++;
        // if (pos.right().valid()) acc++;

        // int diam = acc + std::max(0, height(pos.left())) + std::max(0, height(pos.right()));
        int diam = 2 + height(pos.left()) + height(pos.right());

        int ldiam = diameter(pos.left());
        int rdiam = diameter(pos.right());

        return std::max({diam, ldiam, rdiam});
    }

    static void preorder(BinaryTreeType<T>::Position pos, std::vector<T> &res){
        if (!pos.valid()) return;

        res.push_back(*pos);
        preorder(pos.left(), res);
        preorder(pos.right(), res);
    }

    static void inorder(BinaryTreeType<T>::Position pos, std::vector<T> &res){
        if (!pos.valid()) return;

        inorder(pos.left(), res);
        res.push_back(*pos);
        inorder(pos.right(), res);
    }

};

#endif