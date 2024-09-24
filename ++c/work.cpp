#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void update(const float& i){

    cout << "call const reference\n";

}

void update(float& i){

    cout << "call nonconst reference\n";

    i+=1;

}

int main() {

    double d=10;     float r = 2;

    update(2.0f);

    update(r);

    update(d);
  cin.get();
  return 0;
}