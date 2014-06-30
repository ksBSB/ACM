#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
const int INF = 0x3f3f3f3f;

int n, m, T, s, e;
int tc[N], vc[N], g[N][N];
int dp[N][N][3*N];

void Floyd () {
	for (int i = 0; i < n; i++)
		g[i][i] = 0;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				g[i][j] = min (g[i][j], g[i][k] + g[k][j]);
		}
	}
}

void init () {
	memset(dp, -1, sizeof(dp));
	memset(g, INF, sizeof(g));

	scanf("%d%d%d%d%d", &n, &m, &T, &s, &e);
	for (int i = 0; i < n; i++)
		scanf("%d", &tc[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &vc[i]);

	int a, b, v;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &v);
		g[a][b] = g[b][a] = min(g[a][b], v);
	}

	Floyd ();
}

int dfs (int u, int val, int t) {
	if (g[u][e] > t) return -INF;

	if (dp[u][val][t] != -1) return dp[u][val][t];

	int& ans = dp[u][val][t];
	ans = 0;

	for (int i = 0; i < n; i++) {
		if (vc[i] <= val) continue;
		ans = max(ans, dfs(i, vc[i], t - tc[i] - g[u][i]) + vc[i]);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case #%d:\n%d\n", i, dfs (s, 0, T));
	}
	return 0;
}
