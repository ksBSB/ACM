#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, w;
	Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
	bool operator < (const Edge& u) const { return w < u.w; }
}E[maxn];

int N, M, K, F[maxn];

void init () {

	int u, v, w;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		E[i] = Edge(u, v, w);
	}
	sort(E, E + M);
}

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }

int handle(int s, int u, int v) {
	for (int i = 1; i <= N; i++) F[i] = i;

	for (int i = s; i < M; i++) {
		int p = find(E[i].u), q = find(E[i].v);
		if (p != q)
			F[p] = q;
		if (find(u) == find(v)) return E[i].w - E[s].w;
	}
	return inf;
}

int solve (int s, int e) {
	int ret = inf;
	for (int i = 0; i < M; i++)
		ret = min(ret, handle(i, s, e));
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();

		int s, e, u, v;
		scanf("%d%d", &s, &e);

		scanf("%d", &K);
		while (K--) {
			scanf("%d%d", &u, &v);
			while (u == v);
			printf("%d\n", solve(u, v) + s + e);
		}
	}
	return 0;
}
