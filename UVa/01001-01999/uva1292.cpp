#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2000;

int n, dp[N][2], v[N];
vector<int> g[N];

void init () {
	int u, c, p;
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++) g[i].clear();

	for (int i = 0; i < n; i++) {
		scanf("%d:(%d)", &u, &c);
		while (c--) {
			scanf("%d", &p);
			g[u].push_back(p);
			g[p].push_back(u);
		}
	}
}

void dfs (int u) {
	v[u] = dp[u][1] = 1;
	dp[u][0] = 0;

	for (int i = 0; i < g[u].size(); i++) {
		int p = g[u][i];
		if (v[p]) continue;
		dfs(p);
		dp[u][0] += dp[p][1];
		dp[u][1] += min(dp[p][0], dp[p][1]);
	}
}

int solve () {
	int ans = 0;

	for (int i = 0; i < n; i++) {
		if (v[i]) continue;
		dfs(i);
		ans += min(dp[i][0], dp[i][1]);
	}
	return ans;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		printf("%d\n", solve() );
	}
	return 0;
}
