#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int N, M, ne, val[maxn], first[maxn], jump[maxn * 2];
int id, far[maxn], son[maxn], dep[maxn], top[maxn], cnt[maxn], idx[maxn];
struct Edge {
	int u, v;
	void set (int u, int v) {
		this->u = u;
		this->v = v;
	}
}ed[maxn * 2];

inline void add_Edge(int a, int b) {
	ed[ne].set(a, b);
	jump[ne] = first[a];
	first[a] = ne++;
}

void dfs_fir(int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	son[u] = 0;
	cnt[u] = 1;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int k = ed[i].v;
		if (k == pre)
			continue;
		dfs_fir(k, u, d + 1);
		cnt[u] += cnt[k];
		if (cnt[son[u]] < cnt[k])
			son[u] = k;
	}
}

void dfs_sec(int u, int rot) {
	top[u] = rot;
	idx[u] = id++;

	if (son[u])
		dfs_sec(son[u], rot);

	for (int i = first[u]; i + 1; i = jump[i]) {
		int k = ed[i].v;
		if (k == far[u] || k == son[u])
			continue;
		dfs_sec(k, k);
	}
}

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2];
struct Seg {
	int l, r, s;
	Seg (int s = 0, int l = 0, int r = 0) {
		this->l = l;
		this->r = r;
		this->s = s;
	}
	void maintain(int d) {
		s = 1;
		l = r = d;
	}
}nd[maxn << 2];

inline Seg merge(const Seg& L, const Seg& R) {
	if (L.s == 0) return R;
	if (R.s == 0) return L;
	return Seg(L.s + R.s + (L.r == R.l ? -1 : 0), L.l, R.r);
}

inline void pushdown(int u) {
	if (v[u] != -1) {
		v[lson(u)] = v[rson(u)] = v[u];
		nd[lson(u)].maintain(v[u]);
		nd[rson(u)].maintain(v[u]);
		v[u] = -1;
	}
}

inline void pushup(int u) {
	nd[u] = merge(nd[lson(u)], nd[rson(u)]);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	v[u] = -1;

	if (l == r) {
		nd[u].maintain(-1);
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int w) {
	if (l <= lc[u] && rc[u] <= r) {
		v[u] = w;
		nd[u].maintain(w);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, w);
	if (r > mid)
		modify(rson(u), l, r, w);
	pushup(u);
}

Seg query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return nd[u];

	pushdown(u);
	Seg ret;
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		ret = merge(ret, query(lson(u), l, r));
	if (r > mid)
		ret = merge(ret, query(rson(u), l, r));
	pushup(u);
	return ret;
}

void init () {
	ne = 0;
	id = 1;
	memset(first, -1, sizeof(first));

	for (int i = 1; i <= N; i++)
		scanf("%d", &val[i]);

	int a, b;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &a, &b);
		add_Edge(a, b);
		add_Edge(b, a);
	}
	dfs_fir(1, 0, 0);
	dfs_sec(1, 1);

	build(1, 1, N);
	for (int i = 1; i <= N; i++)
		modify(1, idx[i], idx[i], val[i]);

	/*
	for (int i = 1; i <= N; i++) {
		Seg ret = query(1, idx[i], idx[i]);
		printf("%d ", ret.r);
	}
	printf("\n");
	*/
}

void modify(int a, int b, int w) {
	int p = top[a], q = top[b];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(a, b);
		}
		modify(1, idx[p], idx[a], w);
		a = far[p];
		p = top[a];
	}
	if (dep[a] > dep[b])
		swap(a, b);
	modify(1, idx[a], idx[b], w);
}

int query(int a, int b) {
	int p = top[a], q = top[b];
	Seg one, two;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(a, b);
			swap(one, two);
		}
		one = merge(query(1, idx[p], idx[a]), one);
		a = far[p];
		p = top[a];
	}

	if (dep[a] > dep[b]) {
		swap(a, b);
		swap(one, two);
	}

	two = merge(query(1, idx[a], idx[b]), two);
	int ret = one.s + two.s;
	if (one.l == two.l) ret--;
	return ret;
}

int main () {

	while (scanf("%d%d", &N, &M) == 2) {
		init();

		int a, b, w;
		char op[5];
		while (M--) {
			scanf("%s%d%d", op, &a, &b);
			if (op[0] == 'C') {
				scanf("%d", &w);
				modify(a, b, w);
			} else
				printf("%d\n", query(a, b));
		}
	}
	return 0;
}
