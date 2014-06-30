#include<stdio.h>
#include<string.h>
#define N 50
struct coor{
	int x;
	int y;
	int z;
};

char map[N][N][N];
int vis[N][N][N];
int n, m, h, cnt;
coor que[N * N * N];
const int dir[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

int BFS(coor *head, coor *end){
	if (head == end)
		return 0;
	coor *move = end;
	while (head != end){
		for (int i = 0; i < 6; i++){
			int a, b, c;
			a = head -> x + dir[i][0];
			b = head -> y + dir[i][1];
			c = head -> z + dir[i][2];
			if (a < 0 || a >= n)	continue;
			if (b < 0 || b >= m)	continue;
			if (c < 0 || c >= h)	continue;
			if (vis[c][a][b])	continue;
			if (map[c][a][b] == '#')	continue;

			if (map[c][a][b] == 'E')	return 1;

			move -> x = a;
			move -> y = b;
			move -> z = c;
			vis[c][a][b] = 1;
			move++;
		}
		head++;}
	cnt++;
	if (BFS(end, move))
		return 1;
	else
		return 0;
}

int judge(){
	for (int a = 0; a < h; a++)
		for (int b = 0; b < n; b++)
			for (int c = 0; c < m; c++)
				if (map[a][b][c] == 'S'){
					que[0].x = b, que[0].y = c, que[0].z = a;
					vis[a][b][c] = 1;
					if (BFS(que, que + 1))
						return 1;
					else
						return 0;
				}
}

int main(){
	while (scanf("%d%d%d", &h, &n, &m), h && n && m){
		// Init.
		memset(map, 0, sizeof(map));
		memset(vis, 0, sizeof(vis));
		memset(que, 0, sizeof(que));
		cnt = 0;

		// Read.
		for (int k = 0; k < h; k++){
			getchar();
			for (int i = 0; i < n; i++)
				gets(map[k][i]);
		}

		// Handle.
		if(judge())
			printf("Escaped in %d minute(s).\n", cnt + 1);
		else
			printf("Trapped!\n");
	}
	return 0;}
