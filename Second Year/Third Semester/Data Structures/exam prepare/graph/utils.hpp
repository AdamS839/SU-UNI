#ifndef __GRAPH_UTIL_HPP
#define __GRAPH_UTIL_HPP

#include "Set.hpp"
#include <climits>
#include "Dictionary.hpp"
#include <cstddef>
#include <vector>
#include <queue>


template<typename V, template<typename> class Graph>
class GraphUtil {
public:
    static std::size_t outDegree(V const &v, Graph<V> const &g){
        return g.adjacent(v).size();
    }
    static std::size_t inDegree(V const &v, Graph<V> const &g){
        std::size_t deg = 0;

        for(V const &vertex : g.vertices()){
            for(V const &child : g.adjacent(vertex)){
                if(child == v) deg++;
            }
        }
        return deg;
    }

    static std::vector<V> dfs(Graph<V> const &g){
        std::vector<V> result;
        Set<T> visited;
    
        for(V const &vertex : g.vertices()){
            dfsFrom(vertex, g, result, visited);
        }

        return result;
    }

    static std::vector<V> bfs(Graph<V> const &g){
        std::vector<V> result;
        Set<T> visited;

        for (V const &vertex : g.vertices()){
            if (visited.contains(vertex)){
                continue;
            }

            std::queue<V> q;
            q.push(vertex);

            while(!q.empty()){
                V currVertex = q.front();
                q.pop();
                if (visited.contains(currVertex)) continue;

                visited.insert(currVertex);
                result.push_back(currVertex);

                for (V const &child : g.adjacent(currVertex)) q.push(child)
            }
        }
        return result;
    }

    static std::size_t connectedComponents(Graph<V> const &g){
        std::size_t result = 0;
        Set<V> visited;

        for (V const &vertex : g.vertices()){
            if (!visited.contains(  vertex)){
                dfsFrom(vertex, g, visited);
                result++;
            }
        }
        return result;
    }

    static bool hasPathFromTo(V const &from, V const &to, Graph<V> const &g){
        Set<V> visited;
        return hasPathFromTo(from, to, g, visited);
    }

    static std::size_t shortestPath(V const &from, V const &to, Graph<V> const &G){
        Set<V> visited;

        std::queue<V> q;
        q.push(from);

        std::size_t level = 0;
        while(!q.empty()){
            std::size_t qsize = q.size();

            for (std::size_t i = 0; i < qsize; ++i){
                V currVert = q.front();
                q.pop();

                if (currVert == to) return level;

                if (visited.contains(currVert)) continue;

                visited.insert(currVert);

                for (V const &child : g.adjacent(currVert)) q.push(child);
            }
            level++;
        }
        return ULLONG_MAX;
    }

    static std::size_t shortestPathDfs(V const &from, V const &to, Graph<V> const &g){
        Set<V> visited;
        return shortestPathDfs(from, to, g, visited);
    }

    static std::vector<std::vector<V>> allPathsFromTo(V const &from, V const &to, Graph<V> const &g){
        std::vector<std::vector<V>> result;

        std::vector<V> acc;
        Set<V> visited;

        allPathsFromTo(from, to, g, visited, acc, result);

        return result;
    }

    static std::vector<V> toposort(Graph<V> const &g){
        std::vector<V> result;

        Dictionary<V, std::size_t> inDegrees;
        std::vector<V> vs = g.vertices();

        for(V const &vertex : vs){
            inDegrees.insert(vertex, 0);
        }

        for (V const &vertex : vs){
            for(V const &child : g.adjacent(vertex)){
                inDegrees[child]++;
            }
        }

        std::queue<V> q;
        for(V const &vertex : vs){
            if (inDegrees[vertex] == 0){
                q.push(vertex);
            }
        }

        while (!q.empty()){
            V currVert = q.front();
            q.pop();

            result.push_back(currVert);
            for(V const &child : g.adjancet(currVert)){
                inDegrees[child]--;
                if(inDegrees[child] == 0){
                    q.push(child);
                }
            }
        }
        return result;
    }

    static bool hasCycle(Graph<V> const &g){
        return g.vertices().size() != toposort(g).size();
    }

    static bool hasCycle(Graph<V> const &g){
        Set<V> visited, stack;

        bool cycle = false;
        for (V const &vertex : g.vertices()){
            cycle = cycle || hasCycle(vertex, g, visited, stack, vertex);
        }
        return cycle;
    }

private:

    static void dfsFrom(V const &v, Graph<V> const &g, std::vector<V> &result, Set<V> &visited){
        if (visited.contains(v)) return;

        visited.insert(v);
        result.push_back(v);

        for(V const &child : g.adjacent(v)){
            dfsFrom(child, g, result, visited);
        }
    }

    static void dfsFrom(V const &v, Graph<V> const &g, Set<V> &visited) {
        if (visited.contains(v))
        return;

        visited.insert(v);

        for (V const &child : g.adjacent(v))
        dfsFrom(child, g, visited);
    }

    static bool hasPathFromTo(V const &from, V const &to, Graph<V> const &g, Set<V> &visited) {
        if (from == to)
        return true;

        if (visited.contains(from))
        return false;

        visited.insert(from);

        bool hasPath = false;

        for (V const &child : g.adjacent(from))
        hasPath = hasPath || hasPathFromTo(child, to, g, visited);

        return hasPath;
    } 

    static size_t shortestPathDfs(V const &from, V const &to, Graph<V> const &g, Set<V> &visited, size_t currLength, size_t shortest) {
        if (from == to)
        return currLength;

        if (visited.contains(from))
        return shortest;

        visited.insert(from);

        for (V const &child : g.adjacent(from)) {
        size_t result = shortestPathDfs(child, to, g, visited, currLength + 1, shortest);
        shortest = std::min(result, shortest);
        }

        visited.remove(from);

        return shortest;
    }

    static void allPathsFromTo(V const &from, V const &to, Graph<V> const &g, Set<V> &visited, std::vector<V> &currPath, std::vector<std::vector<V> > &allPaths) {
        if (from == to) {
        currPath.push_back(from);
        allPaths.push_back(currPath);
        currPath.pop_back();
        return;
        }

        if (visited.contains(from))
        return;

        visited.insert(from);
        currPath.push_back(from);

        for (V const &child : g.adjacent(from))
        allPathsFromTo(child, to, g, visited, currPath, allPaths);

        visited.remove(from);
        currPath.pop_back();
    }

    static bool hasCycle(V const &vertex, Graph<V> const &g, Set<V> &visited, Set<V> &stack, V const &parent) {
        if (visited.contains(vertex))
        return false;

        visited.insert(vertex);
        stack.insert(vertex);

        bool cyclic = false;
        for (V const &child : g.adjacent(vertex)) {
        if (!g.isDirected() && child == parent && vertex != child)
            continue;

        if (stack.contains(child))
            return true;

        cyclic = cyclic || hasCycle(child, g, visited, stack, vertex);
        }

        stack.remove(vertex);

        return cyclic;
    }

};

#endif // __GRAPH_UTIL_HPP