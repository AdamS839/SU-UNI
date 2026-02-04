#include <iostream>
#include <vector>
#include <list>

using Graph = std::vector<std::list<int>>;

void pathsFromToLength(int from, int to, Graph const &g, std::vector<bool> &visited, int edgeLen, int &count){
    if (from == to && edgeLen == 0){
        count++;
    }

    visited[from] = true;
    for (int child : g[from]){
        if (!visited[child]){
            pathsFromToLength(child, to, g, visited, edgeLen - 1, count);
        }
    }
    visited[from] = false;
}

int pathsFromToLength(int from, int to, Graph &g, int edgeLen){
    std::vector<bool> visited(g.size(), false);
    int counter = 0;
    pathsFromToLength(from, to, g, visited, edgeLen, counter);
    return counter;
}

int main() {

    Graph graph = {
        {1},
        {0,2,3},
        {1,4},
        {1,5},
        {2,6},
        {3,6},
        {4,5,7},
        {6, 8, 9},
        {7},
        {7}
    };

    std::cout << pathsFromToLength(0, 7, graph, 5) << '\n';
}