#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 40005;
const int inf = 0x3f3f3f3f;
const int BIT = 20;

int dep[maxn], f[maxn][BIT+5];
vector<pii> G[maxn];

void ST (int n) {
	for (int k = 1; k <= BIT; k++) {
		for (int i = 1; i <= n; i++) 
			f[i][k] = f[f[i][k-1]][k-1];
	}

	int s;
	for (int i = 1; i <= n; i++) if (f[i][0] == 0) {
		s = i; break;
	}
	memset(dep, inf, sizeof(dep));
	dep[s] = 0;

	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first;
			if (dep[v] > dep[u] + 1) {
				dep[v] = dep[u] + 1;
				que.push(v);
			}
		}
	}
}

int LCA(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);

	int mv = dep[v] - dep[u];
	for (int i = 0; i <= BIT && mv; mv >>= 1, i++)
		if (mv&1) v = f[v][i];

	if (u == v) return u;

	for (int i = BIT; i >= 0; i--) {
		if (f[u][i] == f[v][i]) continue;
		u = f[u][i]; v = f[v][i];
	}
	return f[u][0];
}

int N, M, dis[maxn];

void dfs (int u, int fa) {
	f[u][0] = fa;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first, w = G[u][i].second;
		if (v == fa) continue;
		dis[v] = dis[u] + w;
		dfs(v, u);
	}
}

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) G[i].clear();
	memset(f, 0, sizeof(f));

	int u, v, w;
	for (int i = 1; i < N; i++) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		dfs(1, 0);
		ST(N);

		int u, v;
		while (M--) {
			scanf("%d%d", &u, &v);
			int k = LCA(u, v);
			printf("%d\n", dis[u] - dis[k] + dis[v] - dis[k]);
		}
	}
	return 0;
}
