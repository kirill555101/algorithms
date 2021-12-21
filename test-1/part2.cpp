/*
  ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!

  Дана последовательность, состоящая из символов '(' и ')'.
  Требуется определить, является ли данная последовательность правильной скобочной последовательностью.
  Длина исходной последовательности ≤ 800000.
*/

#include <iostream>

class Stack {
private:
  int* arr;

  size_t current_size;

public:
  Stack(size_t len) {
    current_size = 0;
    arr = new int[len];
  }

  ~Stack() {
    delete[] arr;
  }

  void push() {
    arr[current_size++] = 1;
  }

  void pop() {
    if (current_size > 0) {
      arr[current_size--] = 0;
    }
  }

  size_t get_size() {
    return current_size;
  }
};

int main() {
  std::string str;
  std::cin >> str;

  Stack stack(str.length());
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '(') {
      stack.push();
    }
    else if (str[i] == ')') {
      stack.pop();
    }
  }

  std::cout << (stack.get_size() == 0 ? "YES" : "NO") << std::endl;
}
