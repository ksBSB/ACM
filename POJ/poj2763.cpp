#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005;
int N, Q, S, ne;

int first[maxn], jump[maxn * 2];
int id, far[maxn], son[maxn], cnt[maxn], dep[maxn], top[maxn], idx[maxn];

struct Edge {
	int u, v, w;
	void set (int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
}ed[maxn * 2];

void dfs_fir (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	cnt[u] = 1;
	son[u] = 0;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == pre)
			continue;
		dfs_fir(v, u, d+1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs_sec(int u, int rot) {
	top[u] = rot;
	idx[u] = id++;

	if (son[u])
		dfs_sec(son[u], rot);

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == far[u] || v == son[u])
			continue;
		dfs_sec(v, v);
	}
}

inline void add_Edge(int u, int v, int w) {
	ed[ne].set(u, v, w);
	jump[ne] = first[u];
	first[u] = ne++;
}

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
typedef long long ll;
int lc[maxn << 2], rc[maxn << 2];
ll s[maxn << 2];

inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = 0;

	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int x, int w) {
	if (lc[u] == x && rc[u] == x) {
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

void init () {
	ne = 0;
	id = 1;

	int u, v, w;
	memset(first, -1, sizeof(first));
	for (int i = 0; i < N - 1; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_Edge(u, v, w);
		add_Edge(v, u, w);
	}
	dfs_fir(1, 0, 0);
	dfs_sec(1, 1);

	build(1, 1, N);
	for (int i = 0; i < N - 1; i++) {
		if (dep[ed[i*2].u] < dep[ed[i*2].v])
			swap(ed[i*2].u, ed[i*2].v);
		modify(1, idx[ed[i*2].u], ed[i*2].w);
	}
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
	while (scanf("%d%d%d", &N, &Q, &S) == 3) {
		init();
		int k, u, w;
		while (Q--) {
			scanf("%d%d", &k, &u);
			if (k) {
				scanf("%d", &w);
				modify(1, idx[ed[u*2 - 2].u], w);
			} else {
				printf("%lld\n", solve(S, u));
				S = u;
			}
		}
	}
	return 0;
}
