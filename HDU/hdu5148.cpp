#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
const int maxn = 2005;

int N, K;
ll ans, dp[maxn][55];
vector<pii> g[maxn];

void cmin(ll& v, ll x) {
	if (v == -1 || v > x)
		v = x;
}

void init () {
	scanf("%d%d", &N, &K);

	ans = -1;
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= N; i++)
		g[i].clear();

	int a, b, c;
	for (int i = 1; i < N; i++) {
		scanf("%d%d%d", &a, &b, &c);
		g[a].push_back(make_pair(b, c));
		g[b].push_back(make_pair(a, c));
	}
}

void dfs(int u, int f) {
	dp[u][1] = 0;

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		int w = g[u][i].second * 2;
		if (v == f) continue;
		dfs(g[u][i].first, u);
		for (int k = K - 1; k; k--) {
			if (dp[u][k] == -1) continue;
			for (int j = 1; j + k <= K; j++) {
				if (dp[v][j] == -1) continue;
				cmin(dp[u][k+j], dp[u][k] + dp[v][j] + w * (K - j) * j);
			}
		}
	}
	if (dp[u][K] != -1)
		cmin(ans, dp[u][K]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		dfs(1, 0);
		printf("%I64d\n", ans);
	}
	return 0;
}
