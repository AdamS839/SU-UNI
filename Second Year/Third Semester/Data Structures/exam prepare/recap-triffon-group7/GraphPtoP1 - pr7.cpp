#include <iostream>
#include <vector>
#include <list>

template<typename T>
using graph = std::vector<std::list<T>>;

template<typename T>
bool dfsPath(T from, T to, std::vector<bool> &visited, std::vector<bool> &allowed, graph<T> const &g){
    if (from == to) return true;
    visited[from] = true;
    for (T const &child : g[from]){
        if (!visited[child] && allowed[child]){
            if (dfsPath(child, to, visited, allowed, g)) return true;
        }
    }
    return false;
}

template<typename T>
bool isBackG(std::vector<T> &path, graph<T> const &g){
    std::vector<bool> visited(g.size(), false), allowed(g.size(), false);

    for (T v : path) allowed[v] = true;
    return dfsPath(path.back(), path.front(), visited, allowed, g);
}

template<typename T>
bool dfsAcyclic(T from, T to, std::vector<bool> &visited, std::vector<T> &path, std::vector<T> &result, graph<T> const &g){
     visited[from] = true;
    path.push_back(from);

    if (from == to){
        if(isBackG(path, g)){
            result = path;
            return true;
        }
    }
   
    for (T const &child : g[from]){
        if (!visited[child]){
            if (dfsAcyclic(child, to, visited, path, result, g)) return true;
        }
    }
    path.pop_back();
    visited[from] = false;
    return false;
}

template<typename T>
std::vector<T> findSpecialPath(graph<T> const &g, T from, T to){
    std::vector<bool> visited(g.size(), false);
    std::vector<T> path, result;
    if (dfsAcyclic(from, to, visited, path, result, g)) return result;
    return {};
}

int main() {

    std::vector<std::list<int>> graph = {
        {1},
        {3, 5},
        {4},
        {0, 5},
        {6},
        {3, 6},
        {7},
        {8, 9},
        {},
        {7}
    };

    std::vector<int> spec = findSpecialPath(graph, 0, 9);
    for (int v : spec){
        std::cout << v << ' ';
    }
    std::cout << '\n';

    return 0;
}