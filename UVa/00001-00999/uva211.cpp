#include <stdio.h>
#include <string.h>

const int R = 7;
const int C = 8;
const int N = 30;
const int d[2][2] = {{0, 1}, {1, 0}};

int ans, t[R][C], g[R][C], vis[R][C], rec[N];

bool init() {
	ans = 0;
	memset(rec, 0, sizeof(rec));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) if (scanf("%d", &g[i][j]) != 1) return false;
	return true;
}

void setInit() {
	int c = 1;
	for (int i = 0; i < R; i++)
		for (int j = i; j < R; j++)
			t[i][j] = t[j][i] = c++;
}

void put() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) printf("%4d", vis[i][j]);
		printf("\n");
	}
	printf("\n");
}

void dfs(int x, int y, int c) {
	if (c == 28) {
		ans++; put();
		return;
	}

	if (y == C) {
		x++; y = 0;
	}
	if (vis[x][y]) dfs(x, y + 1, c);
	else {

		for (int i = 0; i < 2; i++) {
			int p = x + d[i][0], q = y + d[i][1];
			if (p >= R || q >= C || vis[p][q]) continue;
			int k = t[g[x][y]][g[p][q]];
			if (rec[k]) continue;
			vis[x][y] = vis[p][q] = k; rec[k] = 1;
			dfs(x, y + 1, c + 1);
			vis[x][y] = vis[p][q] = 0; rec[k] = 0;
		}
	}
}

int main() {
	setInit();
	int cas = 0;
	while (init()) {
		if (cas) printf("\n\n\n");
		printf("Layout #%d:\n\n", ++cas);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++)
				printf("%4d", g[i][j]);
			printf("\n");
		}

		printf("\nMaps resulting from layout #%d are:\n\n", cas); 
		dfs(0, 0, 0);
		printf("There are %d solution(s) for layout #%d.\n", ans, cas);
	}
	return 0;
}
