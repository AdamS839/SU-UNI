#include <iostream>
#include <vector>
#include <list>

using Graph = std::vector<std::list<int>>;

bool hasCycle(int vertex, std::vector<bool> &visited, std::vector<bool> &stack, Graph const &g){
    if (visited[vertex]) return false;

    visited[vertex] = true;
    stack[vertex] = true;

    bool cyclic = false;
    for (int const &child : g[vertex]){

        if (stack[child]) return true;

        cyclic = cyclic || hasCycle(child, visited, stack, g);
    }
    stack[vertex] = false;
    return cyclic;
}

bool hasCycle(Graph &g){
    std::vector<bool> visited(g.size(), false), stack(g.size(), false);
    bool cyclic = false;
    for (int i = 0; i < g.size(); ++i){
        cyclic = cyclic || hasCycle(i, visited, stack,g);
    }
    return cyclic;
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

    std::cout << std::boolalpha << hasCycle(graph) << '\n';

    return 0;
}