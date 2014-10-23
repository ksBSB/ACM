#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 30005;

int N, Q, ne, first[maxn], jump[maxn * 2], link[maxn * 2], val[maxn];
int id, idx[maxn], dep[maxn], far[maxn], son[maxn], top[maxn], cnt[maxn];

void dfs (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	son[u] = 0;
	cnt[u] = 1;

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

inline void add_Edge(int u, int v) {
	link[ne] = v;
	jump[ne] = first[u];
	first[u] = ne++;
}

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];

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

int query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];
	int mid = (lc[u] + rc[u]) / 2, ret = 0;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

void modify(int u, int x, int v) {
	if (x == lc[u] && x == rc[u]) {
		s[u] = v;
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, v);
	else
		modify(rson(u), x, v);
	pushup(u);
}

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &val[i]);

	int u, v;
	ne = id = 0;
	memset(first, -1, sizeof(first));
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		u++, v++;
		add_Edge(u, v);
		add_Edge(v, u);
	}

	dfs(1, 0, 0);
	dfs(1, 1);
	build(1, 1, N);
	for (int i = 1; i <= N; i++)
		modify(1, idx[i], val[i]);
}

int query (int u, int v) {
	int p = top[u], q = top[v], ret = 0;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		ret += query(1, idx[p], idx[u]);
		u = far[p];
		p = top[u];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	ret += query(1, idx[u], idx[v]);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		scanf("%d", &Q);
		printf("Case %d:\n", kcas);
		int k, u, v;
		while (Q--) {
			scanf("%d%d%d", &k, &u, &v);
			if (k)
				modify(1, idx[u+1], v);
			else
				printf("%d\n", query(u+1, v+1));
		}
	}
	return 0;
}
