#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 10005;
const int inf = 0x3f3f3f3f;
const int BIT = 20;

int dep[maxn], far[maxn][BIT+5];
vector<pii> G[maxn];
queue<int> que;

void ST (int n) {
	for (int k = 1; k <= BIT; k++) {
		for (int i = 1; i <= n; i++) 
			far[i][k] = far[far[i][k-1]][k-1];
	}

	memset(dep, inf, sizeof(dep));
	for (int i = 1; i <= n; i++) if (far[i][0] == 0) {
		dep[i] = 0; que.push(i);
	}

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
		if (mv&1) v = far[v][i];

	if (u == v) return u;

	for (int i = BIT; i >= 0; i--) {
		if (far[u][i] == far[v][i]) continue;
		u = far[u][i]; v = far[v][i];
	}
	return far[u][0];
}

int N, M, Q, f[maxn];
long long dis[maxn];

int find (int x) { return x == f[x] ? x : f[x] = find(f[x]); }

void dfs (int u, int fa) {
	far[u][0] = fa;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first, w = G[u][i].second;
		if (v == fa) continue;
		dis[v] = dis[u] + w;
		dfs(v, u);
	}
}

void init () {
	memset(dis, 0, sizeof(dis));
	for (int i = 1; i <= N; i++) {
		f[i] = i; far[i][0] = 0;
		G[i].clear();
	}

	int u, v, w;
	while (M--) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
		int p = find(u), q = find(v);
		if (p != q) f[p] = q;
	}
}

int main () {
	while (scanf("%d%d%d", &N, &M, &Q) == 3) {
		init();
		for (int i = 1; i <= N; i++)
			if (far[i][0] == 0) dfs(i, 0);
		ST(N);

		int u, v;
		while (Q--) {
			scanf("%d%d", &u, &v);
			if (find(u) != find(v)) printf("Not connected\n");
			else {
				int k = LCA(u, v);
				printf("%lld\n", dis[u] + dis[v] - 2 * dis[k]);
			}
		}
	}
	return 0;
}
