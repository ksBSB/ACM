#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, M, E, first[maxn], jump[maxn * 2], link[maxn * 2], vis[maxn];
int id, idx[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn], dep[maxn];

inline void add_Edge (int u, int v) {
	link[E] = v;
	jump[E] = first[u];
	first[u] = E++;
}

void dfs (int u, int pre, int d) {
	far[u] = pre;
	son[u] = 0;
	cnt[u] = 1;
	dep[u] = d;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == pre)
			continue;
		dfs(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs (int u, int rot) {
	top[u] = rot;
	idx[u] = ++id;
	if (son[u])
		dfs(son[u], rot);
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u] || v == son[u])
			continue;
		dfs(v, v);
	}
}

void dfs (int u) {
	if (vis[u])
		return;
	vis[u] = 1;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u])
			continue;
		dfs(v);
	}
}

struct query {
	int u, v, r, d;
	void set(int u, int v, int r, int d) {
		this->u = u;
		this->v = v;
		this->r = r;
		this->d = d;
	}
	friend bool operator < (const query& a, const query& b) {
		return a.d > b.d;
	}
}q[maxn];

int LCA (int u, int v) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		u = far[p];
		p = top[u];
	}
	return dep[u] < dep[v] ? u : v;
}

void init () {
	E = id = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(u, v);
		add_Edge(v, u);
	}
	dfs(1, 0, 0);
	dfs(1, 1);

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		int rot = LCA(u, v);
		q[i].set(u, v, rot, dep[rot]);
	}
	sort(q, q + M);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();

		int ans = 0;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < M; i++) {
			if (vis[q[i].u] || vis[q[i].v])
				continue;
			dfs(q[i].r);
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
