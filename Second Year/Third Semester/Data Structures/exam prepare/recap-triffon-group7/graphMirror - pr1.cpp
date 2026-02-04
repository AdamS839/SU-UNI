#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using graph = std::vector<std::list<int>>;

bool maxTwoWayFrom(int const &from, graph const &g, int length, std::vector<int> &path){
    path.push_back(from);
    if (path.size() >= length + 1) return true;

    for (int child : g[from]){
        if (std::find(g[child].begin(), g[child].end(), from) == g[child].end()) continue;

        if (std::find(path.begin(), path.end(), from) == path.end()){
            if (maxTwoWayFrom(child, g, length, path)) return true;
        }
    }
    path.pop_back();
    return false;
}

bool maxTwoWayFrom(int from, graph &g, int length){
    std::vector<int> path;
    return maxTwoWayFrom(from, g, length, path);
}

bool pathN(int v, graph &g, int length, std::vector<bool> &visited, int currL){
    visited[v] = true;
    if (currL >= length) return true;
    for (int child : g[v]){
        if (!visited[child]){
            if (pathN(child, g, length, visited, currL + 1)) return true;
        }
    }
    visited[v] = false;
    return false;
}

bool pathN(int n, graph &g, int length){
    std::vector<bool> visited(g.size(), false);
    return pathN(n, g, length, visited, 0);
}