#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 105;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, d;
	Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
	bool operator < (const Edge& a) const { return d < a.d; }
}E[maxn * maxn];

int N, M, F[maxn], D[maxn][maxn], vis[maxn * maxn];
vector<pii> G[maxn];

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	scanf("%d%d", &N, &M);
	memset(D, 0, sizeof(D));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= N; i++)
		F[i] = i, G[i].clear();

	int u, v, w;
	for (int i = 0; i < M; i++)
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].d);
	sort(E, E + M);
}

void dfs (int u, int fa, int w, int* d) {
	d[u] = w;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first;
		if (v == fa) continue;
		dfs(v, u, max(w, G[u][i].second), d);
	}
}

int solve () {
	int ret = 0;
	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v;
		if (find(u) != find(v)) {
			vis[i] = 1;
			ret += E[i].d;
			F[find(u)] = find(v);
			G[u].push_back(make_pair(v, E[i].d));
			G[v].push_back(make_pair(u, E[i].d));
		}
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int ans1 = solve(), ans2 = inf;
		for (int i = 1; i <= N; i++)
			dfs(i, 0, 0, D[i]);
		for (int i = 0; i < M; i++) {
			if (vis[i]) continue;
			int u = E[i].u, v = E[i].v, d = E[i].d;
			ans2 = min(ans2, ans1 + d - D[u][v]);
		}
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}
