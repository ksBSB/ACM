#include <stdio.h>
#include <string.h>

#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)

const int N = 150;
const int INF = 0x3f3f3f3f;

int n, m, ans, g[N][N], f[N][N];

void init() {
	int a, b;
	memset(g, 0, sizeof(g));
	memset(f, INF, sizeof(f));

	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		f[a][b] = f[b][a] = g[a][b] = g[b][a] = 1;
	}

	for (int i = 0; i < n; i++)
		f[i][i] = 0;
}

void Floyd() {
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}

int solve() {
	int tmp, ans = 0;
	int c, s[N];

	for (int x = 0; x < n; x++) {
		for (int y = x + 1; y < n; y++) {

			if (f[x][y] == INF) continue;

			tmp = c = 0;
			memset(s, 0, sizeof(s));

			for (int i = 0; i < n; i++) if (f[x][i] + f[i][y] == f[x][y]) s[c++] = i;

			for (int i = 0; i < c; i++) {
				for (int j = i + 1; j < c; j++) {

					if (g[s[i]][s[j]] && f[x][s[i]] != f[x][s[j]]) tmp++;
				}
			}

			ans = max(ans, tmp);

		}
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		Floyd();
		printf("Case #%d: %d\n", i, solve() );
	}
	return 0;
}
