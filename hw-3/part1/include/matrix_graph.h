#pragma once

#include "i_graph.h"

class MatrixGraph : public IGraph {
public:
  MatrixGraph(size_t verticesNumber);

  MatrixGraph(const IGraph& graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;

  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  size_t verticesNumber;

  std::vector<std::vector<bool>> edges;
};
