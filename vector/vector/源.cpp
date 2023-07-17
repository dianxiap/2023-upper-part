#define _CRT_SECURE_NO_WARNINGS 1
#include "vecror.h"
using namespace std;
//void test1()
//{
//	dianxia::vector<int> v1;
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//
//	for (auto e : v1)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	for (size_t i = 0; i < v1.size(); i++)
//	{
//		v1[i]++;
//	}
//	for (auto e : v1)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}

void test2()
{
	dianxia::vector<int> v(10,1);
	dianxia::vector<string> v1(10, "1111");
	dianxia::vector<int> v2(10, 1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl; 
	dianxia::vector<int> v3(v.begin(), v.end());
	for (auto e : v3)
	{
		cout << e << " ";
	}
	cout << endl;
	string str("hello world");
	dianxia::vector<char> v4(str.begin(), str.end());
	for (auto e : v4)
	{
		cout << e << " ";
	}
	cout << endl;
	int a[] = { 16,2,77,29 };
	dianxia::vector<int> v5(a, a + 4);
	for (auto e : v5)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	test2();
}