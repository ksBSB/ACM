#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;

struct Edge {
	int u, v, l;
	Edge(int u = 0, int v = 0, int l = 0): u(u), v(v), l(l) {}
	bool operator < (const Edge& u) const { return l < u.l; }
};

int N, F[maxn], X[maxn], Y[maxn], P[maxn], D[maxn][maxn];
vector<Edge> edges, G[maxn];

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }
int distance(int x, int y) { return x * x + y * y; }

void init () {
	scanf("%d", &N);
	edges.clear();
	memset(D, 0, sizeof(D));
	for (int i = 1; i <= N; i++) {
		F[i] = i;
		G[i].clear();
	}

	for (int i = 1; i <= N; i++) {
		scanf("%d%d%d", &X[i], &Y[i], &P[i]);
		for (int j = 1; j < i; j++)
			edges.push_back(Edge(i, j, distance(X[i]-X[j], Y[i]-Y[j])));
	}
	sort(edges.begin(), edges.end());
}

void dfs (int u, int f, int d, int* p) {
	p[u] = d;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].v, td = G[u][i].l;
		if (v == f) continue;
		dfs(v, u, max(d, td), p);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		double S = 0;
		for (int i = 0; i < edges.size(); i++) {
			int u = edges[i].u, v = edges[i].v;
			if (find(u) != find(v)) {
				F[find(u)] = find(v);
				G[u].push_back(Edge(u, v, edges[i].l));
				G[v].push_back(Edge(v, u, edges[i].l));
				S += sqrt(edges[i].l);
			}
		}

		double ans = 0;
		for (int i = 1; i <= N; i++) dfs(i, -1, 0, D[i]);
		for (int i = 1; i <= N; i++)
			for (int j = i+1; j <= N; j++)
				ans = max(ans, (P[i] + P[j]) * 1.0 / (S - sqrt(D[i][j])));
		printf("%.2lf\n", ans);
	}
	return 0;
}
