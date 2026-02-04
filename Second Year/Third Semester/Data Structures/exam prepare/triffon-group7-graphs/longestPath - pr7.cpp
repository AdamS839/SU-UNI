#include <iostream>
#include <vector>
#include <list>
#include <climits>

using Graph = std::vector<std::list<int>>;

void longestPath(int vert, int parent, int dist, Graph const &g, int &maxDist, int &farthest){
    if (dist  > maxDist){
        maxDist = dist;
        farthest = vert;
    }

    for (int child : g[vert]){
        if (child != parent) longestPath(child, vert, dist + 1, g, maxDist, farthest);
    }
}

int longestPath(Graph &g){
    int maxDist = -1;
    int u = 0;
    longestPath(0, -1, 0, g, maxDist, u);
    maxDist = -1;
    int v = u;
    longestPath(u, -1, 0, g, maxDist, u);
    return maxDist;
}

int main() {

    Graph graph = {
        {1},
        {0,3},
        {4},
        {1,5},
        {2,6},
        {3,6},
        {4,5,7},
        {6, 8, 9},
        {7},
        {7}
    };

    std::cout << longestPath(graph) << '\n';

    return 0;
}