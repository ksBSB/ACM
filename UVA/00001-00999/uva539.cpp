#include<stdio.h>
#include<string.h>

#define N 26

int map[N][N];
int tem[N][N];
int max;
int n;

void find(int h,int time)
{
	int i;

	for(i = 0;i < n; i++)
	{
		if(map[h][i]&&!tem[h][i])
		{
			tem[h][i]=tem[i][h]=1;
			find(i,time+1);
			tem[h][i]=tem[i][h]=0;
		}
	}

	if(time > max)
		max = time;
}

int main()
{
	int m;

	while(scanf("%d%d",&n,&m),n&&m)
	{
		//Init.
		memset(map,0,sizeof(map));
		memset(tem,0,sizeof(tem));
		max=0;

		//Read.
		for(int i = 0;i < m; i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			map[a][b]=map[b][a]=1;
		}

		//Count.
		for(int i = 0;i < n; i++)
			for(int j = 0;j < n ; j++)
				if(map[i][j])
				{
					tem[i][j]=tem[j][i]=1;
					find(j,1);
					tem[i][j]=tem[j][i]=0;
				}
		//Cout.
		printf("%d\n",max);
	}
	return 0;
}
