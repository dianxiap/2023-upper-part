#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define ll long long
#define db double
using namespace std;
const ll mod = 1e9 + 7;
string l, r;
ll ml = 0, mr = 0;
ll dp[1010][11][11], len[1010];

ll dfs(ll now, ll last, ll prelast, ll lim, ll lead)
{
	if (now == 0)
		return 1;
	if (last != -1 && prelast != -1 && !lim && !lead
		&& dp[now][last][prelast] != -1)
		return dp[now][last][prelast];
	ll up = lim ? len[now] : 9;
	ll ans = 0;
	for (ll i = 0; i <= up; i++)
	{
		if (!lead && (i == last || i == prelast))
			continue;
		ans += dfs(now - 1, i == 0 && lead ? -1 : i, lead ? -1 : last,
			lim && i == up, lead && i == 0) % mod;
		ans %= mod;
	}
	if (last != -1 && prelast != -1 && !lim && !lead)
		dp[now][last][prelast] = ans;
	return ans;
}

void solve()
{

	memset(dp, -1, sizeof(dp));
	for (ll i = 0; i < r.size(); i++)
		len[i + 1] = r[i] - '0';
	ll ans1 = dfs(r.size(), -1, -1, 1, 1);
	memset(dp, -1, sizeof(dp));
	for (ll i = 0; i < l.size(); i++)
		len[i + 1] = l[i] - '0';
	ll ans2 = dfs(l.size(), -1, -1, 1, 1);
	ans2--;
	for (int i = 1; i < l.size(); i++)
	{
		if (l[i] == l[i - 1] || (i - 2 >= 0 && l[i] == l[i - 2]))
		{
			ans2++;
			break;
		}
	}

	printf("%lld\n", ((mr - ml + 1 - (ans1 - ans2)) % mod + mod) % mod);
		
}

int main()
{
	cin >> l >> r;
	for (int i = 0; i < l.size(); i++)
	{
		ml = (ml * 10 + l[i] - '0') % mod;
	}
	for (int i = 0; i < r.size(); i++)
	{
		mr = (mr * 10 + r[i] - '0') % mod;
	}
	reverse(l.begin(), l.end());
	reverse(r.begin(), r.end());
	solve();
	return 0;
}

