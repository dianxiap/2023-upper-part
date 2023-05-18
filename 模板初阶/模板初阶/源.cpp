#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

template<class T,class Y>
Y Add(T a, Y b)
{
	cout << "Ä£°å" << endl;
	return a + b;
}
int Add(int a, int b)
{
	cout << "·ÇÄ£°å" << endl;
	return a + b;
}

int main()
{
	int a = 10;
	int b = 100;	
	double d = 3.14;

	cout << Add(a, b) << endl;
	cout << Add(a, d) << endl;
}