#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
using namespace std;

const int N = 300;
int a[N][N];
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	int sum = 0;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < m / 2; j++)
		{
			sum = a[i * 2][j * 2] + a[i * 2 + 1][j * 2] + a[i * 2][j * 2 + 1] + a[i * 2 + 1][j * 2 + 1];
			sum /= 4;
			cout << sum << ' ';
		}
		cout << endl;
	}
}