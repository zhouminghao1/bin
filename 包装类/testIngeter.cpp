#include"integer.h"
#include"integer.cpp"
#include <iostream>

int main(){
  Integer a(10);
  Integer b(20);
  Integer c = a + b;
  std::cout << c.intValue() << std::endl;
  return 0;
}