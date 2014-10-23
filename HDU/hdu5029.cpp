#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100010;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2], d[maxn << 2];

inline void pushup(int u) {
	int k = s[lson(u)] < s[rson(u)] ? rson(u) : lson(u);
	s[u] = s[k];
	d[u] = d[k];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	if (l == r) {
		s[u] = 0;
		d[u] = l;
		return;
	}
	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
} 

void modify(int u, int x, int v) {
	if (lc[u] == x && rc[u] == x) {
		s[u] += v;
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, v);
	else
		modify(rson(u), x, v);
	pushup(u);
}

typedef pair<int,int> pii;
vector<pii> g[maxn];
int N, M, E, first[maxn], jump[maxn * 2], link[maxn * 2], val[maxn];
int id, idx[maxn], dep[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn];

inline void add_Edge (int u, int v) {
	link[E] = v;
	jump[E] = first[u];
	first[u] = E++;
}

void dfs (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	cnt[u] = 1;
	son[u] = 0;

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

void dfs(int u, int rot) {
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

void init () {
	int u, v;
	id = E = 0;
	memset(first, -1, sizeof(first));
	for (int i = 0; i <= N; i++) g[i].clear();

	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(u, v);
		add_Edge(v, u);
	}
	dfs(1, 0, 0);
	dfs(1, 1);
}

inline void add(int l, int r, int x) {
	g[l].push_back(make_pair(x, 1));
	g[r+1].push_back(make_pair(x, -1));
}

void solve (int u, int v, int w) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		add(idx[p], idx[u], w);
		u = far[p];
		p = top[u];
	}

	if (dep[u] > dep[v])
		swap(u, v);
	add(idx[u], idx[v], w);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		int u, v, w;
		while (M--) {
			scanf("%d%d%d", &u, &v, &w);
			solve(u, v, w);
		}

		int ans = 0;
		build(1, 0, 100000);
		for (int i = 1; i <= N; i++) {

			for (int j = 0; j < g[i].size(); j++)
				modify(1, g[i][j].first, g[i][j].second);
			val[i] = d[1];
		}

		for (int i = 1; i <= N; i++)
			printf("%d\n", val[idx[i]]);
	}
	return 0;
}
