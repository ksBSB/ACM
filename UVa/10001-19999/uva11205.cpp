#include<stdio.h>
#include<string.h>
#define N 101
#define M 101

int n, m;
int map[N][M];
int num[3] = {7, 3, 1};
int tem[M];

int judge(int a, int b, int sum)
{
	for(int i = 1; i <= sum ;i++)
	{
		if(map[a][tem[i]] != map[b][tem[i]])
			return 0;
	}
	return 1;
}

int find(int k)
{
	for(int a = 0; a < n; a++)
		for(int b = a + 1; b < n; b++)
			if( judge(a, b, k) )
				return 0;
return 1;
}

int build(int sum, int k)
{
	if(sum != k - 1)
	{
		for(tem[k] = tem[k - 1] + 1; tem[k] < m; tem[k]++)
			if(build(sum, k + 1))
					return 1;
	}
	else
	{
		if(find(sum))
			return 1;
	}
	return 0;
}

int main()
{
	int t;
	scanf("%d", &t);

	while(t--)
	{
		// Init.
		memset(map, 0, sizeof(map));

		// Read.
		scanf("%d%d", &m, &n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				scanf("%d", &map[i][j]);

/*		// Find the Min.
		int min;
		for(int i = 0; i < 3; i++)
			if(m > num[i])
			{
				min = 4 - i;
				break;
			}
*/		
		// Count.
		int i;
		for(i = 0; i <= m; i++)
		{
			memset(tem, 0, sizeof(tem));
			tem[0] = -1;
			if(build(i,1))		break;
		}

		printf("%d\n", i);
	}
return 0;
}
