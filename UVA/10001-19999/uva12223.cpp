#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 50005;

struct state {
	int v;
	ll w;
	state (int v = 0, ll w = 0) {
		this->v = v;
		this->w = w;
	}
};

int n, vis[N];
ll ans, sum, cnt[N], dp[N];
vector<state> g[N];

void init () {
	int a, b;
	ll w;

	scanf("%d", &n);

	sum = 0;
	memset(dp, 0, sizeof(dp));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i <= n; i++) 
		g[i].clear();

	for (int i = 1; i < n; i++) {
		scanf("%d%d%lld", &a, &b, &w);
		g[a].push_back(state(b, w));
		g[b].push_back(state(a, w));
	}

	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%lld", &a, &w);
		sum += w;
		cnt[a] = w;
	}
}

void dfsCnt (int u, ll W) {
	vis[u] = 1;
	dp[1] += W * cnt[u];
	for (int i = 0; i < g[u].size(); i++) {
		state cur = g[u][i];

		if (vis[cur.v]) continue;

		dfsCnt(cur.v, cur.w*2 + W);

		cnt[u] += cnt[cur.v];
	}
}

void dfsAns (int u) {
	vis[u] = 1;
	ans = min (ans, dp[u]);

	for (int i = 0; i < g[u].size(); i++) {
		state cur = g[u][i];
		if (vis[cur.v]) continue;

		dp[cur.v] = dp[u] + (sum - 2*cnt[cur.v]) * cur.w*2;
		dfsAns(cur.v);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		memset(vis, 0, sizeof(vis));
		dfsCnt(1, 0);

		ans = dp[1];
		memset(vis, 0, sizeof(vis));
		dfsAns(1);

		bool flag = false;
		printf("%lld\n", ans);
		for (int i = 1; i <= n; i++) if (ans == dp[i]) {
			if (flag) printf(" ");
			printf("%d", i);
			flag = true;
		}
		printf("\n");
	}
	return 0;
}
