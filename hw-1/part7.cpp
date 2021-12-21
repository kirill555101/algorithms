/*
* Дан массив неотрицательных целых 64-разрядных чисел.
* Количество чисел не больше 10e6. Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>

inline int bit(unsigned long long num, int pos)
{
  return (num >> pos) & 1;
}

void binary_quick_sort(unsigned long long *arr, int left, int right, int pos)
{
  if (arr == nullptr || right <= left)
  {
    return;
  }

  int i = left, j = right;

  while (i != j)
  {
    while (bit(arr[i], pos) == 0 && (i < j))
    {
      ++i;
    }

    while (bit(arr[j], pos) == 1 && (j > i))
    {
      --j;
    }

    auto temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  if (bit(arr[right], pos) == 0)
  {
    ++j;
  }

  binary_quick_sort(arr, left, j - 1, pos - 1);
  binary_quick_sort(arr, j, right, pos - 1);
}

int main()
{
  size_t len;
  std::cin >> len;

  auto arr = new unsigned long long[len];
  if (arr == nullptr)
  {
    return 1;
  }

  for (size_t i = 0; i < len; ++i)
  {
    std::cin >> arr[i];
  }

  binary_quick_sort(arr, 0, len - 1, 63);

  for (size_t i = 0; i < len; ++i)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  delete[] arr;

  return 0;
}
