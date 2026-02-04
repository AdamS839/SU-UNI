#ifndef __Tree_HPP
#define __Tree_HPP
#include <iostream>
#include <vector>

template<typename T>
class Tree{

public:
Tree(T const &root, std::vector<Tree<T>> children = std::vector<Tree<T>> {}) : m_root(root), m_children(std::move(children)) {}

void addSubtree(Tree const &t){
    m_children.push_back(t);
}

bool leaf() const{
    return m_children.empty();
}

T &root() {return m_root;}
T const &root() const {return m_root;}

std::vector<Tree<T>> const &children() const { return m_children; }

bool search(T const &val) const{
    if (m_root == val) return true;
    for (Tree const &t : m_children){
        if(t.search(val)) return true;
    }
    return false;
}

std::size_t leaves(){
    if (leaf()) 1;
    std::size_t res = 0;
    for (Tree const &child : m_children){
        res += child.leaves();
    }
    return res;
}

std::vector<T> level(std::size_t k){
    std::vector<T> result;
    level(k, result);
    return result;
}

bool isSubtreeOf(Tree const &bigger) const{
    return isSubtreeOf(bigger, *this);
}

private:

static bool isSubtreeOf(Tree const &bigger, Tree const &smaller){
    if (smaller.leaf()) return bigger.root() == smaller.root();

    bool res = false;
    if (bigger.root() == smaller.root()){
        if (isSubtreeOfHelper(bigger, smaller)) return true;
    }
    else {
        for (Tree const &child : bigger.children()){
            res = res || isSubtreeOf(child, smaller);
        }
    }
    return res;
}

static bool isSubtreeOfHelper(Tree const &bigger, Tree const &smaller){
    if (bigger.root() != smaller.root()) return false;
    for (Tree const &smallchild : smaller.children()){
        bool res = false;
        for (Tree const &bigchild : bigger.children()){
            res = res || isSubtreeOfHelper(bigchild, smallchild);
        }
        if (!res) return false;
    } 
    return true;
}

void level(std::size_t k, std::vector<T> &result){
    if (leaf() && k == 0){
        result.push_back(root());
        return;
    }
    if (k == 0){
        result.push_back(root());
        return;
    }
    for (Tree const &child : children()){
        result += child.level(k-1, result);
    }
}

private:
T m_root;
std::vector<Tree<T>> m_children;
};


#endif