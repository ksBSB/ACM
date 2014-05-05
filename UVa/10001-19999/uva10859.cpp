#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1010;
const int M = 2000;

int n, m, v[N], dp[N][2];
vector<int> g[N];

void init() {
	int a, b;
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++) g[i].clear();
	memset(v, 0, sizeof(v));
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

void dfs(int x) {
	v[x] = 1;
	dp[x][0] = 0;
	dp[x][1] = M;

	for (int i = 0; i < g[x].size(); i++) {
		int u = g[x][i];
		if (v[u]) continue;
		dfs(u);
		dp[x][0] += dp[u][1] + 1;
		if (dp[u][1] > dp[u][0]) {
			dp[x][1] += dp[u][0] + 1;
		} else {
			dp[x][1] += dp[u][1];
		}
	}
}

void solve () {
	int ans = 0;
	for (int i = 0; i < n; i++) if (!v[i]) {
		dfs(i);
		ans += min(dp[i][0], dp[i][1]);
	}
	printf("%d %d %d\n", ans/M, m - (ans%M), ans%M);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
