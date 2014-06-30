#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
#define N 8

struct co{
	int x;
	int y;
}; 
int dir[N][2]={{-1, -2}, {-2, -1}, {1, -2}, {-2, 1}, {1, 2}, {2, 1}, {-1, 2}, {2, -1}};
int map[N][N];
co en;
char str1[N], str2[N];

int find(co *head, co *end, int k)
{
	co *move = end;
	while(head != end)
	{
		for(int i = 0; i < N; i++)
		{
			int a = head->x + dir[i][0];
			int b = head->y + dir[i][1];

			if(a < 0 || a >= N)	continue;
			if(b < 0 || b >= N) continue;
			if(map[a][b])	continue;	
			if(a == en.x && b == en.y)
			{
				printf("To get from %s to %s takes %d knight moves.\n", str1, str2, k + 1);
				return 1;
			}			
			move->x = a;
			move->y = b;
			map[a][b] = 1;
			move++;
		}
		head++;
	}

	if(find(end, move, k+1))
		return 1;
	else
		return 0;
}

int main()
{
	while(cin>> str1>> str2)
	{
		memset(map, 0, sizeof(map));
		if(strcmp(str1, str2) == 0)
		{
			printf("To get from %s to %s takes 0 knight moves.\n", str1, str2);
			continue;
		}

		en.x = str2[0] - 'a';
		en.y = str2[1] - '1';

		co q[100];

		q[0].x = str1[0] - 'a';
		q[0].y = str1[1] - '1';
		map[q[0].x][q[0].y] = 1;

		find(q, q + 1, 0);
		memset(str1, 0, sizeof(str1));
		memset(str2, 0, sizeof(str2));
	}
	return 0;}
