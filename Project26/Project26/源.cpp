#define _CRT_SECURE_NO_WARNINGS 1
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;

int n, m;
int a[N], b[N], c[N];
int res[N];

void solve()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)c[i] = i;
	for (int i = 1; i <= n; i++)cin >> a[i];
	for (int i = 1; i <= n; i++)cin >> b[i];

	sort(c + 1, c + n + 1, [&](int x, int y)
		{
			return a[x] < a[y];
		}
	);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)res[c[i]] = b[i];
	for (int i = 1; i <= n; i++)cout << res[i] << ' ';
	cout << endl;

}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}