#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;
const int INF = 0x3f3f3f3f;

int id, far[maxn], son[maxn], cnt[maxn], idx[maxn], top[maxn], dep[maxn];

int N, en, first[maxn], jump[maxn * 2], val[maxn];
struct Edge {
	int u, v, w;
	void set (int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
}ed[maxn * 2];

void dfs_fir (int u, int pre, int d) {
	dep[u] = d;
	far[u] = pre;
	cnt[u] = 1;
	son[u] = 0;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == pre)
			continue;
		dfs_fir(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs_sec(int u, int rot) {
	idx[u] = id++;
	top[u] = rot;

	if (son[u])
		dfs_sec(son[u], rot);

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == far[u] || v == son[u])
			continue;
		dfs_sec(v, v);
	}
}

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

int lc[maxn << 2], rc[maxn << 2], filp[maxn << 2], Ma[maxn << 2], Mi[maxn << 2];

inline void maintain (int u) {
	filp[u] ^= 1;
	swap(Ma[u], Mi[u]);
	Ma[u] = -Ma[u];
	Mi[u] = -Mi[u];
}

inline void pushup(int u) {
	Ma[u] = max(Ma[lson(u)], Ma[rson(u)]);
	Mi[u] = min(Mi[lson(u)], Mi[rson(u)]);
}

inline void pushdown (int u) {
	if (filp[u]) {
		maintain(lson(u));
		maintain(rson(u));
		filp[u] = 0;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	filp[u] = 0;

	if (l == r) {
		Ma[u] = Mi[u] = val[l];
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int x, int w) {
	if (lc[u] == x && rc[u] == x) {
		Ma[u] = Mi[u] = w;
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, w);
	else
		modify(rson(u), x, w);
	pushup(u);
}

void splay(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		splay(lson(u), l, r);
	if (r > mid)
		splay(rson(u), l, r);
	pushup(u);
}

int query (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r) 
		return Ma[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2, ret = -INF;
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	pushup(u);
	return ret;
}

inline void add_Edge(int u, int v, int w) {
	ed[en].set(u, v, w);
	jump[en] = first[u];
	first[u] = en++;
}

void init () {
	en = 0;
	id = 1;
	memset(first, -1, sizeof(first));

	scanf("%d", &N);
	
	int u, v, w;
	for (int i = 0; i  < N - 1; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_Edge(u, v, w);
		add_Edge(v, u, w);
	}

	dfs_fir(1, 0, 0);
	dfs_sec(1, 1);


	for (int i = 0; i < N - 1; i++) {
		int t = i * 2;
		if (dep[ed[t].u] < dep[ed[t].v])
			swap(ed[t].u, ed[t].v);
		val[idx[ed[t].u]] = ed[t].w;
	}
	build(1, 1, N);
}

int query (int u, int v) {
	int p = top[u], q = top[v], ret = -INF;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		ret = max(ret, query(1, idx[p], idx[u]));
		u = far[p];
		p = top[u];
	}
	//printf("%d %d\n", u, v);

	if (u == v)
		return ret;

	if (dep[u] > dep[v])
		swap(u, v);
	ret = max(ret, query(1, idx[son[u]], idx[v]));
	return ret;
}

void modify (int u, int v) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		splay(1, idx[p], idx[u]);
		u = far[p];
		p = top[u];
	}

	if (u == v)
		return;

	if (dep[u] > dep[v])
		swap(u, v);
	splay(1, idx[son[u]], idx[v]);
}

void solve () {
	int u, v;
	char op[20];
	while (scanf("%s", op), strcmp(op, "DONE") != 0) {
		scanf("%d%d", &u, &v);
		if (op[0] == 'C')
			modify(1, idx[ed[u*2-2].u], v);
		else if (op[0] == 'Q')
			printf("%d\n", query(u, v));
		else
			modify(u, v);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
