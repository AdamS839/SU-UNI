#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>



int shortestPath(std::vector<std::list<int>> const &g, int const &from, int const &to){
    std::vector<bool> visited(g.size(), false);

    std::queue<int> q;
    q.push(from);
    visited[from] = true;

    int level = 0;
    while (!q.empty()){
        int qsize = q.size();
        for(int i = 0; i < qsize; ++i){
            int curr = q.front();
            q.pop();

            if(curr == to) return level;

            for (int const &child : g[curr]){
                if(!visited[child]){
                    visited[child] = true;
                    q.push(child);
                }
            }
        }
        level++;
    }
    return INT_MAX;
}

void dfs(std::vector<std::list<int>> const &g, int curr, std::vector<bool> &visited, std::vector<int> &result){
    if (visited[curr]) return;

    visited[curr] = true;
    result.push_back(curr);

    for (int const &child : g[curr]){
        dfs(g, child, visited, result);
    }
}

std::vector<int> dfs(std::vector<std::list<int>> const &g, int start){
    std::vector<int> result;
    std::vector<bool> visited(g.size(), false);
    dfs(g, start, visited, result);
    return result;
}

int shortestPathDfs(std::vector<std::list<int>> const &g, int from, int to, std::vector<bool> &visited, 
                    int currLength, int shortest){
    if (from == to) return currLength;

    if (visited[from]) return shortest;

    visited[from] = true;

    for(int const &child : g[from]){
        int res = shortestPathDfs(g, child, to, visited, currLength + 1, shortest);
        shortest = std::min(res, shortest);
    }
    visited[from] = false;
    return shortest;
}

int shortestPathDfs(std::vector<std::list<int>> const &g, int from, int to){
    std::vector<bool> visited(g.size(), false);
    return shortestPathDfs(g, from, to, visited, 0, INT_MAX);
}

int connectedComponents(std::vector<std::list<int>> const &g){
    int result = 0;
    std::vector<bool> visited(g.size(), false);
    std::vector<int> dummy;

    for (int i = 0; i < g.size(); ++i){
        if (!visited[i]){
            dfs(g, i, visited, dummy);
            result++;
        }
    }

    return result;
}

std::vector<int> bfs(std::vector<std::list<int>> const &g){
    std::vector<int> result;
    std::vector<bool> visited(g.size(), false);

    for(int i = 0; i < g.size(); ++i){
        if (visited[i]) continue;


        std::queue<int> q;
        q.push(i);
        visited[i] = true;

        while (!q.empty()){
            int curr = q.front();
            q.pop();

            result.push_back(curr);

            for (int const &child : g[curr]){
                if (!visited[child]){
                    visited[child] = true;
                    q.push(child);
                }
            }
        }
    }
    return result;
}

std::vector<int> toposort(std::vector<std::list<int>> const &g){
    std::vector<int> result;
    std::vector<int> inDegree(g.size(), 0);

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
            if(inDegree[child] == 0) q.push(child);
        }
    }

    if (result.size() != g.size()) return {};
    return result;
}

bool hasPathFromTo(std::vector<std::list<int>> const &g, int const &from, int const &to, std::vector<bool> &visited){
    if (from == to) return true;

    if (visited[from]) return false;

    visited[from] = true;
    bool haspath = false;
    for(int const &child : g[from]){
        haspath = haspath || hasPathFromTo(g, child, to, visited);
    }
    visited[from] = false;
    return haspath;
}

bool hasPathFromTo(std::vector<std::list<int>> const &g, int from, int to){
    std::vector<bool> visited(g.size(), false);
    return hasPathFromTo(g, from, to, visited);
}

void allPathsFromTo(std::vector<std::list<int>> const &g, int const &from, int const &to, std::vector<bool> &visited,
                    std::vector<int> &currPath, std::vector<std::vector<int>> &allPaths){
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
        allPathsFromTo(g, child, to, visited, currPath, allPaths);
    }
    visited[from] = false;
    currPath.pop_back();
}

std::vector<std::vector<int>> allPathsFromTo(std::vector<std::list<int>> const &g, int from, int to){
    std::vector<bool> visited(g.size(), false);
    std::vector<std::vector<int>> result;
    std::vector<int> acc;
    allPathsFromTo(g, from, to, visited, acc, result);
    return result;
}

bool hasCycle(int const &vertex, std::vector<std::list<int>> const &g, std::vector<bool> &visited,
              std::vector<bool> &stack, int const &parent, bool isDirected = false){
    if (visited[vertex]) return false;

    visited[vertex] = true;
    stack[vertex] = true;

    bool cyclic = false;
    for(int const &child : g[vertex]){
        if (!isDirected && child == parent) continue;

        if (stack[child]) return true;

        cyclic = cyclic || hasCycle(child, g, visited, stack, vertex);
    }
    stack[vertex] = false;
    return cyclic;
}

bool hasCycle(std::vector<std::list<int>> const &g){
    std::vector<bool> visited(g.size(), false), stack(g.size(), false);
    bool cyclic = false;
    for (int i = 0; i < g.size(); ++i){
        cyclic = cyclic || hasCycle(i, g, visited, stack, -1, false);
    }
    return cyclic;
}


int main() {
    std::cout << std::boolalpha;

    // Тест 1: Една голяма компонента
    std::vector<std::list<int>> singleComponent = {
        {1, 2}, 
        {0, 3}, 
        {0, 3}, 
        {1, 2},
    };

    std::vector<std::list<int>> g2 = {
        {1},
        {2},
        {3, 4},
        {4},
        {5},
        {}
    };
    // std::cout << "Single component: " << connectedComponents(singleComponent) << std::endl;  // 1
    // std::cout << "Shortest path: " << shortestPath(singleComponent, 0, 3) << '\n';
    // std::cout << "Has cycle: " << hasCycle(singleComponent) << '\n';
    // std::vector<int> topsort = toposort(g2);
    // for(int const &a : topsort){
    //     std::cout << a << ' ';
    // }
    // std::cout << '\n';

    return 0;
}