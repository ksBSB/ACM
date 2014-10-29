#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50005;

int N, M, E, Q, first[maxn], jump[maxn * 2], dpMax[maxn][20], dpMin[maxn][20];
struct Edge {
	int u, v, w;
	void set(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
}ed[maxn * 2];

inline void add_Edge (int u, int v, int w) {
	ed[E].set(u, v, w);
	jump[E] = first[u];
	first[u] = E++;
}

int fmax[maxn], fidx[maxn], smax[maxn], sidx[maxn];

inline void maintain(int u, int w, int v) {
	if (w > smax[u]) {
		smax[u] = w;
		sidx[u] = v;
	}

	if (smax[u] > fmax[u]) {
		swap(smax[u], fmax[u]);
		swap(sidx[u], fidx[u]);
	}
}

void dfs(int u, int pre) {
	fmax[u] = fidx[u] = smax[u] = sidx[u] = 0;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == pre)
			continue;
		dfs(v, u);
		maintain(u, fmax[v] + ed[i].w, v);
	}
}

void dfs(int u, int pre, int d) {
	maintain(u, d, pre);
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == pre)
			continue;
		dfs(v, u, (v == fidx[u] ? smax[u] : fmax[u]) + ed[i].w);
	}
}

void rmq_init() {
	for (int i = 1; i <= N; i++)
		dpMax[i][0] = dpMin[i][0] = fmax[i];

	for (int k = 1; (1<<k) <= N; k++) {
		for (int i = 1; i + (1<<k) - 1 <= N; i++) {
			dpMax[i][k] = max(dpMax[i][k-1], dpMax[i+(1<<(k-1))][k-1]);
			dpMin[i][k] = min(dpMin[i][k-1], dpMin[i+(1<<(k-1))][k-1]);
		}
	}
}

int rmq_query(int l, int r) {
	int k = 0;
	while ((1<<(k+1)) <= r - l + 1) k++;
	return max(dpMax[l][k], dpMax[r-(1<<k)+1][k]) - min(dpMin[l][k], dpMin[r-(1<<k)+1][k]);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		int u, v, w;
		E = 0;
		memset(first, -1, sizeof(first));
		for (int i = 1; i < N; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_Edge(u, v, w);
			add_Edge(v, u, w);
		}

		dfs(1, 0);
		dfs(1, 0, 0);

		rmq_init();
		while (M--) {
			int ans = 0, mv = 1;
			scanf("%d", &Q);
			for (int i = 1; i <= N; i++) {
				while (mv <= i && rmq_query(mv , i) > Q) mv++;
				ans = max(ans, i - mv + 1);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
