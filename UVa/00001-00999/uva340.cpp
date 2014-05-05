#include<stdio.h>
#include<string.h>
#define N 1005
#define M 15
#define min(a, b) a > b? b : a

int num[N][N];
int vis[M], tem[N];

int main(){
	int n, bo, cnt, ti = 1;

	while (scanf("%d", &n), n){
		// Init.
		memset(num, 0, sizeof(num));
		memset(tem, 0, sizeof(tem));
		bo = 1;
		cnt = 0;

		// Read.
		while (bo){
			for (int i = 0; i < n; i++){
				scanf("%d", &num[cnt][i]);
				if (num[cnt][i] == 0)
					bo = 0;
				if (cnt == 0)
					tem[num[0][i]]++;
			}
			cnt++;
		}

		// Printf.
		printf("Game %d:\n", ti++);
		for (int i = 1; i < cnt - 1; i++){
			memset(vis, 0, sizeof(vis));
			int so = 0, fo = 0;

			for (int j = 0; j < n; j++){
				if (num[i][j] == num[0][j])
					so++;
				vis[num[i][j]]++;
			}

			for (int j = 1; j <= 9; j++)
				fo += min(tem[j], vis[j]);

			printf("    (%d,%d)\n", so, fo - so);
		}
	}
	return 0;
}
