#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 5
#define order 23
#define MAX 10

int num[MAX];
int ok;
int bo;

void dfs(int x, int sum)
{
	if ( sum == order && x == 5)
	{
		ok = 1;
		return ;
	}
	else if (x >= 5)
		return;
	dfs(x + 1, sum + num[x]);
	dfs(x + 1, sum - num[x]);
	dfs(x + 1, sum * num[x]);
}

int main()
{
	while (1)
	{
		// Init.
		memset(num, 0, sizeof(num));
		bo = 1;
		ok = 0;

		// Read.
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &num[i]);
			if (num[i])
				bo = 0;
		}

		if (bo) 
			break;

		sort(num, num + N);

		do{
			dfs(1, num[0]);
		}while(next_permutation(num, num + N));

		if (ok)
			printf("Possible\n");
		else
			printf("Impossible\n");
	}
	return 0;
}
