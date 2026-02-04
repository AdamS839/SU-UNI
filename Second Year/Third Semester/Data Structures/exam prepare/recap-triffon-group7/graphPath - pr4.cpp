#include <iostream>
#include <vector>
#include <list>

template<typename T>
bool graphPathWithKlength(T from, T to, int k, std::vector<std::list<T>> const &g, std::vector<bool> &visited, std::vector<T> &path, std::vector<T> &result){
    path.push_back(from);
    if (k == 0){
        if (from == to){
            result = path;
            path.pop_back();
            return true;
        }
    }
    visited[from] = true;

    for (T const &child : g[from]){
        if (!visited[child]){
            if (graphPathWithKlength(child, to, k - 1, g, visited, path, result)) return true;
        }
    }

    visited[from] = false;
    path.pop_back();
    return false;
}

template<typename T>
std::vector<T> graphPathWithKlength(T from, T to, int length, std::vector<std::list<T>> &g){
    std::vector<bool> visited(g.size(), false);
    std::vector<T> path, result;
    if (graphPathWithKlength(from, to, length, g, visited, path, result)) return result;
    return {};
}

int main() {

    std::vector<std::list<int>> graph ={
        {1},
        {2, 3},
        {},
        {4},
        {5, 6},
        {},
        {7},
        {}
    };

    std::vector<int> path = graphPathWithKlength(0, 7, 5, graph);

    for (int const &vertex : path){
        std::cout << vertex << " ";
    }
    std::cout << '\n';

    return 0;
}