#include<iostream>
using namespace std;

class Base{
  public:
  void print(){
    cout << "1 ";
  }
  virtual void speak(){
    cout << "2 ";
  }
};

class Child: public Base{
  public:
    void print(){
      cout << "3 ";
    }
    void speak(){
      cout << "4 ";
    }
};

int main(){
  Base objB;
  Child objC;

  objB.print();objB.speak();
  objC.print();objC.speak();

  Base* ptr = &objB;
  ptr->print();ptr->speak();

  ptr = &objC;
  ptr->print();ptr->speak();
}
