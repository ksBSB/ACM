#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 405;
const int inf = 0x3f3f3f3f;

int N, M, G[maxn][maxn], dp[maxn];

void init () {
	memset(G, 0, sizeof(G));
	scanf("%d%d", &N, &M);

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		G[u][v] = G[v][u] = 1;
	}
}

int bfs(int s, int e, int t) {
	memset(dp, inf, sizeof(dp));
	dp[s] = 0;

	queue<int> que;
	que.push(s);

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		if (u == e) break;

		for (int i = 1; i <= N; i++) if (G[u][i] == t && dp[i] > dp[u] + 1) {
			dp[i] = dp[u] + 1;
			que.push(i);
		}
	}
	return dp[e];
}

int main () {
	init();
	int ans = max(bfs(1, N, 0), bfs(1, N, 1));
	printf("%d\n", ans == inf ? -1 : ans);
	return 0;
}
