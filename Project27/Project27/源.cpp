#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int N = 1010, M = 20010;

int n, m;
int h[N], hs[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int in_ssc[N], id[N], sz[N],ssc_cnt;
stack<int> q;
int p[N], newp[N],f[N];

void add(int h[], int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++timestamp;
	q.push(u), in_ssc[u] = true;

	for (int i = h[u]; i != -1; i = ne[i])
	{
		int j = e[i];
		if (!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u], low[j]);
		}
		else if (in_ssc[j])
			low[u] = min(low[u], dfn[j]);
	}
	if (low[u] == dfn[u])
	{
		int y;
		++ssc_cnt;
		do {
			y = q.top();
			q.pop();
			in_ssc[y] = false;
			id[y] = ssc_cnt;
			newp[ssc_cnt] += p[y];
		} while (y != u);
	}
}

int main()
{
	cin >> n >> m;
	memset(h, -1, sizeof h);
	memset(hs, -1, sizeof hs);

	for (int i = 1; i <= n; i++)cin >> p[i];

	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		add(h,a, b);
	}

	for (int i = 1; i <= n; i++)
	{
		if (!dfn[i])
			tarjan(i);
	}

	for(int u=1;u<=n;u++)
		for (int i = h[u]; i != -1; i = ne[i])
		{
			int j = e[i];
			int a = id[u];
			int b = id[j];
			if (a != b)
				add(hs, a, b);
		}
	for (int u = ssc_cnt; u; u--)
	{
		if (!f[u])f[u] = newp[u];

		for (int i = h[u]; i != -1; i = ne[i])
		{
			int j = e[i];
			f[j] = max(f[j], f[u] + newp[j]);
		}
	}

	int res = 0;
	for (int i = 1; i <= ssc_cnt; i++)res = max(res, f[i]);

	cout << res;
}