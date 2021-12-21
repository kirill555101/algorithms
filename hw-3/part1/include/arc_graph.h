#pragma once

#include "i_graph.h"

class ArcGraph : public IGraph {
public:
  ArcGraph(size_t verticesNumber);

  ArcGraph(const IGraph& graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;

  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  size_t verticesNumber;

  std::vector<std::pair<int, int>> edges;
};
