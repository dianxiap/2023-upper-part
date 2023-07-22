#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


template<class T>
struct Less
{
	bool operator()(const T& x, const T& y) const
	{
		return x < y;
	}
};

// 指针版本的特化
template<>
struct Less<int*>
{
	bool operator()(const int* x, const int* y) const
	{
		return *x < *y;
	}
};

int main()
{
	int a1 = 100;
	int a2 = 15;
	int a3 = 56;
	int a4 = 178;
	int a5 = 56;
	int a6 = 98;

	vector<int> v{ a1,a2,a3,a4,a5,a6 };

	sort(v.begin(), v.end(), Less<int>());

	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
	return 0;
}