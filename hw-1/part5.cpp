/*
* Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием.
* Решение должно поддерживать передачу функции сравнения снаружи.
* Общее время работы алгоритма O(n log n).

* На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri).
* Найти длину окрашенной части числовой прямой.
*/

#include <iostream>

struct Point
{
  int x;
  bool is_begin;
};

bool cmp(Point p1, Point p2)
{
  return p1.x > p2.x;
}

Point *merge_sort(Point *up, Point *down, size_t begin, size_t end, bool (*cmp)(Point p1, Point p2))
{
  if (up == nullptr || down == nullptr || cmp == nullptr)
  {
    return nullptr;
  }

  if (begin == end)
  {
    down[begin] = up[begin];
    return down;
  }

  size_t left = begin, middle = (begin + end) >> 1, right = middle + 1;

  Point *left_buffer = merge_sort(up, down, begin, middle, cmp);
  Point *right_buffer = merge_sort(up, down, middle + 1, end, cmp);

  Point *target = left_buffer == up ? down : up;

  for (size_t i = begin; i <= end; ++i)
  {
    if (left <= middle && right <= end)
    {
      target[i] = cmp(right_buffer[right], left_buffer[left]) ? left_buffer[left++] : right_buffer[right++];
    }
    else
    {
      target[i] = (left <= middle) ? left_buffer[left++] : right_buffer[right++];
    }
  }

  return target;
}

size_t find_colored_part_len(Point *points, size_t count)
{
  if (points == nullptr || count == 0)
  {
    return 0;
  }

  size_t depth = 0, res = 0;

  for (size_t i = 0; i + 1 < count; ++i)
  {
    depth += points[i].is_begin ? 1 : -1;

    if (depth > 0)
    {
      res += points[i + 1].x - points[i].x;
    }
  }

  return res;
}

int main()
{
  size_t count;
  std::cin >> count;

  size_t len = count << 1;

  Point *points = new Point[len];
  if (points == nullptr)
  {
    return 1;
  }

  int begin, end;

  for (size_t i = 0, j = 0; i < count; ++i, ++j)
  {
    std::cin >> begin >> end;

    points[j] = Point({begin, true});
    points[++j] = Point({end, false});
  }

  Point *new_points = new Point[len];
  if (new_points == nullptr)
  {
    return 1;
  }

  Point *sorted_points = merge_sort(points, new_points, 0, len - 1, cmp);

  if (sorted_points == points)
  {
    delete[] new_points;
  }
  else
  {
    delete[] points;
  }

  std::cout << find_colored_part_len(sorted_points, len) << std::endl;

  delete[] sorted_points;

  return 0;
}
