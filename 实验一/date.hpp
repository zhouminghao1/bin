#ifndef DATE_HPP_
#define DATE_HPP_
#include <iostream>

class Date
{
private:
  int year;
  int month;
  int day;

  //是否为闰年
  static bool isLeapYear(int y)
  {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
  }
  
public:
  //构造函数
  Date();
  Date(int y, int m, int d);
  Date(int num);//给定一个数字以计算日期

  // 获取年
  int getYear() const { return year; }

  // 获取月
  int getMonth() const { return month; }

  // 获取日
  int getDay() const { return day; }

  // 计算两个日期之间的天数
  int daysSince1970(Date date) const;

  //增加天数
  void addDays(int num);

  // 打印日期
  void printDate() const;
};



#endif