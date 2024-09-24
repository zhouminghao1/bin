#include "date.hpp"
#include "date.cpp"

int main()
{
  int num;
  std::cout << " Please input a number of date( num >= 0 ): " << std::endl;
  std::cin >> num;
  Date date(num);
  date.printDate();
  Date date1(2022, 2, 9);
  date1.addDays(40);
  date1.printDate();
  std::cout << date.daysSince1970(date1) << std::endl;
  return 0;
}