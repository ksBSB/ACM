#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50005;
typedef long long ll;

int N, C, E, W[maxn], T[maxn], first[maxn], jump[maxn<<1], linker[maxn<<1];
ll dp[maxn][5], ed[maxn][5], ans[maxn];

void addEdge(int u, int v) {
	jump[E] = first[u];
	linker[E] = v;
	first[u] = E++;
}

void init () {
	scanf("%d%d", &N, &C);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &W[i], &T[i]);

	E = 0;
	int u, v;
	memset(first, -1, sizeof(first));
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
}

void maintain(int u) {
	ans[u] += W[u];
	if (T[u]) {
		for (int i = C; i; i--) {
			dp[u][i] = dp[u][i-1] + W[u];
			ed[u][i] = ed[u][i-1] + W[u];
		}
		dp[u][0] = dp[u][0] = 0;
		ed[u][1] = ed[u][1] = W[u];
	} else {
		for (int i = C; i >= 0; i--) {
			dp[u][i] += W[u];
			ed[u][i] += W[u];
		}
	}
	ed[u][0] = ed[u][0] = 0;
}

void modify(ll& d, ll v) { d = max(d, v); }

void dfs (int u, int fa) {
	ll& ret = ans[u];
	ret = 0;
	memset(dp[u], 0, sizeof(dp[u]));
	memset(ed[u], 0, sizeof(ed[u]));

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = linker[i];
		if (v == fa) continue;
		dfs(v, u);

		if (T[u]) {
			int t = C - 1;
			for (int i = 0; i <= t; i++) {
				ret = max(ret, ed[v][i] + dp[u][t-i]);
				ret = max(ret, ed[u][i] + dp[v][t-i]);
			}
		} else {
			// 当前节点不是trap时，dp转移时不能等于C
			for (int i = 1; i <= C; i++) {
				ret = max(ret, ed[v][i] + dp[u][C-i]);
				ret = max(ret, ed[u][i] + dp[v][C-i]);
			}
		}

		for (int i = 0; i <= C; i++) {
			modify(dp[u][i], dp[v][i]);
			modify(ed[u][i], ed[v][i]);
		}
	}
	maintain(u);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		dfs(0, 0);
		ll ret = 0;
		for (int i = 0; i < N; i++)
			ret = max(ret, ans[i]);
		printf("%lld\n", ret);
	}
	return 0;
}
