#include <iostream>
#include <vector>
#include <list>

using Graph = std::vector<std::list<int>>;

void allPathsFromTo(int from, int to,std::vector<bool> &visited, Graph const &g, std::vector<int> &currPath, std::vector<std::vector<int>> &allPaths){
    if (from == to){
        currPath.push_back(from);
        allPaths.push_back(currPath);
        currPath.pop_back();
        return;
    }

    if (visited[from]) return;
    visited[from] = true;
    currPath.push_back(from);

    for (int const &child : g[from]){
        allPathsFromTo(child, to, visited, g, currPath, allPaths);
    }
    visited[from] = false;
    currPath.pop_back();
}


std::vector<std::vector<int>> allPathsFromTo(int from, int to, Graph &g){
    std::vector<bool> visited(g.size(), false);
    std::vector<std::vector<int>> result;
    std::vector<int> acc;
    allPathsFromTo(from, to, visited, g, acc, result);
    return result;
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

    std::vector<std::vector<int>> res = allPathsFromTo(0, 9, graph);

    for(std::vector<int> vec : res){
        std::cout << '[';
        for (int val : vec){
            std::cout << val << ' ';
        }
        std::cout << "] ";
    }
    std::cout << '\n';

    return 0;
}