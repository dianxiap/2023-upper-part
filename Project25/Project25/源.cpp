#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;

int n, k;
int a[N];
int b[N];
int tmp[N];

void solve()
{
	cin >> n >> k;
	vector<int> a(n), b(n);

	for (auto x : a)cin >> x;
	for (auto x : b)cin >> x;

	vector<int> p(n);
	iota(begin(p), end(p), 0);


}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}