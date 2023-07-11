#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 15;
typedef long long LL;

LL l, r, dp[N][N];

int len, a[N];

LL dfs(int pos, LL sum, int num, int lead, int limit)
{
	if (!pos)
	{
		if (lead && !num)return 1;
		return sum;
	}

	if (!lead && !limit && dp[pos][sum] != -1)return dp[pos][sum];

	LL res = 0, up = limit ? a[pos] : 9;

	for (int i = 0; i <= up; i++)
	{
		int t = sum;
		if (i == num)
		{
			if (!num)t = sum + (lead == 0);
			else t = sum + 1;
		}
		else t = sum;

		res += dfs(pos - 1, t, num, lead && !i, limit && i == up);
	}
	return limit ? res : (lead ? res : dp[pos][sum] = res);
}

LL cal(LL x, int num)
{
	len = 0;
	memset(dp, -1, sizeof dp);
	while (x)a[++len] = x % 10, x /= 10;
	return dfs(len, 0, num, 1, 1);
}

void solve()
{
	for (int i = 0; i <= 9; i++)
	{
		cout << cal(r, i) - cal(l - 1, i) << ' ';
	}
}

int main()
{
	cin >> l >> r;
	solve();
}