#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template<typename T>
using graph = std::vector<std::list<T>>;

template<typename T>
bool hasCycle(T const &vert, graph<T> const &g, std::vector<bool> &visited, std::vector<bool> &stack, std::vector<T> &path, std::vector<T> &cycle){
    if (visited[vert]) return false;
    
    visited[vert] = true;
    stack[vert] = true;

    path.push_back(vert);

    for (T const &child : g[vert]){
        if (!visited[child]){
            if(hasCycle(child, g, visited, stack, path, cycle)) return true;
        }
        else if (stack[child]){
            auto it = std::find(path.begin(), path.end(), child);
            cycle.assign(it, path.end());
            cycle.push_back(child);
            return true;
        }
    }
    stack[vert] = false;
    path.pop_back();
    return false;
}

template<typename T>
std::vector<T> hasCycle(graph<T> const &g){
    std::vector<bool> visited(g.size(), false), stack(g.size(), false);
    std::vector<T> path, pathCycle;
    for (int i = 0; i < g.size(); ++i){
        if (hasCycle(i, g, visited, stack, path, pathCycle)) return pathCycle;
    }
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
        {3}
    };

    std::vector<int> path = hasCycle(graph);
    for (int const &v : path){
        std::cout << v << ' ';
    }
    std::cout << '\n';

    return 0;
}