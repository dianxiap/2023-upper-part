#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>

using namespace std;
int dig[11];
int dp[11][5000];
int A, B;
int pow2[11];

int F(int x)
{
    int cnt = 0;
    int ret = 0;
    while (x)
    {
        ret += (x % 10) << cnt;
        x /= 10;
        cnt++;
    }
    return ret;
}

int dfs(int pos, int comp, bool limit)
{
    if (pos == 0) return comp >= 0;
    if (!limit && dp[pos][comp] != -1) return dp[pos][comp];

    int up = limit ? dig[pos] : 9;
    int ans = 0;
    for (int i = 0; i <= up; i++)
    {
        int new_comp = comp - i * pow2[pos - 1];
        if (new_comp < 0) continue;
        ans += dfs(pos - 1, new_comp, limit && i == up);
    }

    if (!limit) dp[pos][comp] = ans;
    return ans;
}
int solve(int x)
{
    int len = 0;
    while (x)
    {
        dig[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, F(A), 1);
}

int main()
{
    pow2[0] = 1;
    for (int i = 1; i <= 10; i++) pow2[i] = pow2[i - 1] * 2;

    int t;
    scanf("%d", &t);
    memset(dp, -1, sizeof(dp));
    for (int kase = 1; kase <= t; kase++)
    {
        scanf("%d%d", &A, &B);
        printf("Case #%d: %d\n", kase, solve(B));
    }
}