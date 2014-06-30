#include<stdio.h>
#include<string.h>
#define M 5
#define N 26

int x, y, p, q;
int map[N][N];
int n;

void find_go(int k)
{
	for(int i = 0; i < n; i++)
		for(int j = 1; map[i][j]; j++)
			if(map[i][j] == k)
			{
				x=i;
				y=j;
				return;
			}
}

void find_come(int k)
{
	for(int i = 0; i < n; i++)
		for(int j = 1; map[i][j]; j++)
			if(map[i][j] == k)
			{
				p=i;
				q=j;
				return;
			}
}

void re_move(int k)
{
	if(k == 26)
		map[0][1] = k;
	else
		map[k][1] = k;
}

void clear(int a, int b)
{
	for(int i = 1; map[a][b+i]; i++)
	{
		re_move(map[a][b+i]);
		map[a][b+i] = 0;
	}
}

int main()
{
	while(scanf("%d",&n) == 1)
	{
		// Init.
		memset(map, 0, sizeof(map));	
		for(int i = 0; i < n; i++)
			map[i][0] = map[i][1] = i;
		map[0][1] = 26;

		// Read.
		char str[M];
		int a,b;

		while(scanf("%s", str), strcmp(str, "quit"))
		{
			if(strcmp(str, "move") == 0)
			{
				scanf("%d%s%d", &a, str, &b);

				if(a == 0)	a = 26;
				if(b == 0)  b = 26;
				
				find_go(a);
				find_come(b);
				if(x == p)	continue;
				clear(x, y);
			
				if(strcmp(str, "onto") == 0)
				{
					clear(p, q);
					map[p][q+1] = map[x][y];
					map[x][y] = 0;
				}	
				else
				{
					int i;
					for(i = 1; map[p][q+i]; i++);
					map[p][q+i] = map[x][y];
					map[x][y] = 0;		
				}					
			}
			else
			{
				scanf("%d%s%d", &a, str, &b);
				if(a == 0)	a = 26;
				if(b == 0)	b = 26;	
			
				find_go(a);
				find_come(b);

				if(x == p) continue;

				if(strcmp(str, "onto") == 0)
				{
					clear(p, q);

					for(int i = 0; map[p][q+i]; i++)
					{
						map[p][q+i+1] = map[x][y+i];
						map[x][y+i] = 0;
					}
				}
				else
				{
					int i;

					for(i = 1; map[p][q+i]; i++);
					for(int j = 0; map[x][y+j]; j++, i++)
					{	
						map[p][q+i] = map[x][y+j];
						map[x][y+j] = 0;
					}
				}
			}
		}

		//Cout.	
		for(int i = 0;i < n; i++)
		{
			printf("%d:",i);

			for(int j = 1; map[i][j]; j++)
			{
				if(map[i][j] == 26)
					printf(" 0");
				else	
					printf(" %d", map[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
