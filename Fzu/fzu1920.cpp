#include <stdio.h>
#include <string.h>

const int N = 10;
const int d[][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };

int n, v[N][N];
char g[N][N];

void init() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%s", g[i]);
	memset(v, 0, sizeof(v));
}

void dfs(int x, int y) {
	v[x][y] = 1;

	if (g[x][y] != '0') return;

	for (int i = 0; i < 8; i++) {
		int p = x + d[i][0], q = y + d[i][1];
		if (p < 0 || p >= n) continue;
		if (q < 0 || q >= n) continue;

		if ( !v[p][q] )
			dfs(p, q);
	}
}

int solve() {

	int ans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ( !v[i][j] && g[i][j] == '0')
				dfs(i, j), ans++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ( !v[i][j] && g[i][j] != '@') ans++;
		}
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %d\n", i, solve() );
	}
	return 0;
}
