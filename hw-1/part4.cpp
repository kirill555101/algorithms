/*
* В операционной системе Technux есть планировщик процессов.
* Каждый процесс характеризуется:
* приоритетом P
* временем, которое он уже отработал t
* временем, которое необходимо для завершения работы процесса T
* Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и
* кладет обратно в очередь процессов.
* Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
* Требуется посчитать кол-во переключений процессора.
*/

#include <iostream>

template <typename T>
class Heap
{
private:
  T *elements;

  size_t size = 0;

  bool (*cmp)(T e1, T e2);

  void sift_down(size_t i)
  {
    size_t left, right, j;
    T temp;

    while ((i << 1 + 1) < size)
    {
      left = i << 1 + 1;
      right = i << 1 + 2;

      j = left;

      // If size > right and elements[left] > elements[right]
      if (size > right && cmp(elements[left], elements[right]))
      {
        j = right;
      }

      // If elements[j] >= elements[i]
      if (cmp(elements[j], elements[i]) || !(cmp(elements[j], elements[i]) || cmp(elements[i], elements[j])))
      {
        break;
      }

      temp = elements[i];
      elements[i] = elements[j];
      elements[j] = temp;

      i = j;
    }
  }

public:
  Heap(bool (*cmp)(T e1, T e2), size_t count)
  {
    elements = new T[count];
    this->cmp = cmp;
  }

  ~Heap()
  {
    if (elements != nullptr)
    {
      delete[] elements;
    }
  }

  void add(T element)
  {
    size_t index = size, parent_index = (index - 1) >> 1;
    elements[index] = element;
    T temp;

    while (parent_index >= 0 && index > 0)
    {
      // If elements[index] > elements[parent_index]
      if (cmp(elements[index], elements[parent_index]))
      {
        temp = elements[index];
        elements[index] = elements[parent_index];
        elements[parent_index] = temp;
      }

      index = parent_index;
      parent_index = (index - 1) >> 1;
    }

    ++size;
  }

  size_t get_size()
  {
    return size;
  }

  T extract_min()
  {
    T element = elements[0];

    elements[0] = elements[size - 1];
    --size;
    sift_down(0);

    return element;
  }
};

// The process itself
struct Process
{
  size_t P; // Prioritet
  size_t t; // Worked time
  size_t T; // Required time
};

// Function compares 2 elements and chooses the prioritet one
bool cmp(Process p1, Process p2)
{
  return p1.P * (p1.t + 1) < p2.P * (p2.t + 1);
}

int main()
{
  size_t count;
  std::cin >> count;

  Heap<Process> heap(cmp, count);

  size_t P, T;
  for (size_t i = 0; i < count; ++i)
  {
    std::cin >> P >> T;
    heap.add(Process({P, 0, T}));
  }

  Process process;
  size_t total_count = 0;

  while (heap.get_size())
  {
    process = heap.extract_min();

    process.t += process.P;
    if (process.t < process.T)
    {
      heap.add(process);
    }

    ++total_count;
  }

  std::cout << total_count << std::endl;
}
