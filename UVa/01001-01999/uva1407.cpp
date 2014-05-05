#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 505;
const int INF = 0x3f3f3f3f;
struct state {
	int v, val;
	state() { };
	state(int vi, int value) {
		this->v = vi;
		this->val = value;
	}
};

int n, m, vis[N], cnt[N], dp[N][N][2];
vector<state> g[N];

void init () {
	memset(vis, 0, sizeof(vis));
	memset(dp, INF, sizeof(dp));
	for (int i = 0; i < n; i++) g[i].clear();

	int a, b, value;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &a, &b, &value);
		g[a].push_back(state(b, value));
		g[b].push_back(state(a, value));
	}
}

void solve (int u) {
	vis[u] = cnt[u] = 1;
	dp[u][1][0] = dp[u][1][1] = 0;

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v, val = g[u][i].val;
		if (vis[v]) continue;
		solve(v);

		cnt[u] += cnt[v];
		for (int j = cnt[u]; j > 1; j--) {

			for (int x = 0; x <= j && x <= cnt[v]; x++) {
				dp[u][j][0] = min(dp[u][j][0], dp[u][j-x][1]+dp[v][x][0]+val);
				dp[u][j][0] = min(dp[u][j][0], dp[u][j-x][0]+dp[v][x][1]+2*val);
				dp[u][j][1] = min(dp[u][j][1], dp[u][j-x][1]+dp[v][x][1]+2*val);
			}
		}
	}	
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init();
		solve(0);

		printf("Case %d:\n", cas++);
		int a;
		scanf("%d", &m);
		while (m--) {
			scanf("%d", &a);
			for (int i = n; i; i--) if (dp[0][i][0] <= a) {
				printf("%d\n", i); break;
			}
		}
	}
	return 0;
}
