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
	A* p4 = (A*)malloc(sizeof(A));
	free(p4);
	A* p5 = new A;
	delete p5;
}