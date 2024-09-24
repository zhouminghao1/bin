#include<iostream>
using namespace std;

int main(){
  int num=0;
  while(1){
    if(num<0){
      cout<<num<<endl;
      num--;
      break;
    }
    num++;
  }
  cout<<num;
}