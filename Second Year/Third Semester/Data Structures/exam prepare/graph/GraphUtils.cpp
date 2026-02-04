#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>

void addEdge(std::vector<std::list<int>> &g, int v, int u, bool isDirected = false){
    g[v].push_back(u);

    if (!isDirected){
        g[u].push_back(v);
    }
}

void dfsVisit(std::vector<std::list<int>> const &g, int curr, std::vector<bool> &visited, std::vector<int> &result){
    if (visited[curr]) return;

    visited[curr] = true;
    result.push_back(curr);

    for (int successor : g[curr]){
        if (!visited[successor]){
            dfsVisit(g, successor, visited, result  );
        }
    }
}

std::vector<int> dfs(std::vector<std::list<int>> const &g, int start){
    std::vector<int> result;
    std::vector<bool> visited(g.size(), false);
    dfsVisit(g, start, visited, result);
    return result;
}

int connectedComponents(std::vector<std::list<int>> const &g, int start){
    int result = 0;
    std::vector<bool> visited(g.size(), false);

    for(int i = 0; i < g.size(); ++i){
        if (!visited[i]){
            dfsVisit(g, i, visited);
            result++;
        }
    }

    return result;
}

std::vector<int> bfs(std::vector<std::list<int>> const &g){
    std::vector<int> result;
    std::vector<bool> visited(g.size(), false);

    for (int i = 0; i < g.size(); ++i){
        if(visited[i]) continue;

        std::queue<int> q;
        q.push(i);

        while (!q.empty()){
            int currVert = q.front();
            q.pop();

            if (visited[currVert]) continue;

            visited[currVert] = true;
            result.push_back(currVert);

            for (int const &child : g[currVert]){
                q.push(child);
            }
        }
    }
    return result;
}

int shortestPath(std::vector<std::list<int>> const &g, int &from, int &to){
    std::vector<bool> visited(g.size(), false);

    std::queue<int> q;
    q.push(from);

    int level = 0;
    while (!q.empty()){
        int qsize = q.size();
        for (int i = 0; i < qsize; ++i){
            int currVert = q.front();
            q.pop();

            if(currVert == to) return level;

            if (visited[currVert]) continue;

            visited[currVert] = true;

            for (int &node : g[currVert]){
                q.push(node);
            }
        }
        level++;
    }

    return INT_MAX;
}

int shortestPathDFShelp(std::vector<std::list<int>> const &g, int const &from, int const &to, std::vector<bool> &visited, int currLen, int shortest){
    if (currLen >= shortest) return shortest;
    
    if (from == to) return currLen;

    if (visited[from]) return shortest;

    visited[from] = true;

    for(int child : g[from]){
        int result = shortestPathDFShelp(g, child, to, visited, currLen + 1, shortest);
        shortest = std::min(result, shortest); 
    }
    //
    visited[from] = false;

    return shortest;
}

int shortestPathDFS(std::vector<std::list<int>> const &g, int from, int to){
    std::vector<bool> visited(g.size(), false);

    return shortestPathDFShelp(g, from, to, visited, 0, INT_MAX);
}

bool hasCycle(int const &vertex, std::vector<std::list<int>> const &g, std::vector<bool> &visited, std::vector<bool> &stack, int const &parent, bool isDirected = false){
    if (visited[vertex]) return false;

    visited[vertex] = true;
    stack[vertex] = true;

    bool cyclic = false;
    for (int neighbor : g[vertex]){
        if (!isDirected && neighbor == parent) continue;

        if (stack[neighbor]) return true;

        cyclic = cyclic || hasCycle(neighbor, g, visited, stack, vertex, isDirected);
    }

    stack[vertex] = false;
    return cyclic;
}

bool hasCycle(std::vector<std::list<int>> const &g){
    std::vector<bool> visited(g.size(), false), stack(g.size(), false);

    bool cyclic = false;
    for (int i = 0; i < g.size(); ++i){
        cyclic = cyclic || hasCycle(i, g, visited, stack, i);
    }
    return cyclic;
}


void allPathsFromTo(int const &from, int const &to, std::vector<std::list<int>> const &g, 
                    std::vector<bool> &visited, std::vector<int> &currPath, std::vector<std::vector<int>> &allPaths){
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
        allPathsFromTo(child, to, g, visited, currPath, allPaths);
    }

    visited[from] = false;
    currPath.pop_back();
}


std::vector<std::vector<int>> allPathsFromTo(int const &from, int const &to, std::vector<std::list<int>> const &g){
    std::vector<std::vector<int>> result;

    std::vector<int> acc;
    std::vector<bool> visited(g.size(), false);

    allPathsFromTo(from, to, g, visited, acc, result);
    return result;
}


std::vector<int> toposort(std::vector<std::list<int>> const &g){
    std::vector<int> result;

    std::vector<int> inDegrees(g.size(), 0);

    for (int i = 0; i < g.size(); ++i){
        for (int neighbor : g[i]){
            if (neighbor >= 0 && neighbor < g.size()) inDegrees[neighbor]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i< g.size(); ++i){
        if (inDegrees[i] == 0) q.push(i);
    }

    while (!q.empty()){
        int curr = q.front();
        q.pop();
        
        result.push_back(curr);

        for (int neighbor : g[curr]){
            if (neighbor >= 0 && neighbor < g.size()){
                inDegrees[neighbor]--;
                if (inDegrees[neighbor] == 0) q.push(neighbor);
            }
        }
    }

    if (result.size() != g.size()){
        return {};
    }

    return result;
}


bool hasPathFromTo(std::vector<std::list<int>> const &g, int &from, int &to, std::vector<bool> &visited){
    if (from == to) return true;

    if (visited[from]) return false;

    visited[from] = true;
    bool hasPath = false;

    for (int const &child : g[from]){
        hasPath = hasPath || hasPathFromTo(g, child, to, visited);
    }

    return hasPath;
}

bool hasPathFromTo(std::vector<std::list<int>> const &g, int from, int to){
    std::vector<bool> visited(g.size(), false);

    return hasPathFromTo(g, from, to, visited);
}