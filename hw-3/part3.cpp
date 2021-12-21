/*
  Требуется отыскать самый выгодный маршрут между городами.
  Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
*/

#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <climits>

class Graph {
public:
  Graph(size_t size) : size(size), edges(size, std::list<std::pair<unsigned, unsigned>>()) {}

  void add_edge(unsigned from, unsigned to, unsigned weight) {
    edges[from].push_back(std::make_pair(to, weight));
    edges[to].push_back(std::make_pair(from, weight));
  }

  std::vector<std::pair<unsigned, unsigned>> get_related(unsigned vertex) const {
    std::vector<std::pair<unsigned, unsigned>> vertices;

    for (const auto &edge : edges[vertex]) {
      vertices.push_back(edge);
    }

    return vertices;
  }

  int find_path(int from, int to) {
    std::vector<unsigned> vertices_path(size, UINT_MAX);
    vertices_path[from] = 0;

    std::set<std::pair<unsigned, unsigned>> queue;
    queue.emplace(std::make_pair(0, from));

    while (!queue.empty()) {
      unsigned v = (queue.begin())->second;
      queue.erase(queue.begin());

      auto paths = get_related(v);

      for (auto c : paths) {
        if (vertices_path[c.first] > vertices_path[v] + c.second) {
          if (vertices_path[c.first] != UINT_MAX) {
            queue.erase(std::make_pair(vertices_path[c.first], c.first));
          }

          vertices_path[c.first] = vertices_path[v] + c.second;
          queue.emplace(std::make_pair(vertices_path[c.first], c.first));
        }
      }
    }

    return (vertices_path[to] != UINT_MAX) ? vertices_path[to] : -1;
  }

private:
  size_t size;

  std::vector<std::list<std::pair<unsigned, unsigned>>> edges;
};

int main() {
  size_t n, m;
  std::cin >> n >> m;

  Graph graph(n);

  for (size_t i = 0; i < m; ++i) {
    unsigned s, t, w;
    std::cin >> s >> t >> w;
    graph.add_edge(s, t, w);
  }

  unsigned from, to;
  std::cin >> from >> to;

  std::cout << graph.find_path(from, to) << std::endl;

  return 0;
}
