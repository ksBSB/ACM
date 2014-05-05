#include <stdio.h>
#include <string.h>

#define min(a,b) (a)<(b)?(a):(b)

const int N = 105;
const int K = 15;
const int INF = 0x3f3f3f3f;

int A, B, n, m, l, k;
int dp[N][K], g[N][N], f[N][N], vis[N][K];

void init() {
	scanf("%d%d%d%d%d", &A, &B, &m, &l, &k);
	n = A + B;

	memset(g, INF, sizeof(g));
	memset(f, INF, sizeof(f));
	memset(vis, 0, sizeof(vis));

	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		g[a][b] = g[b][a] = f[a][b] = f[b][a] = c;
	}

	for (int i = 1; i <= n; i++)
		f[i][i] = 0;
}

void Floyd() {

	for (int t = 1; t <= A; t++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] = min(f[i][j], f[i][t] + f[t][j]);
}

void solve() {
	memset(dp, INF, sizeof(dp));
	dp[n][0] = 0;

	m = n * (k + 1);
	int u, v, c;

	for (int t = 0; t < m; t++) {

		c = INF;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= k; j++) {
				if (!vis[i][j] && dp[i][j] < c) {
					u = i, v = j;
					c = dp[i][j];
				}
			}
		}

		vis[u][v] = 1;

		for (int i = 1; i <= n; i++) {
			if (f[u][i] <= l && dp[i][v + 1] > dp[u][v]) {
				dp[i][v + 1] =  dp[u][v];
				vis[i][v + 1] = 0;
			}

			if (dp[i][v] > dp[u][v] + g[u][i]) {
				dp[i][v] = dp[u][v] + g[u][i];
				vis[i][v] = 0;
			}
		}
	}

	printf("%d\n", dp[1][k]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		Floyd();
		solve();
	}
	return 0;
}
