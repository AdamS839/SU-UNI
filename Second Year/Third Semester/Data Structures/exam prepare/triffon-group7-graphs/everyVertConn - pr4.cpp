#include <iostream>
#include <vector>
#include <list>

using Graph = std::vector<std::list<int>>;

void dfs(int start, Graph const &g, std::vector<bool> &visited){
    visited[start] = true;

    for(int const &child : g[start]){
        if (!visited[child]){
            dfs(child, g, visited);
        }
    }
}

bool allConnected(Graph const &g){
    std::vector<bool> visited(g.size(), false);
    dfs(0, g, visited);
    for (bool v : visited){
        if (!v) return false;
    }
    return true;
}

int main() {

    Graph graph = {
        {1},
        {2, 3, 5},
        {4},
        {0, 5},
        {6},
        {3, 6},
        {7},
        {1, 8, 9},
        {},
        {7}
    };

    std::cout << std::boolalpha << allConnected(graph) << '\n';

    return 0;
}