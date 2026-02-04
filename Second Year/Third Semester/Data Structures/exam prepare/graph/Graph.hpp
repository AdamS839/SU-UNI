#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include <algorithm>
#include <vector>
#include "Dictionary.hpp"

template<typename V>
class Graph {
public:
  bool empty() const { return m_graph.empty(); }

  void addVertex(V const &v) {
    if (m_graph.lookup(v).has_value())
      return;

    m_graph.insert(v, std::vector<V>{});
  }

  void addEdge(V const &u, V const& v) {
    if (!hasVertex(u) || !hasVertex(v))
      return;

    m_graph[u].push_back(v);
    if (!m_isDirected)
      m_graph[v].push_back(u);
  }

  bool hasVertex(V const &v) const {
    return m_graph.lookup(v).has_value();
  }

  bool hasEdge(V const &u, V const& v) const {
    if (!hasVertex(u) || !hasVertex(v))
      return false;

    return std::find(m_graph[u].begin(),
                     m_graph[u].end(),
                     v)
           != m_graph[u].end();
  }

  bool isDirected() const { return m_isDirected; }

  std::vector<V> vertices() const {
    std::vector<V> result;

    for (auto iter = m_graph.begin(); iter != m_graph.end(); ++iter) {
      result.push_back(iter.key());
    }

    return result;
  }

  std::vector<V> const &adjacent(V const &v) const {
    return m_graph[v];
  }

public:
  // хубаво е този конструктор да е експлицитен,
  // т.е. да трябва да го извикаме явно,
  // защото иначе бихме могли да преобразуваме
  // bool до граф неявно, което не е добра практика
  explicit Graph(bool isDirected=false)
  : m_isDirected(isDirected) {}

private:
  Dictionary<V, std::vector<V> > m_graph;
  bool m_isDirected;
};

#endif // __GRAPH_HPP