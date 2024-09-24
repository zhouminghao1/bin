#include "integer.h"
#include <iostream>

Integer::Integer(const Integer &rhs)
{
  value = rhs.value;
}

Integer& Integer::operator=(const Integer &rhs)
{
  value = rhs.value;
  return *this;
}

Integer& Integer::operator=(int rhs)
{
  value = rhs;
  return *this;
}

std::string Integer::to_string() const
{
  return std::to_string(value);
}

int Integer::intValue() const{
  return value;
}

Integer::operator int() const
{
  return value;
}

Integer::operator double() const{
  return static_cast<double>(value);
}

Integer::operator char() const{
  return static_cast<char>(value);
}

int Integer::cmp(const Integer &rhs)
{
  int num = value - rhs.value;
  if(num > 0)
    return 1;
  else if(num < 0)
    return -1;
  else
    return 0;
}

bool Integer::operator==(const Integer &rhs)
{
  return value == rhs.value;
}

bool Integer::operator!=(const Integer &rhs)
{
  return value != rhs.value;
}

bool Integer::operator<(const Integer &rhs)
{
  return value < rhs.value;
}

bool Integer::operator<=(const Integer &rhs)
{
  return value <= rhs.value;
}

bool Integer::operator>(const Integer &rhs)
{
  return value > rhs.value;
}

bool Integer::operator>=(const Integer &rhs)
{
  return value >= rhs.value;
}

int Integer::parse(const char *c_str)
{
  return std::stoi(c_str);
}

Integer Integer::operator+()
{
  return *this;
}

Integer Integer::operator-()
{
  return Integer(-value);
}

Integer Integer::operator++()
{
  return Integer(++value);
}

Integer Integer::operator--()
{
  return Integer(--value);
}

Integer &Integer::operator+=(const Integer &rhs)
{
  value += rhs.value;
  return *this;
}

Integer &Integer::operator-=(const Integer &rhs)
{
  value -= rhs.value;
  return *this;
}

Integer &Integer::operator*=(const Integer &rhs)
{
  value *= rhs.value;
  return *this;
}

Integer &Integer::operator/=(const Integer &rhs)
{
  value /= rhs.value;
  return *this;
}

Integer operator+(const Integer &Left, const Integer &Right)
{
  return Integer(Left.intValue() + Right.intValue());
}

Integer operator+(const Integer &Left, int Right)
{
  return Integer(Left.intValue() + Right);
} 

Integer operator+(int Left, const Integer &Right)
{
  return Integer(Left + Right.intValue());
}

Integer operator-(const Integer &Left, const Integer &Right)
{
  return Integer(Left.intValue() - Right.intValue());
}

Integer operator-(const Integer &Left, int Right)
{
  return Integer(Left.intValue() - Right);
}

Integer operator-(int Left, const Integer &Right)
{
  return Integer(Left - Right.intValue());
}

Integer operator*(const Integer &Left, const Integer &Right)
{
  return Integer(Left.intValue() * Right.intValue());
}

Integer operator*(const Integer &Left, int Right)
{
  return Integer(Left.intValue() * Right);
}

Integer operator*(int Left, const Integer &Right)
{
  return Integer(Left * Right.intValue());
}

Integer operator/(const Integer &Left, const Integer &Right)
{
  return Integer(Left.intValue() / Right.intValue());
}

Integer operator/(const Integer &Left, int Right)
{
  return Integer(Left.intValue() / Right);
}

Integer operator/(int Left, const Integer &Right)
{
  return Integer(Left / Right.intValue());
}