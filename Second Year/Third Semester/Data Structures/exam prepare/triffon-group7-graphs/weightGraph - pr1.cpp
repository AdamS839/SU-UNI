#include <iostream>
#include <vector>
#include <list>
#include <climits>

using weightGraph = std::vector<std::list<std::pair<int,int>>>;

// int shortestPathDfs(int from, int to, weightGraph const &g, std::vector<bool> &visited, int &curr, int &shortest){
//     if (from == to) return curr;
//     if (visited[from]) return shortest;
//     visited[from] = true;

//     for (int const &child : g[from]){
//         if (!visited[child]){
//             int res = shortestPathDfs(child, to, g, visited, curr + 1, shortest);
//             shortest = std::min(res, shortest);
//         }
//     }
//     visited[from] = false;
//     return shortest;
// }

void shortestPathFromTo(int from, int to, weightGraph const &g, std::vector<bool> &visited, int currW, int &shortestW){
    if (from == to) {
        shortestW = std::min(currW, shortestW);
        return;
    }

    visited[from] = true;

    for (auto &[child, weight] : g[from]){
        if (!visited[child]){
            shortestPathFromTo(child, to, g, visited, currW + weight, shortestW);
        }
    }
    visited[from] = false;
}

int shortestPathFromTo(int from, int to, weightGraph &g){
    std::vector<bool> visited(g.size(), false);
    int weight = INT_MAX;
    shortestPathFromTo(from, to, g, visited, 0, weight);
    return weight; 
}

int main() {

    weightGraph g = {
        {{1, 5}},          // 0 -> 1 (тегло 5)
        {{0, 5}, {2, 3}, {3, 6}}, // 1 -> 0 (5), 1 -> 2 (3), 1 -> 3 (6)
        {{1, 3}, {4, 2}},  // 2 -> 1 (3), 2 -> 4 (2)
        {{1, 6}, {5, 4}},  // 3 -> 1 (6), 3 -> 5 (4)
        {{2, 2}, {6, 7}},  // 4 -> 2 (2), 4 -> 6 (7)
        {{3, 4}, {6, 1}},  // 5 -> 3 (4), 5 -> 6 (1)
        {{4, 7}, {5, 1}, {7, 3}}, // 6 -> 4 (7), 6 -> 5 (1), 6 -> 7 (3)
        {{6, 3}, {8, 2}, {9, 4}}, // 7 -> 6 (3), 7 -> 8 (2), 7 -> 9 (4)
        {{7, 2}},          // 8 -> 7 (2)
        {{7, 4}}           // 9 -> 7 (4)
    };

    std::cout << shortestPathFromTo(0, 7, g) << '\n';
}