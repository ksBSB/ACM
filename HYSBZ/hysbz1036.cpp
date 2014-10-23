#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 30005;
const int INF = 0x3f3f3f3f;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2], m[maxn << 2], val[maxn];

inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
	m[u] = max(m[lson(u)], m[rson(u)]);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		s[u] = m[u] = val[l];
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int x, int w) {
	if (lc[u] == x && rc[u] == x) {
		s[u] = m[u] = w;
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, w);
	else
		modify(rson(u), x, w);
	pushup(u);
}

int sum(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	int mid = (lc[u] + rc[u]) / 2, ret = 0;
	if (l <= mid)
		ret += sum(lson(u), l, r);
	if (r > mid)
		ret += sum(rson(u), l, r);
	return ret;
}

int query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return m[u];

	int mid = (lc[u] + rc[u]) / 2, ret = -INF;
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	return ret;
}

int N, Q, ne, first[maxn], jump[maxn * 2], link[maxn * 2];
int id, idx[maxn], far[maxn], son[maxn], cnt[maxn], top[maxn], dep[maxn];

inline void add_Edge (int u, int v) {
	link[ne] = v;
	jump[ne] = first[u];
	first[u] = ne++;
}

void dfs_fir (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	son[u] = 0;
	cnt[u] = 1;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == pre)
			continue;
		dfs_fir(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs_sec(int u, int rot) {
	top[u] = rot;
	idx[u] = ++id;

	if (son[u])
		dfs_sec(son[u], rot);
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u] || v == son[u])
			continue;
		dfs_sec(v, v);
	}
}

void init () {
	int u, v;
	id = ne = 0;
	memset(first, -1, sizeof(first));
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(u, v);
		add_Edge(v, u);
	}

	dfs_fir(1, 0, 1);
	dfs_sec(1, 1);
	for (int i = 1; i <= N; i++)
		scanf("%d", &val[idx[i]]);
	build(1, 1, N);
}

int solve_query(int u, int v) {
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
	if (dep[u] > dep[v])
		swap(u, v);
	ret = max(ret, query(1, idx[u], idx[v]));
	return ret;
}

int solve_sum(int u, int v) {
	int p = top[u], q = top[v], ret = 0;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		ret += sum(1, idx[p], idx[u]);
		u = far[p];
		p = top[u];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	ret += sum(1, idx[u], idx[v]);
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		
		int u, v;
		char op[10];
		scanf("%d", &Q);
		while (Q--) {
			scanf("%s%d%d", op, &u, &v);
			if (op[0] == 'C')
				modify(1, idx[u], v);
			else if (op[1] == 'M')
				printf("%d\n", solve_query(u, v));
			else
				printf("%d\n", solve_sum(u, v));
		}
	}
	return 0;
}
