#include<iostream>
using namespace std;

int main(){
  enum m_color {red, bule, black, yellow};
  cout << "  Size of fundamental types :\n"; 
	cout << "------------------------------------------\n"; 
    cout << " The sizeof(char) is :          " << sizeof(char) << " bytes \n" ; 
    cout << " The sizeof(short) is :         " << sizeof(short) << " bytes \n" ; 
    cout << " The sizeof(int) is :           " << sizeof(int) << " bytes \n" ; 
    cout << " The sizeof(long) is :          " << sizeof(long) << " bytes \n" ; 
    cout << " The sizeof(long long) is :     " << sizeof(long long) << " bytes \n"; 
    cout << " The sizeof(float) is :         " << sizeof(float) << " bytes \n" ; 
    cout << " The sizeof(double) is :        " << sizeof(double) << " bytes \n"; 
    cout << " The sizeof(long double) is :   " << sizeof(long double) << " bytes \n"; 
    cout << " The sizeof(bool) is :          " << sizeof(bool) << " bytes \n"; 
  cout << "  Size of pointer types :\n"; 
	cout << "------------------------------------------\n";
    cout << " The sizeof(int *) is :         " << sizeof(int *) << " bytes \n"; 
    cout << " The sizeof(char *) is :        " << sizeof(char *) << " bytes \n"; 
    cout << " The sizeof(long *) is :        " << sizeof(long *) << " bytes \n"; 
  cout << "  Size of enumerations  :\n"; 
	cout << "------------------------------------------\n";
    cout << " The sizeof(m_color) is :       " << sizeof(m_color) << " bytes \n"; 
    return 0; 
}