#include <iostream>
#include <vector>
#include <list>

using Graph = std::vector<std::list<int>>;

void dfs(int vertex, Graph const &g, std::vector<bool> &visited){
    visited[vertex] = true;

    for(int const &child : g[vertex]){
        if (!visited[child]) dfs(child, g, visited);
    }
}

int connectedComponents(Graph &g){
    int counter = 0;
    std::vector<bool> visited(g.size(), false);
    for (int i = 0; i < g.size(); ++i){
        if (!visited[i]){
            dfs(i, g, visited);
            counter++;
        }
    }
    return counter;
}

int main() {

    Graph graph = {
        {1},
        {3, 5},
        {4},
        {0, 5},
        {6},
        {3, 6},
        {7},
        {1, 8, 9},
        {},
        {7}
    };

    std::cout << connectedComponents(graph) << '\n';


    return 0;
}