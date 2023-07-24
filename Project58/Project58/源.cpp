#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

class A
{
public:
	int* a = new int;
	virtual ~A()
	{
		delete a;
		cout << "~A" << endl;
	}
};

class B : public A
{
	virtual ~B()
	{
		cout << "~B" << endl;
	}
};

int main()
{
	A* ptr = new B;
	int b = 10;
	int c = 20;
	ptr->a = &b;
	ptr->A::a = &c;
	cout << *(ptr->a) << endl;
	cout << *(ptr->A::a) << endl;
	delete ptr;
}