#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, Q, ne, first[maxn], f[maxn], jump[maxn * 2];
int id, idx[maxn], top[maxn], far[maxn], son[maxn], dep[maxn], cnt[maxn];

struct Edge {
	int u, v;
	void set (int u, int v) {
		this->u = u;
		this->v = v;
	}
}ed[maxn * 2];

void dfs (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	cnt[u] = 1;
	son[u] = 0;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == pre)
			continue;
		dfs(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs(int u, int rot) {
	top[u] = rot;
	idx[u] = ++id;
	if (son[u])
		dfs(son[u], rot);
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == far[u] || v == son[u])
			continue;
		dfs(v, v);
	}
}

inline void add_Edge(int u, int v) {
	ed[ne].set(u, v);
	jump[ne] = first[u];
	first[u] = ne++;
}

void init () {
	int u, v;
	ne = id = 0;
	memset(first, -1, sizeof(first));
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(u, v);
		add_Edge(v, u);
	}
	dfs(1, 0, 0);
	dfs(1, 1);
	for (int i = 0; i < N - 1; i++) {
		int t = i * 2;
		if (dep[ed[t].u] < dep[ed[t].v])
			swap(ed[t].u, ed[t].v);
	}
}

inline void add (int l, int r) {
	f[l]++, f[r + 1]--;
}

void solve (int u, int v) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		add(idx[p], idx[u]);

		u = far[p];
		p = top[u];
	}

	if (u == v)
		return;

	if (dep[u] > dep[v])
		swap(u, v);
	add(idx[son[u]], idx[v]);
}

int main () {
	init();

	scanf("%d", &Q);
	int u, v;
	while (Q--) {
		scanf("%d%d", &u, &v);
		solve(u, v);
	}

	int mv = 0;
	for (int i = 1; i <= N; i++) {
		mv += f[i];
		f[i] = mv;
	}

	printf("%d", f[idx[ed[0].u]]);
	for (int i = 1; i < N - 1; i++)
		printf(" %d", f[idx[ed[i*2].u]]);
	printf("\n");
	return 0;
}
