/*
  Требование для всех вариантов Задачи 4
  Решение должно поддерживать передачу функции сравнения снаружи.

  Солдаты. В одной военной части решили построить в одну шеренгу по росту.
  Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
  а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
  Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
  а в конце – самые низкие. За расстановку солдат отвечал прапорщик,
  который заметил интересную особенность – все солдаты в части разного роста.
  Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
  а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.

  Требования: скорость выполнения команды - O(log n).
*/

#include <iostream>
#include <stack>
#include <vector>

class Tree {
public:
  Tree(bool (*cmp)(int n1, int n2)) : cmp(cmp) {}

  ~Tree() {
    clear(root);
  }

  void insert(int value, int &pos) {
    root = insert_element(root, value, pos);
  }

  void remove(int &pos) {
    root = remove_element(root, pos);
  }

private:
  struct Node {
    Node(int value) : value(value) {}

    Node *left = nullptr;

    Node *right = nullptr;

    int value;

    int height = 1;

    int nodes = 1;
  };

  Node* insert_element(Node *node, int value, int &pos) {
    if (node == nullptr) {
		  return new Node(value);
    }

    ++node->nodes;

    if (cmp(value, node->value)) {
    	pos += get_nodes(node->right) + 1;
    	node->left = insert_element(node->left, value, pos);
    } else {
      node->right = insert_element(node->right, value, pos);
    }

    return balance(node);
  }

  Node* remove_element(Node *node, int pos) {
    if (node == nullptr) {
      return nullptr;
    }
    if (pos >= node->nodes) {
      return node;
    }

    int curr = 0;
    std::stack<Node *> nodes;

    while (true) {
      int nodes_right = get_nodes(node->right);

      if (pos - curr > nodes_right) {
        nodes.push(node);
        node = node->left;
        curr += nodes_right + 1;
      } else if (pos - curr < nodes_right) {
        if (node->right == nullptr) {
          break;
        }

        nodes.push(node);
        node = node->right;
      } else {
        Node *left = node->left;
        Node *right = node->right;
        int value = node->value;

        delete node;

        if (right == nullptr) {
          if (left != nullptr) {
            node = left;
            break;
          }
          if (nodes.empty()) {
            return nullptr;
          }

          node = nodes.top();
          nodes.pop();

          if (cmp(value, node->value)) {
            node->left = nullptr;
          } else {
            node->right = nullptr;
          }

          --node->nodes;
        } else {
          if (get_balance_factor(node) >= 0) {
            Node *min = nullptr;
            Node *right_sub_tree_root = find_and_remove_min(right, &min);

            min->right = right_sub_tree_root;
            min->left = left;

            fix_nodes(min);
            node = balance(min);
          } else {
            Node *max = nullptr;
            Node *left_sub_tree_root = find_and_remove_max(left, &max);

            max->left = left_sub_tree_root;
            max->right = right;

            fix_nodes(max);
            node = balance(max);
          }
        }

        break;
      }
    }

    while (!nodes.empty()) {
      Node *new_node = nodes.top();
      --new_node->nodes;

      if (cmp(node->value, new_node->value)) {
        new_node->left = node;
      } else {
        new_node->right = node;
      }

      node = balance(new_node);
      nodes.pop();
    }

    return node;
  }

  int get_height(Node *node) {
	  return (node == nullptr) ? 0 : node->height;
  }

  int get_nodes(Node *node) {
    return (node == nullptr) ? 0 : node->nodes;
  }

  int get_balance_factor(Node *node) {
    return get_height(node->right) - get_height(node->left);
  }

  void fix_height(Node *node) {
    int height_left = get_height(node->left);
    int height_right = get_height(node->right);

    node->height = (height_left > height_right) ? height_left + 1 : height_right + 1;
  }

  void fix_nodes(Node *node) {
    int nodes_left = get_nodes(node->left);
    int nodes_right = get_nodes(node->right);

    node->nodes = nodes_left + nodes_right + 1;
  }

  Node* rotate_right(Node *node) {
    Node *new_node = node->left;

    node->left = new_node->right;
    new_node->right = node;

    fix_nodes(node);
    fix_nodes(new_node);

    fix_height(node);
    fix_height(new_node);

    return new_node;
  }

  Node* rotate_left(Node *node) {
    Node *new_node = node->right;

    node->right = new_node->left;
    new_node->left = node;

    fix_nodes(node);
    fix_nodes(new_node);

    fix_height(node);
    fix_height(new_node);

    return new_node;
  }

  Node* balance(Node *node) {
    fix_height(node);

    if (get_balance_factor(node) == -2) {
      if (get_balance_factor(node->left) > 0) {
        node->left = rotate_left(node->left);
      }

      return rotate_right(node);
    } else if (get_balance_factor(node) == 2) {
      if (get_balance_factor(node->right) < 0) {
        node->right = rotate_right(node->right);
      }

      return rotate_left(node);
    }

    return node;
  }

  Node* find_and_remove_max(Node *node, Node **max) {
    if (node->right == nullptr) {
      *max = node;
      return node->left;
    }

    node->right = find_and_remove_max(node->right, max);
    --node->nodes;

    return balance(node);
  }

  Node* find_and_remove_min(Node *node, Node **min) {
    if (node->left == nullptr) {
      *min = node;
      return node->right;
    }

    node->left = find_and_remove_min(node->left, min);
    --node->nodes;

    return balance(node);
  }

  void clear(Node *node) {
    if (node == nullptr) {
      return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
  }

  Node* root = nullptr;

  bool (*cmp)(int n1, int n2);
};

bool cmp(int n1, int n2) {
  return n1 < n2;
}

int main() {
	size_t count;
	std::cin >> count;

	Tree tree(cmp);
	std::vector<int> positions;

	int type, value;

	for (size_t i = 0; i < count; ++i) {
		std::cin >> type >> value;

		if (type == 1) {
			int pos = 0;
			tree.insert(value, pos);
			positions.push_back(pos);
		} else if (type == 2) {
			tree.remove(value);
		}
	}

	for (size_t i = 0; i < positions.size(); ++i) {
		std::cout << positions[i] << std::endl;
	}

	return 0;
}
