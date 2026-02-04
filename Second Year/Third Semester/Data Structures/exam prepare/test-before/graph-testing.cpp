#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <climits>
#include <algorithm>

using graph = std::vector<std::list<int>>;

int shortestPathBfs(graph &g, int from, int to){
    std::vector<bool> visited(g.size(), false);

    int result = 0;
    std::queue<int> q;
    q.push(from);
    visited[from] = true;

    while (!q.empty()){
        int qsize = q.size();
        for (int i = 0; i < qsize; ++i){
            int curr = q.front();
            q.pop();

            if (curr == to) return result;

            for (int const &child : g[curr]){
                if(!visited[child]){
                    visited[child] = true;
                    q.push(child);
                }
            }
        }
        result++;
    }

    return INT_MAX;
}

void pathsFromToDfs(int from, int to, graph const &g, std::vector<bool> &visited, std::vector<int> &curr, std::vector<std::vector<int>> &allPaths){
    if (from == to){
        curr.push_back(from);
        allPaths.push_back(curr);
        curr.pop_back();
        return;
    }
    visited[from] = true;
    curr.push_back(from);

    for (int const &child : g[from]){
        if (!visited[child]){
            pathsFromToDfs(child, to, g, visited, curr, allPaths);
        }
    }
    visited[from] = false;
    curr.pop_back();
}

std::vector<std::vector<int>> pathsFromToDfs(graph &g, int from, int to){
    std::vector<bool> visited(g.size(), false);
    std::vector<std::vector<int>> result;
    std::vector<int> acc;
    pathsFromToDfs(from, to, g, visited, acc, result);
    return result;
}


std::vector<int> toposort(graph const &g){
    std::vector<int> result;
    std::vector<int> inDegree(g.size(), false);

    for (int i = 0; i < g.size(); ++i){
        for (int const &child : g[i]){
            inDegree[child]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < g.size(); ++i){
        if (inDegree[i] == 0) q.push(i);
    }

    while (!q.empty()){
        int curr = q.front(); 
        q.pop();

        result.push_back(curr);

        for (int const &child : g[curr]){
            inDegree[child]--;
            if (inDegree[child] == 0) q.push(child);
        }
    }

    return result;
}

bool hasCycle(int vert, std::vector<bool> &visited, std::vector<bool> stack, std::vector<int> &path, std::vector<int> &result, graph const &g){
    if (visited[vert]) return false;

    visited[vert] = true;
    stack[vert] = true;

    path.push_back(vert);

    for (int child : g[vert]){
        if (!visited[child]){
            if (hasCycle(child, visited, stack, path, result, g)) return true;
        }
        else if (stack[child]){
            auto it = std::find(path.begin(), path.end(), child);
            result.assign(it, path.end());
            result.push_back(child);
            return true;
        }
    }
    stack[vert] = false;
    path.pop_back();
    return false;
}

std::vector<int> hasCycle(graph &g){
    std::vector<bool> visited(g.size(), false), stack(g.size(), false);
    std::vector<int> path, result;
    for(int i = 0; i < g.size(); ++i){
        if (hasCycle(i, visited, stack, path, result, g)) return result;
    }
    return {};
}

int main() {

    graph g = {
        {1},
        {2},
        {3, 4},
        {4},
        {5},
        {}
    };

    graph cycleg = {
        {1},
        {2},
        {3, 4},
        {4},
        {5},
        {2}
    };

    // std::cout << shortestPathBfs(g, 0, 4) << '\n';
    
    // std::vector<std::vector<int>> paths = pathsFromToDfs(g, 0, 5);
    // for (std::vector<int> vec : paths){
    //     std::cout << '[';
    //     for (int v : vec){
    //         std::cout << v << ' ';
    //     }
    //     std::cout << ']';
    // }
    // std::cout << '\n';

    // std::vector<int> topsort = toposort(g);
    // for(int v : topsort){
    //     std::cout << v << ' ';
    // }
    // std::cout << '\n';

    std::vector<int> cycle = hasCycle(cycleg);
    for (int v : cycle){
        std::cout << v << ' ';
    }
    std::cout << '\n';

    return 0;
}