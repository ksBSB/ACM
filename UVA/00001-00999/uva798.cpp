#include <stdio.h>
#include <string.h>

const int N = 20;
const int M = 105;
int n, c, r, ans;
int w[N], h[N], m[N], g[M][M];

void init() {
	ans = 0;
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++) scanf("%d%d%d", &m[i], &w[i], &h[i]);
}

bool judge(int x, int y, int p, int q) {
	if (x + p > r || y + q > c) return false;

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			if (g[x + i][y + j]) return false;
		}
	}
	return true;
}

void set(int x, int y, int p, int q, int d) {
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++)
			g[x + i][y + j] = d;
	}
}

void dfs(int x, int y) {
	if (y >= c) {
		x += 1; 
		y = 0;
	}

	if (x >= r) {
		ans++; return;
	}

	if (!g[x][y]) {
		for (int i = 0; i < n; i++) if (m[i]) {

			if (judge(x, y, h[i], w[i])) {
				set(x, y, h[i], w[i], 1); m[i]--;
				dfs(x, y + 1);
				set(x, y, h[i], w[i], 0); m[i]++;
			} 

			if (judge(x, y, w[i], h[i]) && h[i] != w[i]) {
				set(x, y, w[i], h[i], 1); m[i]--;
				dfs(x, y + 1);
				set(x, y, w[i], h[i], 0); m[i]++;
			}
		}
	} else
		dfs(x, y + 1);
}

int main () {
	while (scanf("%d%d%d", &c, &r, &n) == 3) {
		init();
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
