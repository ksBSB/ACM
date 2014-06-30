#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
const int INF = 0x3f3f3f3f;

int n, m, k, g[N][N], A[2*N], dp[N*2][N];

void init () {
	int a, b;

	memset(g, 0, sizeof(g));
	memset(dp, INF, sizeof(dp));

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) dp[0][i] = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}

	scanf("%d",  &k);
	for (int i = 1; i <= k; i++) scanf("%d", &A[i]);
}

int solve() {
	int ans = k;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			for (int t = 1; t <= n; t++) if (j == t || g[j][t]) {
				dp[i][j] = min(dp[i][j], dp[i-1][t]+(j == A[i] ? 0 : 1));
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		ans = min(dp[k][i], ans);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();	
		printf("%d\n", solve());
	}
	return 0;
}
