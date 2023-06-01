#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200010;
typedef long long LL;
int n,k;
LL a[N];
LL s[N];

LL check(LL p)
{
	LL res = 0;
	while (p && p % 10 == 0)
	{
		res++;
		p /= 10;
	}
	return res;
}

void solve()
{
	cin >> n >> k;
	s[0] = 1;
	LL res = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		s[i] = s[i - 1] * a[i];
	}

	for (int i = 1; i <= n; i++)
	{
		int l = i, r = n;
		//最大右端点
		while (l < r)
		{
			int mid = l + r >> 1;
			if (check(s[mid] / s[l - 1])>=k)r = mid;
			else l = mid + 1;
		}
		int ans = l;

		l = i, r = n;
		//最小左端点
		while (l < r)
		{
			int mid = l + r + 1 >> 1;
			if (check(s[mid] / s[l - 1]) <= k)l = mid;
			r = mid - 1;
		}
		if (check(s[ans] / s[l - 1]) == k)
			res += l - ans + 1;
	}
	cout << res << endl;
}
int main()
{
	int  t;
	cin >> t;
	while (t--)
	{
		solve();

	}
}