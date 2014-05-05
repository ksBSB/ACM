#include<stdio.h>
#include<string.h>
#define N 250
#define M 3
int r, c, bo, sum;
int map[N][N], vis[N][N];
const int dir[4][2] = {{1, 0}, {-1, 0}, {0 , 1}, {0, -1}};

int build(){
	char ch;
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			scanf("%c", &ch);
			if (ch == '\\'){
				for (int x = 0; x < M; x++)
					for (int y = 0; y < M; y++){
						if (x == y)
							map[i * M + x][j * M + y] = 1;
						else
							map[i * M + x][j * M + y] = 0;
					}
			}
			else{
				for (int x = 0; x < M; x++)
					for (int y = 0; y < M; y++){
						if (x + y == M - 1)
							map[i * M + x][j * M + y] = 1;
						else
							map[i * M + x][j * M + y] = 0;
					}
			}
		}
		getchar();
	}
}

void DFS(int a, int b){
	vis[a][b] = 1;
	sum++;
	int p, q;
	for (int i = 0; i < 4; i++){
		p = a + dir[i][0];
		q = b + dir[i][1];
		if (p < 0 || p >= r)	continue;
		if (q < 0 || q >= c)	continue;
		if (map[p][q] || vis[p][q])	continue;
		if (p == 0 || p == r - 1 || q == 0 || q == c - 1)
			bo = 1;
		DFS(p, q);
	}
}
int main(){
	int cnt, max, t = 1;
	while (scanf("%d%d%*c", &c, &r), c || r){
		// Init.
		memset(map, 0, sizeof(map));
		memset(vis, 0, sizeof(vis));
		cnt = max = 0;

		// Build_Map.
		build();
		r *= 3;
		c *= 3;

		// DFS.
		for (int i = 1; i < r - 1; i++)
			for (int j = 1; j < c - 1; j++){
				if (vis[i][j] || map[i][j])
					continue;
				sum = bo = 0;
				DFS(i, j);
				if (!bo){
					cnt++;
					if (max < sum)
						max = sum;
				}
			}

		// Prinf.
		printf("Maze #%d:\n", t++);
		if (cnt)
			printf("%d Cycles; the longest has length %d.\n\n", cnt, max / M);
		else
			printf("There are no cycles.\n\n");
	}
	return 0;}
