#pragma once
#include <string>
#include <iostream>

class Integer
{
private:
  int value;

public:
  // 构造函数
  Integer(int v = 0) : value(v) {}
  Integer(const char *c_str)
  {
    value = std::stoi(c_str);
  }
  Integer(const std::string &str)
  {
    value = std::stoi(str);
  }

  // 复制操作函数
  Integer(const Integer &rhs);
  Integer& operator=(const Integer &rhs);
  Integer& operator=(int rhs);

  // 类型转换
  std::string to_string() const;
  int intValue() const;
  operator int() const;
  operator double() const;
  operator char() const;

  // 关系运算符
  int cmp(const Integer &rhs);
  bool operator==(const Integer &rhs);
  bool operator!=(const Integer &rhs);
  bool operator<(const Integer &rhs);
  bool operator<=(const Integer &rhs);
  bool operator>(const Integer &rhs);
  bool operator>=(const Integer &rhs);

  //字符串转换为整数
  static int parse(const char *c_str);
  static int parse(const std::string &str)
  {
    return parse(str.c_str());
  }

  //算术运算
  Integer operator+();
  Integer operator-();
  Integer operator++();
  Integer operator--();
  Integer &operator+=(const Integer &rhs);
  Integer &operator-=(const Integer &rhs);
  Integer &operator*=(const Integer &rhs);
  Integer &operator/=(const Integer &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Integer &obj);
  friend std::istream &operator>>(std::istream &is, Integer &obj);
};



// 二元运算符+、-、*、/
Integer operator+(const Integer &Left, const Integer &Right);
Integer operator+(const Integer &Left, int Right);
Integer operator+(int Left, const Integer &Right);

Integer operator-(const Integer &Left, const Integer &Right);
Integer operator-(const Integer &Left, int Right);
Integer operator-(int Left, const Integer &Right);

Integer operator*(const Integer &Left, const Integer &Right);
Integer operator*(const Integer &Left, int Right);
Integer operator*(int Left, const Integer &Right);

Integer operator/(const Integer &Left, const Integer &Right);
Integer operator/(const Integer &Left, int Right);
Integer operator/(int Left, const Integer &Right);

// 流运算符<<和>>
std::ostream &operator<<(std::ostream &os, const Integer &obj)
{
  os << obj.intValue();
  return os;
}

std::istream &operator>>(std::istream &is, const Integer &obj)
{
  is >> obj.intValue();
  return is;
}
