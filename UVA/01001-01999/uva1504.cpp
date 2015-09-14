#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 3005;
const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

struct Edge {
	int u, v, d;
	Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
	bool operator < (const Edge& a) const { return d < a.d; }
}E[maxn * maxn];

int N, M, Q, F[maxn], G[maxn][maxn], D[maxn][maxn], V[maxn][maxn];
int K, first[maxn], jump[maxn << 1], link[maxn << 1];

inline void addEdge(int u, int v) {
	jump[K] = first[u];
	link[K] = v;
	first[u] = K++;
}
int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	memset(V, 0, sizeof(V));
	memset(G, inf, sizeof(G));
	memset(D, inf, sizeof(D));

	int u, v, d;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &d);
		E[i] = Edge(u, v, d);
		G[u][v] = G[v][u] = min(G[u][v], d);
	}
}

double solve () {
	int n = N;
	double ret = 0;
	sort(E, E + M);

	K = 0;
	memset(first, -1, sizeof(first));
	for (int i = 0; i < N; i++) F[i] = i;

	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v, d = E[i].d;
		if (find(u) != find(v)) {
			F[find(u)] = find(v);
			ret += d;
			addEdge(u, v);
			addEdge(v, u);
			V[u][v] = V[v][u] = 1;
		}
	}
	return ret;
}

int dfs (int root, int u, int fa) {
	int ret = inf;

	for (int i = first[u]; i != -1; i = jump[i]) {
		int v = link[i];
		if (v == fa) continue;
		int tmp = dfs(root, v, u);
		ret = min(tmp, ret);
		D[u][v] = D[v][u] = min(D[u][v], tmp);
	}

	if (fa != root)
		ret = min(ret, G[root][u]);
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		double ans = solve(), sum = 0;
		for (int i = 0; i < N; i++) dfs(i, i, -1);

		scanf("%d", &Q);
		int u, v, d;
		for (int i = 0; i < Q; i++) {
			scanf("%d%d%d", &u, &v, &d);
			if (V[u][v]) {
				sum += min(D[u][v], d) - G[u][v];
			}
		}
		printf("%.4lf\n", sum / Q + ans);
	}
	return 0;
}
