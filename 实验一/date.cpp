#include "date.hpp"
#include <iostream>

void Date::printDate() const
{
  std::cout << "Date: " << year << "-" << month << "-" << day << std::endl;
}

Date::Date()
{
  year = 1970;
  month = 1;
  day = 1;
}

Date::Date(int y, int m, int d)
{
  year = y;
  month = m;
  day = d;
}

// 增加天数
void Date::addDays(int num)
{
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (num < 0)
  {
    throw std::invalid_argument("Input days cannot be negative");
  }

  while (num > 0)
  {
    if (isLeapYear(year))
    {
      daysInMonth[1] = 29;
    }
    int daysLeft = daysInMonth[month - 1] - day + 1;
    if (num >= daysLeft)
    {
      num -= daysLeft;
      day = 1;
      month++;
      if (month > 12)
      {
        month = 1;
        year++;
      }
    }
    else
    {
      day += num;
      num = 0;
    }
  }
}

// 给定一个数字以计算日期并输出
Date::Date(int num)
{
  if (num < 0)
  {
    throw std::invalid_argument("Input days cannot be negative");
  }

  year = 1970;
  // 先获得年份
  while (num >= 365)
  {
    if (isLeapYear(year))
    {
      if (num >= 366)
      {
        num -= 366;
        year++;
      }
      else
      {
        break;
      }
    }
    else
    {
      num -= 365;
      year++;
    }
  }

  month = 1;
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isLeapYear(year))
  {
    daysInMonth[1] = 29;
  }
  while (num >= daysInMonth[month - 1])
  {
    num -= daysInMonth[month - 1];
    month++;
  }

  day = num + 1;
}

// 计算两个日期之间的天数
int Date::daysSince1970(Date date) const
{
  int days = 0;
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (date.getYear() < 1970)
  {
    throw std::invalid_argument("Input date cannot be earlier than 1970");
  }
  for (int i = 1970; i < date.getYear(); i++)
  {
    if (isLeapYear(i))
    {
      days += 366;
    }
    else
    {
      days += 365;
    }
  }

  if (isLeapYear(date.getYear()))
  {
    daysInMonth[1] = 29;
  }

  for (int i = 1; i < date.getMonth(); i++)
  {
    days += daysInMonth[i - 1];
  }

  days += date.getDay() - 1;

  return days;
}