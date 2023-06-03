#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

const int N = 1010;

int n, m;
int tim[N];
int last[N];

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> tim[i];
		last[i] = -1000;
	}

	while (m--)
	{
		int t, k;
		cin >> t >> k;
		while (k--)
		{
			int i;
			cin >> i;
			if (tim[i] == -1)continue;
			if (t - tim[i] >= last[i])
				last[i] = t;
			else
				printf("Don't take %d at %d!\n", i, t);
		}
	}
}