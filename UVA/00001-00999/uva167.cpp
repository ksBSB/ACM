#include<stdio.h>
#include<string.h>
#define N 8
int map[N][N];
int vis[3][40];
int max;

void DFS(int cnt, int sum){
	if (cnt >= N){
		if (max < sum)
			max = sum;
	}
	else{
			for (int i = 0; i < N; i++){
				if (vis[0][i] == 0 && vis[1][i + cnt] == 0 && vis[2][i - cnt + N] == 0){
					vis[0][i] = vis[1][i + cnt] = vis[2][i - cnt + N] = 1;
					DFS(cnt + 1, sum + map[cnt][i]);
					vis[0][i] = vis[1][i + cnt] = vis[2][i - cnt + N] = 0;
				}
			}
		}
}

int main(){
	int n;
	scanf("%d", &n);
	while (n--){

		// Init.
		memset(map, 0, sizeof(map));
		memset(vis, 0, sizeof(vis));
		max = 0;

		// Read.
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);

		// DFS.
		DFS(0, 0);

		printf("%5d\n", max);
	}
	return 0;}
