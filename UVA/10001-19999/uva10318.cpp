#include <stdio.h>
#include <string.h>

const int N = 10;

int r, c, n, d[N][2], cnt[N], vis[N][N], rec[N][N];
char g[N][N];

void init() {
	n = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));
	memset(rec, 0, sizeof(rec));

	for (int i = 0; i < 3; i++) {
		scanf("%s", g[i]);
		for (int j = 0; j < 3; j++) if (g[i][j] == '*') {
			d[n][0] = i - 1; d[n][1] = j - 1;
			n++;
		}
	}
}

void put() {
	int p = 0, path[50];
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) if (rec[i][j]) {
			path[p++] = i * c + j + 1;
		}
	for (int i = 0; i < p - 1; i++) printf("%d ", path[i]);
	printf("%d\n" , path[p-1]);
}

void clear(int x, int y) {
	for (int i = 0; i < n; i++) {
		int p = x + d[i][0], q = y + d[i][1];
		if (p < 0 || p >= r || q < 0 || q >= c) continue;
		if (vis[p][q])	cnt[p]--;
		else   cnt[p]++;
		vis[p][q] = vis[p][q] ? 0 : 1;
	}
}

bool dfs(int x, int y) {
	if (y == c) { 
		x += 1; y = 0;
		if (x >= 2 && cnt[x - 2] != c) return false;
	}

	if (x == r) {
		if (cnt[x - 1] != c) return false;
		put();
		return true;
	}

	if (dfs(x, y + 1)) return true;

	rec[x][y] = 1; clear(x, y); 
	if (dfs(x, y + 1)) return true;
	rec[x][y] = 0; clear(x, y);

	return false;	
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &r, &c) == 2 && r + c) {
		init();
		printf("Case #%d\n", cas++);
		if (!dfs(0, 0)) printf("Impossible.\n");
	}
	return 0;
}
