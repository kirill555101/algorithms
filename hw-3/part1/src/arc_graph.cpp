#include "arc_graph.h"

ArcGraph::ArcGraph(size_t verticesNumber): verticesNumber(verticesNumber) {}

ArcGraph::ArcGraph(const IGraph& graph):
  verticesNumber(graph.VerticesCount()) {
  for (size_t i = 0; i < verticesNumber; ++i){
    std::vector<int> vertices = graph.GetNextVertices(i);

    for (int j : vertices) {
      AddEdge(i, j);
    }
  }
}

void ArcGraph::AddEdge(int from, int to) {
  for (const auto& edge : edges) {
    if (edge.first == from && edge.second == to) {
      return;
    }
  }

  edges.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
  return verticesNumber;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> vertices;

  for (const auto& edge : edges) {
    if (edge.first == vertex) {
      vertices.push_back(edge.second);
    }
  }

  return vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> vertices;

  for (const auto& edge : edges) {
    if (edge.second == vertex) {
      vertices.push_back(edge.first);
    }
  }

  return vertices;
}
