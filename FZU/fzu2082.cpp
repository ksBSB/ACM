#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50005;
typedef long long ll;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int val[maxn], lc[maxn << 2], rc[maxn << 2];
ll s[maxn << 2];

inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		s[u] = val[l];
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int x, int w) {
	if (x == lc[u] && x == rc[u]) {
		s[u] = w;
		return;
	}
	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, w);
	else
		modify(rson(u), x, w);
	pushup(u);
}

ll query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];
	ll ret = 0;
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	return ret;
}

int N, M, ne, first[maxn], jump[maxn * 2];
int id, idx[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn], dep[maxn];

struct Edge {
	int u, v, w;
	void set (int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
}ed[maxn * 2];

inline void add_Edge(int u, int v, int w) {
	ed[ne].set(u, v, w);
	jump[ne] = first[u];
	first[u] = ne++;
}

void dfs (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	son[u] = 0;
	cnt[u] = 1;

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

void init () {
	int u, v, w;
	id = ne = 0;
	memset(first, -1, sizeof(first));
	for (int i = 1; i < N; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_Edge(u, v, w);
		add_Edge(v, u, w);
	}
	dfs(1, 0, 0);
	dfs(1, 1);
	for (int i = 0; i < N - 1; i++) {
		int t = i * 2;
		if (dep[ed[t].u] < dep[ed[t].v])
			swap(ed[t].u, ed[t].v);
		val[idx[ed[t].u]] = ed[t].w;
	}
	build(1, 1, N);
}

ll solve (int u, int v) {
	ll ret = 0;
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		ret += query(1, idx[p], idx[u]);
		u = far[p];
		p = top[u];
	}

	if (u == v)
		return ret;
	if (dep[u] > dep[v])
		swap(u, v);
	ret += query(1, idx[son[u]], idx[v]);
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		int k, u, v;
		while (M--) {
			scanf("%d%d%d", &k, &u, &v);
			if (k)
				printf("%lld\n", solve(u, v));
			else
				modify(1, idx[ed[u*2-2].u], v);
		}
	}
	return 0;
}
