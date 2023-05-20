#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
typedef pair<int, int> PII;

const int N = 500010, M = N << 1;
int h[N], e[M], ne[M], w[M], idx;
int n, m, s;
int p[N];
bool st[N];
int lca[N];
vector<PII> quary[N];

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int find(int x)
{
	if (p[x] != x)p[x] = find(p[x]);
	return p[x];
}

void tarjan(int u)
{
	st[u] = true;
	for (int i = h[u]; i != -1; i = ne[i])
	{
		int j = e[i];
		if (!st[j])
		{
			tarjan(j);
			p[j] = u;
		}
	}
	for (auto q : quary[u])
	{
		int v = q.first, id = q.second;
		if (st[v])lca[id] = find(v);
	}
}


int main()
{
	memset(h, -1, sizeof h);
	cin >> n >> m >> s;
	int a, b;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b;
		add(a, b), add(b, a);
	}

	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		quary[a].push_back({ b,i });
		quary[b].push_back({ a,i });
	}
	for (int i = 1; i <= n; i++)p[i] = i;
	tarjan(s);
	for (int i = 1; i <= m; i++)cout << lca[i] << endl;
}