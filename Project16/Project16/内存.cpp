#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;


class A
{
public:
	A()
	{
		cout << "A()" << endl;

	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};
int main()
{
	int* p1 = new int;
	int* p2 = new int(10);
	cout << *p2 << endl;
	int* p3 = new int[10];

	delete p1;
	delete p2;
	delete[] p3;

	A* p5 = new A;
	delete p5;
}