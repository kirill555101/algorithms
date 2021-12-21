/*
  Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
  Хранимые строки непустые и состоят из строчных латинских букв.

  Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.

  Начальный размер таблицы должен быть равным 8-ми.
  Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.

  Структура данных должна поддерживать операции добавления строки в множество,
  удаления строки из множества и проверки принадлежности данной строки множеству.

  Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
  g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/

#include <iostream>

class HashTable {
public:
  HashTable() {
    nodes = new Node*[buffer_size];

    for (size_t i = 0; i < buffer_size; ++i) {
      nodes[i] = nullptr;
    }
  }

  ~HashTable() {
    for (size_t i = 0; i < buffer_size; ++i) {
      if (nodes[i] == nullptr) {
        continue;
      }

      delete nodes[i];
    }

    delete[] nodes;
  }

  bool insert(std::string key) {
    if (contains(key)) {
      return false;
    }

    if (3 * buffer_size <= 4 * (size + 1)) {
      rehash();
    }

    size_t hash = get_hash(key);
    size_t i = 0;

    while (i < buffer_size) {
      if (nodes[hash] == nullptr) {
        nodes[hash] = new Node;
        nodes[hash]->data = key;
        ++size;
        return true;
      }
      if (nodes[hash]->deleted) {
        nodes[hash]->data = key;
        nodes[hash]->deleted = false;
        ++size;
        return true;
      }

      ++i;
      hash = (hash + i) % buffer_size;
    }

    return false;
  };

  bool remove(std::string key) {
    if (!contains(key)) {
      return false;
    }

    size_t hash = get_hash(key);
    size_t i = 0;

    while (i < buffer_size) {
      if (!nodes[hash]->deleted && nodes[hash]->data.compare(key) == 0) {
        nodes[hash]->deleted = true;
        --size;
        return true;
      }

      ++i;
      hash = (hash + i) % buffer_size;
    }

    return false;
  }

  bool contains(std::string key) const {
    size_t hash = get_hash(key);
    size_t i = 0;

    while (nodes[hash] != nullptr && i < buffer_size) {
      if (!nodes[hash]->deleted && nodes[hash]->data.compare(key) == 0) {
        return true;
      }

      ++i;
      hash = (hash + i) % buffer_size;
    }

    return false;
  }

private:
  struct Node {
    std::string data;

    bool deleted = false;
  };

  void rehash() {
    Node **tmp = nodes;
    size_t tmp_buffer_size = buffer_size;

    buffer_size *= 2;
    nodes = new Node*[buffer_size];
    size = 0;

    for (size_t i = 0; i < buffer_size; ++i) {
      nodes[i] = nullptr;
    }

    for (size_t i = 0; i < tmp_buffer_size; ++i) {
      if (tmp[i] == nullptr) {
        continue;
      }
      if (!tmp[i]->deleted) {
        insert(tmp[i]->data);
        ++size;
      }

      delete tmp[i];
    }

    delete[] tmp;
  }

  size_t get_hash(std::string key) const {
    size_t hash = 0;

    for (size_t i = 0; i < key.length(); ++i) {
      hash = (hash + 127 * key[i]) % buffer_size;
    }

    return hash;
  };

  size_t buffer_size = 8;

  size_t size = 0;

  Node **nodes = nullptr;
};

int main() {
  HashTable hash_table;

  while(!std::cin.eof()) {
    char command;
    std::string str;

    std::cin >> command;
    std::cin >> str;

    if (str.empty()) {
      break;
    }

    switch (command) {
      case '+':
        std::cout << (hash_table.insert(str) ? "OK" : "FAIL") << std::endl;
        break;

      case '-':
        std::cout << (hash_table.remove(str) ? "OK" : "FAIL") << std::endl;
        break;

      case '?':
        std::cout << (hash_table.contains(str) ? "OK" : "FAIL") << std::endl;
        break;

      default:
        break;
    }
  }

  return 0;
}
