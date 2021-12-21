/*
  Дан невзвешенный неориентированный граф.
  В графе может быть несколько кратчайших путей между какими-то вершинами.
  Найдите количество различных кратчайших путей между заданными вершинами.

  Требования: сложность O(V+E).
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

class Graph {
public:
  Graph(size_t vertices_number): vertices_number(vertices_number), out(vertices_number) {}

  void add_edge(int from, int to) {
    for (int i : out[from]) {
      if (i == to) {
        return;
      }
    }

    out[to].push_back(from);
    out[from].push_back(to);
  }

  int get_vertices_count() const {
    return vertices_number;
  }

  std::vector<int> get_next_vertices(int vertex) const {
    std::vector<int> vertices;

    for (int i : out[vertex]) {
      vertices.push_back(i);
    }

    return vertices;
  }

  int count_paths(int from, int to) {
    std::vector<Vertex> temp_vertices(vertices_number);
    std::queue<int> queue;

    queue.push(from);
    temp_vertices[from].paths = 1;

    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();

      std::vector<int> nextVertices = get_next_vertices(v);

      for (int i : nextVertices) {
        // If not visited, then push into queue
        if (temp_vertices[i].paths == 0) {
          queue.push(i);
          temp_vertices[i].depth = temp_vertices[v].depth + 1;
          temp_vertices[i].paths = temp_vertices[v].paths;
          continue;
        }
        // If visited and has same depth, then increase path number
        if (temp_vertices[i].depth == temp_vertices[v].depth + 1) {
          temp_vertices[i].paths += temp_vertices[v].paths;
        }
      }
    }

    return temp_vertices[to].paths;
  }

private:
  struct Vertex {
    int depth = 0;

    int paths = 0;
  };

  size_t vertices_number = 0;

  std::vector<std::list<int>> out;
};

int main() {
  size_t v, n;
  std::cin >> v >> n;

  Graph graph(v);

  for (size_t i = 0; i < n; ++i) {
    int from, to;
    std::cin >> from >> to;

    graph.add_edge(from, to);
  }

  int from, to;
  std::cin >> from >> to;

  std::cout << graph.count_paths(from, to) << std::endl;

  return 0;
}
