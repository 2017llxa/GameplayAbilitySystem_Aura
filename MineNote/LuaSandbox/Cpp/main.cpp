#include <iostream>
#include "main.h"

using namespace std;

int main()
{
    //int value = 10;
    //byValue(value);//10       值传递 不能修改原变量
    //byReference(value);//20   引用传递 可以修改原变量
    //byPointer(&value);//20    指针传递 可以修改原变量 需要允许“没有对象”时，常用指针
    //cout << value << endl; 

  //浅拷贝
  // int *a = new int(10);
  // int *b = a;
  // cout << *a << endl;
  // cout << *b << endl;

  // *b = 20;
  // cout << *a << endl; 20
  // cout << *b << endl; 20

  //深拷贝
  // int *a = new int(10);
  // int *b = new int(*a);

  // *b = 20;
  // cout << *a << endl; 10
  // cout << *b << endl; 10

  int a = 1;
  int b = 1;
  cout << ++a <<endl;
  cout << b++ <<endl;

 //system("pause");
  return 0;
}
