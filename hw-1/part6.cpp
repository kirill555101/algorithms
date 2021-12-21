/*
* Дано множество целых чисел из [0..10^9] размера n.
* Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
* 10%  перцентиль
* медиана
* 90%  перцентиль

* Реализуйте стратегию выбора опорного элемента “случайный элемент”.
* Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>

size_t partition(int *arr, int begin, int end, bool (*cmp)(int e1, int e2))
{
  if (arr == nullptr || cmp == nullptr)
  {
    return 0;
  }

  if (begin != end)
  {
    const size_t index = begin + rand() % (end - begin);

    int temp = arr[index];
    arr[index] = arr[begin];
    arr[begin] = temp;
  }

  const int elem = arr[begin];
  size_t i = end + 1;

  for (int j = end; j >= begin; --j)
  {
    // If arr[j] >= elem
    if (cmp(arr[j], elem) || !(cmp(arr[j], elem) || cmp(elem, arr[j])))
    {
      --i;

      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }

  return i;
}

size_t find_statistic(int *arr, size_t len, bool (*cmp)(int e1, int e2), size_t index)
{
  if (arr == nullptr || len == 0 || index >= len || cmp == nullptr)
  {
    return 0;
  }

  srand(time(NULL));

  int pos = 0, begin = 0, end = len - 1;

  while (pos != index)
  {
    pos = partition(arr, begin, end, cmp);

    if (pos < index)
    {
      begin = pos + 1;
    }
    else if (pos > index)
    {
      end = pos - 1;
    }
  }

  return arr[index];
}

bool cmp(int e1, int e2)
{
  return e1 > e2;
}

int main()
{
  size_t len;
  std::cin >> len;

  int *arr = new int[len];
  if (arr == nullptr)
  {
    return 1;
  }

  for (size_t i = 0; i < len; ++i)
  {
    std::cin >> arr[i];
  }

  std::cout << find_statistic(arr, len, cmp, 0.1 * len) << std::endl; // 10% percentile
  std::cout << find_statistic(arr, len, cmp, 0.5 * len) << std::endl; // Median
  std::cout << find_statistic(arr, len, cmp, 0.9 * len) << std::endl; // 90% percentile

  delete[] arr;

  return 0;
}
