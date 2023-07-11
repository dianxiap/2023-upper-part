#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;


LL l,r,len;
LL a[20], dp[20][200][200];
LL mod;

//先预处理所有数字各位上的和，再枚举对自己取模的结果
//pos当前位  sum各位上数字的和  st当前数字对sum取模的结果
LL dfs(int pos, int sum, LL st, int limit)
{
	if (pos>len)
	{
		if (!sum)return 0;
		else return st == 0 && sum == mod ? 1 : 0;
	}
	if (!limit && dp[pos][sum][st] != -1)return dp[pos][sum][st];

	LL res = 0, up = limit ? a[len-pos+1] : 9;
	for (int i = 0; i <= up; i++)
	{
		res += dfs(pos + 1, sum + i, (st * 10 + i)%mod, limit && up == i);
	}
	return limit ? res : dp[pos][sum][st] = res;
}


LL cal(LL x)
{
	len = 0;
	while (x)a[++len] = x % 10, x /= 10;
	LL res = 0;
	//mod是所有
	for (mod = 1; mod <= len * 9; mod++)
	{
		memset(dp, -1, sizeof dp);
		res+=dfs(1, 0, 0, 1);
	}
	return res;
}

int main()
{
	cin >> l >> r;
	cout << cal(r)-cal(l-1) << endl;
}