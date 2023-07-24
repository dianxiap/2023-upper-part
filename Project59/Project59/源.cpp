#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

class A
{
public:

  void f() { cout << "A::f()" << endl; }

  int a;

};



class B : public A
{
public:

	void f(int a) { cout << "B::f()" << endl; }

	int a;

};



int main()
{
	B b;

	b.A::f();
	return 0;

}