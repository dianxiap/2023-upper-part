#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

const int N = 1010;

int a[N];
int n, m;

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)cin >> a[i];

	int sum = 0;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += a[i];
		if (sum > m)
		{
			sum = a[i];
			cnt++;
		}
		
	}
	cout << cnt;
}