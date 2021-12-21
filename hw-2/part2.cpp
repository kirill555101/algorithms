/*
  Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
  Требуется построить бинарное дерево, заданное наивным порядком вставки.
  Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
  то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
  Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

  2_3. Выведите элементы в порядке post-order (снизу вверх).
*/

#include <iostream>
#include <queue>
#include <unordered_set>

class Tree {
public:
  Tree(bool (*cmp)(int n1, int n2)) : cmp(cmp) {}

  ~Tree() {
    if (root == nullptr) {
      return;
    }

    Node* current = root;
    std::queue<Node *> queue;

    queue.push(root);
    while (!queue.empty()) {
      Node *current = queue.front();
      queue.pop();

      if (current->left != nullptr) {
        queue.push(current->left);
      }
      if (current->right != nullptr) {
        queue.push(current->right);
      }

      delete current;
    }
  }

  void insert(int value) {
    if (root == nullptr) {
      root = new Node;
      root->value = value;
      return;
    }

    Node* current = root;
    while (true) {
      // For left part
      if (cmp(current->value, value)) {
        if (current->left == nullptr) {
          Node* tmp = new Node;
          tmp->value = value;
          current->left = tmp;
          break;
        }

        current = current->left;
        continue;
      }

      // For right part
      if (current->right == nullptr) {
        Node* tmp = new Node;
        tmp->value = value;
        current->right = tmp;
        break;
      }

      current = current->right;
    }
  }

  void print() const {
    Node* current = root;
    std::unordered_set<Node*> visited;

    while (current != nullptr && visited.find(current) == visited.end()) {
      if (current->left != nullptr && visited.find(current->left) == visited.end()) {
        current = current->left;
      } else if (current->right != nullptr && visited.find(current->right) == visited.end()) {
        current = current->right;
      } else {
        std::cout << current->value << " ";
        visited.insert(current);
        current = root;
      }
    }

    std::cout << std::endl;
  }

private:
  struct Node {
    Node* left = nullptr;

    Node* right = nullptr;

    int value;
  };

  Node* root = nullptr;

  bool (*cmp)(int n1, int n2);
};

bool cmp(int n1, int n2) {
  return n1 > n2;
}

int main() {
  size_t count;
  std::cin >> count;

  Tree tree(cmp);
  int value;

  for (size_t i = 0; i < count; ++i) {
    std::cin >> value;
    tree.insert(value);
  }

  tree.print();

  return 0;
}
