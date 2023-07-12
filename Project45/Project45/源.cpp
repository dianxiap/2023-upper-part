#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 15;

LL l, r, len;
LL a[N], dp[N][N][N][N][N][N];

LL dfs(int pos, int pre,int ppre, int st, int f, int e,int limit)
{
	
	if (e && f)return 0;
	if(!pos) return st;
	
	if (!limit && dp[pos][pre][ppre][st][f][e] != -1) return dp[pos][pre][ppre][st][f][e];

	LL res = 0, up = limit ? a[pos] : 9;
	for (int i = 0; i <= up; i++)
	{
		res += dfs(pos - 1, i, pre, st || (i == pre && i == ppre), f || (i == 4), e || (i == 8), limit && i == up);
	}
	return limit ? res : dp[pos][pre][ppre][st][f][e]=res;
}

LL cal(LL x)
{
	len = 0;
	memset(dp, -1, sizeof dp);
	while (x)a[++len] = x % 10, x /= 10;
	if (len != 11)return 0;
	LL ans = 0;
	for (int i = 1; i <= a[len]; i++)
	{
		ans += dfs(len - 1, i, 0, 0, i == 4, i == 8, i == a[len]);
	}
	return ans;

}

int main()
{
	cin >> l >> r;
	cout << cal(r) - cal(l - 1) << endl;
}