/*
  Дан базовый интерфейс для представления ориентированного графа:
  struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
  };

  Необходимо написать несколько реализаций интерфейса:
  ListGraph, хранящий граф в виде массива списков смежности,
  MatrixGraph, хранящий граф в виде матрицы смежности,
  SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
  ArcGraph, хранящий граф в виде одного массива пар {from, to}.

  Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
  Для каждого класса создавайте отдельные h и cpp файлы.
  Число вершин графа задается в конструкторе каждой реализации.
*/

#include <iostream>

#include "list_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"
#include "arc_graph.h"

int main() {
  size_t size;
  std::cin >> size;

  ListGraph graph(size);

  for (size_t i = 0; i < size; ++i) {
    int from, to;
    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }

  ListGraph listGraph = graph;
  MatrixGraph matrixGraph = graph;
  SetGraph setGraph = graph;
  ArcGraph arcGraph = graph;

  while(true) {
    char command;
    std::cin >> command;

    switch(command) {
      case 'a': { // append
        int from, to;
        std::cin >> from >> to;

        listGraph.AddEdge(from, to);
        matrixGraph.AddEdge(from, to);
        setGraph.AddEdge(from, to);
        arcGraph.AddEdge(from, to);

        break;
      }
      case 'c': { // vertices count
        std::cout << "List: " << listGraph.VerticesCount() << std::endl;
        std::cout << "Matrix: " << matrixGraph.VerticesCount() << std::endl;
        std::cout << "Set: " << setGraph.VerticesCount() << std::endl;
        std::cout << "Arc: " << arcGraph.VerticesCount() << std::endl;

        break;
      }
      case 'n': { // next bertices
        int vertex;
        std::cin >> vertex;

        std::vector<int> vertices1 = listGraph.GetNextVertices(vertex);
        std::vector<int> vertices2 = matrixGraph.GetNextVertices(vertex);
        std::vector<int> vertices3 = setGraph.GetNextVertices(vertex);
        std::vector<int> vertices4 = arcGraph.GetNextVertices(vertex);

        std::cout << "List: ";
        for(int i : vertices1) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        std::cout << "Matrix: ";
        for(int i : vertices2) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        std::cout << "Set: ";
        for(int i : vertices2) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        std::cout << "Arc: ";
        for(int i : vertices3) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        break;
      }
      case 'p': { // prev bertices
        int vertex;
        std::cin >> vertex;

        std::vector<int> vertices1 = listGraph.GetPrevVertices(vertex);
        std::vector<int> vertices2 = matrixGraph.GetPrevVertices(vertex);
        std::vector<int> vertices3 = setGraph.GetPrevVertices(vertex);
        std::vector<int> vertices4 = arcGraph.GetPrevVertices(vertex);

        std::cout << "List: ";
        for(int i : vertices1) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        std::cout << "Matrix: ";
        for(int i : vertices2) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        std::cout << "Set: ";
        for(int i : vertices2) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        std::cout << "Arc: ";
        for(int i : vertices3) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;

        break;
      }
      default:
        return 0;
    }
  }

  return 0;
}
