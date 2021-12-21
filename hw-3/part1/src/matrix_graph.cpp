#include "matrix_graph.h"

MatrixGraph::MatrixGraph(size_t verticesNumber):
  verticesNumber(verticesNumber), edges(verticesNumber) {
  for (std::vector<bool>& edge : edges) {
    edge.assign(verticesNumber, false);
  }
}

MatrixGraph::MatrixGraph(const IGraph& graph):
  verticesNumber(graph.VerticesCount()), edges(verticesNumber) {
  for (std::vector<bool>& edge : edges) {
    edge.assign(verticesNumber, false);
  }

  for (size_t i = 0; i < verticesNumber; ++i) {
    std::vector<int> vertices = graph.GetNextVertices(i);

    for (int j : vertices) {
      AddEdge(i, j);
    }
  }
}

void MatrixGraph::AddEdge(int from, int to) {
  edges[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
  return verticesNumber;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
  std::vector <int> vertices;

  for (size_t i = 0; i < verticesNumber; ++i) {
    if (edges[vertex][i]) {
      vertices.push_back(i);
    }
  }

  return vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
  std::vector <int> vertices;

  for (size_t i = 0; i < verticesNumber; ++i) {
    if (edges[i][vertex]) {
      vertices.push_back(i);
    }
  }

  return vertices;
}
