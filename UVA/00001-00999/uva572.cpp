#include<stdio.h>
#include<string.h>
#define N 105
char map[N][N];
int n, m, cnt;
const int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
void DFS(int a, int b){

	map[a][b] = '*';
	for (int i = 0; i < 8; i++){
		if (a + dir[i][0] < 0 || a + dir[i][0] >= n)	continue;
		if (b + dir[i][1] < 0 || b + dir[i][1] >= m)	continue;
		if (map[a + dir[i][0]][b + dir[i][1]] == '*')	continue;
		DFS(a + dir[i][0], b + dir[i][1]);
	}
}

int main(){
	while (scanf("%d%d%*c", &n, &m), n && m){
		// Init.
		memset(map, 0, sizeof(map));
		cnt = 0;

		// Read.
		for (int i = 0; i < n; i++)
			gets(map[i]);

		// Handle.
		for (int i = 0; i < n; i ++){
			for (int j = 0; j < m; j++){
				if (map[i][j] == '@'){
					DFS(i, j);
					cnt++;
				}
			}
		}

		printf("%d\n", cnt);
	}
	return 0;}
