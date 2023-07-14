#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
typedef long long LL;

const int N = 30;

LL  n;
LL len,a[N], dp[N][N];

LL dfs(int pos, int pre, int limit)
{
	if (!pos)return 1;
	if (!limit && dp[pos][pre] != -1)return dp[pos][pre];

	LL res = 0, up = limit ? a[pos] : 9;

	for (int i = 0; i <= up; i++)
	{
		if (pre == 4 && i == 9)continue;
		res += dfs(pos - 1, i, limit && i == up);
	}
	return limit ? res : dp[pos][pre] = res;
}

LL cal(LL x)
{
	len = 0;
	memset(dp, -1, sizeof dp);
	while (x)a[++len] = x % 10, x /= 10;
	return dfs(len, 0, 1);
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n;
		cout << n-cal(n)+1 << endl;
	}
}