#pragma once

#include <unordered_set>

#include "i_graph.h"

class SetGraph : public IGraph {
public:
  SetGraph(size_t verticesNumber);

  SetGraph(const IGraph& graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;

  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  size_t verticesNumber;

  std::vector<std::unordered_set<int>> out;

  std::vector<std::unordered_set<int>> in;
};
