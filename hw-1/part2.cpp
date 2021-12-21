/*
* Дан массив целых чисел А[0..n-1].
* Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
* Найти m за O(log m).
*/

#include <iostream>

size_t binary_search(int *arr, size_t begin, size_t end)
{
  size_t middle = 0;

  while (begin != end)
  {
    middle = (begin + end) >> 1;

    // If we found index
    if (arr[middle] > arr[middle + 1] && arr[middle] > arr[middle - 1])
    {
      break;
    }

    if (arr[middle] > arr[middle + 1])
    {
      end = middle;
    }
    else
    {
      begin = middle + 1;
    }
  }

  return middle;
}

size_t find_index(int *arr, size_t len)
{
  if (arr == nullptr || len == 0)
  {
    return 0;
  }

  const size_t end = len - 1;
  size_t step = 1;

  // Check if the array is constantly increasing or decreasing
  if (arr[0] > arr[1])
  {
    return 0;
  }
  else if (arr[end - 1] < arr[end])
  {
    return end;
  }

  while (step < end)
  {
    if (arr[step - 1] > arr[step]) // If we crossed over index
    {
      return binary_search(arr, step >> 1, step);
    }
    else if (arr[step] > arr[step + 1]) // If we found index
    {
      return step;
    }

    step <<= 1;
  }

  return binary_search(arr, step >> 1, end);
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

  std::cout << find_index(arr, len) << std::endl;

  delete[] arr;

  return 0;
}
