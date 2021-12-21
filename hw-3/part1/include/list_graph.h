#pragma once

#include <list>

#include "i_graph.h"

class ListGraph : public IGraph {
public:
  ListGraph(size_t verticesNumber);

  ListGraph(const IGraph& graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;

  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  size_t verticesNumber;

  std::vector<std::list<int>> in;

  std::vector<std::list<int>> out;
};
