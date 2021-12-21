/*
* Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
* Формат входных данных.
* В первой строке количество команд n. n ≤ 1000000.
* Каждая команда задаётся как 2 целых числа: a b.
* a = 1 - push front
* a = 2 - pop front
* a = 3 - push back
* a = 4 - pop back
* Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
* Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
* Если дана команда pop*, то число b - ожидаемое значение.
* Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.

* Реализовать очередь с динамическим зацикленным буфером.
*/

#include <iostream>

#define POP_FRONT 2
#define PUSH_BACK 3

class Queue
{
private:
  int *elements;

  size_t size, first, last;

  void expand_size()
  {
    size_t new_size = (size > 0) ? size * 2 : 10;
    int *new_elements = new int[new_size];

    if (first != last)
    {
      size_t j = 0;

      for (size_t i = first; i < size; ++i)
      {
        if (i == last)
        {
          break;
        }

        new_elements[j++] = elements[i];

        if (i == size - 1)
        {
          i = -1;
        }
      }

      first = 0;
      last = j;
    }

    if (elements != nullptr)
    {
      delete[] elements;
    }

    elements = new_elements;
    size = new_size;
  }

public:
  Queue()
  {
    elements = nullptr;

    size = 0;
    first = 0;
    last = 0;

    expand_size();
  }

  ~Queue()
  {
    if (elements != nullptr)
    {
      delete[] elements;
    }
  }

  void push(int element)
  {
    // If not enough memory to push one more element
    if ((last + 1) % size == first)
    {
      expand_size();
    }

    elements[(last) % size] = element;
    last = (last + 1) % size;
  }

  int pop()
  {
    if (first == last)
    {
      return -1;
    }

    int element = elements[first];

    if (first == size - 1)
    {
      first = 0;
    }
    else
    {
      ++first;
    }

    return element;
  }

  bool empty()
  {
    return first == last;
  }
};

int main()
{
  Queue queue;

  size_t count;
  std::cin >> count;

  bool res = true;

  size_t command;
  int value;

  for (size_t i = 0; i < count; ++i)
  {
    std::cin >> command >> value;

    if (command == POP_FRONT)
    {
      if (queue.empty())
      {
        value = -1;
      }

      res = queue.pop() == value;
    }
    else if (command == PUSH_BACK)
    {
      queue.push(value);
    }
    else
    {
      return 1;
    }

    if (!res)
    {
      break;
    }
  }

  std::cout << (res ? "YES" : "NO") << std::endl;

  return 0;
}
