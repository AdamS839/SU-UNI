#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include <algorithm>
#include <vector>
#include "Dictionary.hpp"

template<typename V>
class Graph {
public:
    bool empty() const { return m_graph.empty(); }
    void addVertex(V const &v){
        if (m_graph.lookup(v).has_value()) return;
        m_graph.insert(v, std::vector<V>());
    }

    void addEdge(V const &u, V const &v){
        if (!hasVertex(u) || !hasVertex(v)) return;
        m_graph[u].puush_back(v);
        if (!m_isDirected){ m_graph[v].push_back(u); }
    }

    bool hasVertex(V const &v) const{
        return m_graph.lookup(v).has_value();
    }

    bool hasEdge(V const &u, V const &v) const{
        if (!hasVertex(u) || !hasVertex(v)) return false;
        return std::find(m_graph[u].begin(), m_graph[v].end(), v) != m_graph[u].end();
    }

    bool isDirected() const {
        return m_isDirected;
    }

    std::vector<V> vertices() const{
        std::vector<V> result;
        for(auto iter = m_graph.begin(); iter != m_graph.end(); ++iter){
            result.push_back(iter.key());
        }
        return result;
    }

    std::vector<V> const &adjecent(V const &v) const{
        
    }

public:
    Graph(bool m_isDirected=false) : m_isDirected(m_isDirected) {}
private:
  Dictionary<V, std::vector<V> > m_graph;
  bool m_isDirected;
};

#endif // __GRAPH_HPP
