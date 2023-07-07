#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

const int N = 55;

char s[3][3];


int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cin >> s[i][j];
			}
		}
		int flag = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((i == 0 && s[i][j] == '+' && s[i + 1][j] == '+' && s[i + 2][j] == '+') ||
					(j == 0 && s[i][j] == '+' && s[i][j + 1] == '+' && s[i][j + 2] == '+') ||
					(i == 0 && j == 0 && s[i][j] == '+' && s[i + 1][j + 1] == '+' && s[i + 2][j + 2] == '+') ||
					(i == 0 && j == 2 && s[i][j + 2] == ' +' && s[i + 1][j + 1] == '+' && s[i + 2][j] == '+'))
					{
						cout << '+' << endl;
						flag = 1;
					}

				if ((i == 0 && s[i][j] == 'X' && s[i + 1][j] == 'X' && s[i + 2][j] == 'X') ||
					(j == 0 && s[i][j] == 'X' && s[i][j + 1] == 'X' && s[i][j + 2] == 'X') ||
					(i == 0 && j == 0 && s[i][j] == 'X' && s[i + 1][j + 1] == 'X' && s[i + 2][j + 2] == 'X') ||
					(i == 0 && j == 2 && s[i][j + 2] == ' X' && s[i + 1][j + 1] == 'X' && s[i + 2][j] == 'X'))
					{
						cout << 'X' << endl;
						flag = 1;
					}
				if ((i == 0 && s[i][j] ==  'O' && s[i + 1][j] == 'O' && s[i + 2][j] == 'O') ||
					(j == 0 && s[i][j] == 'O' && s[i][j + 1] == 'O' && s[i][j + 2] == 'O') ||
					(i == 0 && j == 0 && s[i][j] == 'O' && s[i + 1][j + 1] == 'O' && s[i + 2][j + 2] == 'O') ||
					(i == 0 && j == 2 && s[i][j + 2] == 'O' && s[i + 1][j + 1] == 'O' && s[i + 2][j] == 'O'))
				
					{
						cout << 'O' << endl;
						flag = 1;
					}
				

			}


		}
		if(!flag)cout << "DRAW" << endl;
	}
}