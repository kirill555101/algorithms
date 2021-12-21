#include "set_graph.h"

SetGraph::SetGraph(size_t verticesNumber):
  verticesNumber(verticesNumber), out(verticesNumber), in(verticesNumber) {}

SetGraph::SetGraph(const IGraph& graph):
  verticesNumber(graph.VerticesCount()), out(verticesNumber), in(verticesNumber) {
  for (int i = 0; i < verticesNumber; ++i){
    std::vector<int> vertices = graph.GetNextVertices(i);

    for (int j : vertices) {
      AddEdge(i, j);
    }
  }
}

void SetGraph::AddEdge(int from, int to) {
  out[from].insert(to);
  in[to].insert(from);
}

int SetGraph::VerticesCount() const {
  return verticesNumber;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
  std::vector <int> vertices;

  for (int i : out[vertex]) {
    vertices.push_back(i);
  }

  return vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
  std::vector <int> vertices;

  for (int i : in[vertex]) {
    vertices.push_back(i);
  }

  return vertices;
}
