#include <iostream>
using namespace std;
class C
{
  int value;

public:
  C(int v) : value(v) {}
  bool operator<(C &b)
  {
    if (value < b.value)
      return true;

    return false;
  }
  int getValue() { return value; }
};
double getMin(double a, double b)
{
  cout << "getMin(double, double) is invocated!\t";
  if (a < b)
    return a;
  return b;
}
C getMin(C &a, C &b)
{
  cout << "getMin(C&, C&) is invocated!\t";
  if (a < b)
    return a;
  return b;
}
C getMin(C a, C b)
{
  cout << "getMin(C, C) is invocated!\t";
  if (a < b)
    return a;
  return b;
}
int main()
{
  C c1(-9), c2(90);
  cout << getMin(10, 99) << endl;
  cout << getMin(1.2, 2.3) << endl;
  cout << getMin(10, 2.3) << endl;
  cout << getMin(c1, 2).getValue() << endl;
  return 0;
}