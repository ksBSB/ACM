#include<stdio.h>
#include<string.h>
#define N 105
int m, n, cnt;
int map[N][N], bo[N];

int judge(int k){
	for (int i = 1; i <= n; i++)
		if (map[k][i])
			return 0;
	return 1;
}

int clear(int k){
	for (int i = 1; i <= n; i++)
		map[i][k] = 0;
}

int main(){
	while (scanf("%d%d", &n, &m), n || m){
		// Init.
		memset(map, 0, sizeof(map));
		memset(bo, 0, sizeof(bo));
		cnt = 0;

		// Read.
		for (int i = 0; i < m; i++){
			int a, b; 
			scanf("%d%d", &a, &b);
			map[b][a] = 1;
		}

		// Handle.
		while (cnt < n){
			for (int i = 1; i <= n; i++){
				if (bo[i])	continue;
				if (judge(i)){
					if (cnt)
						printf(" ");
					printf("%d", i);
					bo[i] = 1;
					cnt++;
					clear(i);
					break;
				}
			}
		}
		printf("\n");
	}
	return 0;}
