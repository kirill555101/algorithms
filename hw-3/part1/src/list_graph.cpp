#include "list_graph.h"

ListGraph::ListGraph(size_t verticesNumber):
  verticesNumber(verticesNumber), in(verticesNumber), out(verticesNumber) {}

ListGraph::ListGraph(const IGraph& graph):
  verticesNumber(graph.VerticesCount()), in(verticesNumber), out(verticesNumber) {
  for (size_t i = 0; i < verticesNumber; ++i) {
    std::vector<int> vertices = graph.GetNextVertices(i);

    for (int j : vertices) {
      AddEdge(i, j);
    }
  }
}

void ListGraph::AddEdge(int from, int to) {
  if (in.size() < out.size()){
    for (int i : in[to]) {
      if (i == from) {
        return;
      }
    }

    in[to].push_back(from);
    out[from].push_back(to);

    return;
  }

  for (int i : out[from]) {
    if (i == to) {
      return;
    }
  }

  in[to].push_back(from);
  out[from].push_back(to);
}

int ListGraph::VerticesCount() const {
  return verticesNumber;
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  std::vector <int> vertices;

  for (int i : out[vertex]) {
    vertices.push_back(i);
  }

  return vertices;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  std::vector <int> vertices;

  for (int i : in[vertex]) {
    vertices.push_back(i);
  }

  return vertices;
}
