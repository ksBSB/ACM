#include<iostream>
#include<string.h>
using namespace std;

#define M 8

char map[M][M];
int vis[M][M];
int n;
int max_deep;

int judge (int x, int y)
{
	for (int i = 1; ; i++)
	{
		if (x - i < 0)
			break;
		else if (map[x - i][y] == 'X')
			break;
		else if (vis[x - i][y])
			return 0;
	}

	for (int i = 1; ; i++)
	{
		if ( x + i >= n)
			break;
		else if (map[x + i][y] == 'X')
			break;
		else if (vis[x + i][y])
			return 0;
	}

	for (int i = 1; ; i++)
	{
		if (y - i < 0)
			break;
		else if (map[x][y - i] == 'X')
			break;
		else if (vis[x][y - i])
			return 0;
	}

	for (int i = 1; ; i++)
	{
		if (y + i >= n)
			break;
		else if (map[x][y + i] =='X')
			break;
		else if (vis[x][y + i])
			return 0;
	}
	return 1;
}

void DFS(int x, int y, int deep)
{
	while (1)
	{
		if (y >= n)
		{
			y = 0;
			x++;
		}

		if (x >= n)
		{
			if (deep > max_deep)
				max_deep = deep;
			return;
		}

		if (map[x][y] == '.' && judge(x, y))
		{
			vis[x][y] = 1;
			DFS(x, y + 1, deep + 1);
			vis[x][y] = 0;
		}

		y++;
	}
}

int main()
{
	while (cin >> n, n)
	{
		// Init.
		memset(vis, 0, sizeof(vis));
		memset(map, 0, sizeof(map));
		max_deep = 0;

		// Read.
		for (int i = 0; i < n; i++)
			for (int j = 0;j < n; j++)
				cin >> map[i][j];

		DFS(0, 0, 0);

		cout << max_deep << endl;
	}
	return 0;
}
