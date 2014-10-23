#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

struct Tree {
	int lc[maxn << 2], rc[maxn << 2], fp[maxn << 2], s[maxn << 2];
	void splay(int u) {
		s[u] = rc[u] - lc[u] + 1 - s[u];
		fp[u] ^= 1;
	}
	void pushup(int u) {
		s[u] = s[lson(u)] + s[rson(u)];
	}
	void pushdown(int u) {
		if (fp[u]) {
			splay(lson(u));
			splay(rson(u));
			fp[u] = 0;
		}
	}
	void build (int u, int l, int r) {
		lc[u] = l;
		rc[u] = r;
		fp[u] = s[u] = 0;

		if (l == r)
			return;

		int mid = (l + r) / 2;
		build(lson(u), l, mid);
		build(rson(u), mid + 1, r);
		pushup(u);
	}
	void modify(int u, int l, int r) {
		if (l <= lc[u] && rc[u] <= r) {
			splay(u);
			return;
		}
		pushdown(u);
		int mid = (lc[u] + rc[u]) / 2;
		if (l <= mid)
			modify(lson(u), l, r);
		if (r > mid)
			modify(rson(u), l, r);
		pushup(u);
	}
	int query(int u, int l, int r) {
		if (l <= lc[u] && rc[u] <= r)
			return s[u];
		pushdown(u);
		int mid = (lc[u] + rc[u]) / 2, ret = 0;
		if (l <= mid)
			ret += query(lson(u), l, r);
		if (r > mid)
			ret += query(rson(u), l, r);
		pushup(u);
		return ret;
	}
}W, L;

int N, Q, E, first[maxn], jump[maxn * 2], link[maxn * 2];
int id, idx[maxn], top[maxn], far[maxn], son[maxn], dep[maxn], cnt[maxn];

inline void add_Edge(int u, int v) {
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

void init () {
	E = id = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(u, v);
		add_Edge(v, u);
	}
	dfs(1, 0, 0);
	dfs(1, 1);
	W.build(1, 1, N);
	L.build(1, 1, N);
}

void modify(int u, int v, int k) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}

		if (k) {
			L.modify(1, idx[p], idx[u]);
			W.modify(1, idx[p], idx[p]);
			W.modify(1, idx[son[u]], idx[son[u]]);
		} else
			W.modify(1, idx[p], idx[u]);
		u = far[p];
		p = top[u];
	}

	if (dep[u] > dep[v])
		swap(u, v);

	if (k) {
		L.modify(1, idx[u], idx[v]);
		W.modify(1, idx[u], idx[u]);
		W.modify(1, idx[son[v]], idx[son[v]]);
	} else {
		if (u == v)
			return;
		W.modify(1, idx[son[u]], idx[v]);
	}
}

int query(int u, int v) {
	int p = top[u], q = top[v], ret = 0;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		if (u != p)
			ret += W.query(1, idx[son[p]], idx[u]);
		ret += (W.query(1, idx[p], idx[p]) ^ L.query(1, idx[far[p]], idx[far[p]]));
		u = far[p];
		p = top[u];
	}

	if (u == v) return ret;

	if (dep[u] > dep[v])
		swap(u, v);
	ret += W.query(1, idx[son[u]], idx[v]);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int k, u, v;
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d%d%d", &k, &u, &v);
			if (k == 3)
				printf("%d\n", query(u, v));
			else
				modify(u, v, k - 1);
		}
	}
	return 0;
}
