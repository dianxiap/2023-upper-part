#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
using namespace std;
const int N = 100010;

typedef long long LL;
LL n;
int h[N], ne[N], e[N], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool st[N];
LL m;
void dfs(int v, bool color)
{
	st[v] = true;
	if (color)m++;
	for (int i = h[v]; i != -1; i = ne[i])
	{
		int j = e[i];
		if (!st[j])dfs(j, !color);
	}
}
int main()
{
	cin >> n;
	memset(h, -1, sizeof h);

	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		add(x, y), add(y, x);
	}
	dfs(1, true);
	cout << m * (n - m) - (n - 1);
}
