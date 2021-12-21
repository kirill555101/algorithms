/*
* Если в числе содержится только один бит со значением 1, записать в выходной поток OK. Иначе записать FAIL
*/

#include <iostream>

size_t find_number_of_bits(size_t num)
{
  size_t count = 0;

  while (num)
  {
    if ((num & 1) == 1)
    {
      ++count;
    }
    if (count > 1)
    {
      break;
    }

    num >>= 1;
  }

  return count;
}

int main()
{
  size_t num;
  std::cin >> num;

  std::cout << (find_number_of_bits(num) == 1 ? "OK" : "FAIL") << std::endl;

  return 0;
}
