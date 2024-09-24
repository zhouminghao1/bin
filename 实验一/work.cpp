#include <iostream>
#include <string>
using namespace std;

class Animal
{
protected:
  string name;

public:
  Animal(const char *nm = "A") : name("A")
  {
    if (nm != NULL)
      name = nm;
  }
  Animal(const string &nm) : name(nm) {}

  virtual void iam() { cout << "Animal " << name << endl; }
  void hello() { cout << "Animal::hello from " << name << endl; }
  void common() { cout << "Animal::common" << endl; }
};

class Dog : public Animal
{
public:
  Dog(const char *nm = "Dog") : Animal(nm) {}
  void iam() override { cout << "Dog " << name << endl; }
  void hello() { cout << "Dog::hello from " << name << endl; }
};

class Cat : public Animal
{
public:
  Cat(const char *nm = "Cat") : Animal(nm) {}
  void iam() override { cout << "Cat " << name << endl; }
  void hello() { cout << "Cat::hello from " << name << endl; }
};

class Human : public Animal
{
public:
  Human(const char *nm = "Human") : Animal(nm) {}
  void iam() override { cout << "Human " << name << endl; }
  void hello() { cout << "Human::hello from " << name << endl; }
};

class Boy : public Human
{
public:
  Boy(const char *nm = "Boy") : Human(nm) {}
  void iam() override { cout << "Boy " << name << endl; }
  void hello() { cout << "Boy::hello from " << name << endl; }
};

class Girl : public Human
{
public:
  Girl(const char *nm = "Girl") : Human(nm) {}
  void iam() override { cout << "Girl " << name << endl; }
  void hello() { cout << "Girl::hello from " << name << endl; }
};

void invoke_base(Animal *ptr)
{
  cout << "Function " << __FUNCTION__ << endl;
  ptr->iam();
  ptr->hello();
  ptr->common();
}

void invoke_base(Animal &ref)
{
  cout << "Function " << __FUNCTION__ << endl;
  ref.iam();
  ref.hello();
  ref.common();
}

void invoke_Human(Human &ref)
{
  cout << "Function " << __FUNCTION__ << endl;
  ref.iam();
  ref.hello();
  ref.common();
}

void invoke_Cat(Cat *ptr)
{
  ptr->iam();
  ptr->hello();
  ptr->common();
}
void invoke_Dog (Dog &ref)
{
  ref.iam();
  ref.hello();
  ref.common();
}

int main()
{
  Animal a("A");
  Dog d("Goofy");
  Cat c("Kitty");
  Human h("John");
  Boy b("Tom");
  Girl g("Lucy");
  Animal *ptr = &a;
  Animal &ref = a;

  a.iam();
  a.hello();
  a.common();

  d.iam();
  d.hello();
  d.common();
  invoke_Dog(d);

  c.iam();
  c.hello();
  c.common();
  invoke_Cat(&c);

  h.iam();
  h.hello();
  h.common();

  b.iam();
  b.hello();
  b.common();

  g.iam();
  g.hello();
  g.common();

  ptr->iam();
  ptr->hello();
  ptr->common();

  ref.iam();
  ref.hello();
  ref.common();

  invoke_base(&d);
  invoke_base(d);

  invoke_base(&c);
  invoke_base(c);

  invoke_base(&h);
  invoke_base(h);

  invoke_base(&b);
  invoke_base(b);

  invoke_base(&g);
  invoke_base(g);

  return 0;
}
