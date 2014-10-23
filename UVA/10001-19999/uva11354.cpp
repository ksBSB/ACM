#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 50005;
const int INF = 0x3f3f3f3f;

struct Edge {
	int u, v, w;
	Edge (int u = 0, int v = 0, int w = 0) { set(u, v, w); }
	void set(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
	friend bool operator < (const Edge& a, const Edge& b) {
		return a.w < b.w;
	}
}ed[maxn * 2];

int N, M, Q, ne, f[maxn], first[maxn], jump[maxn * 2], val[maxn];
int id, idx[maxn], top[maxn], far[maxn], son[maxn], dep[maxn], cnt[maxn];
vector<Edge> vec;

inline int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

inline void add_Edge (int u, int v, int w) {
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

void dfs (int u, int rot) {
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

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];

inline void pushup(int u) {
	s[u] = max(s[lson(u)], s[rson(u)]);
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

int query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];
	int mid = (lc[u] + rc[u]) / 2, ret = 0;
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	return ret;
}

void init () {
	int u, v, w;
	ne = id = 0;
	vec.clear();
	memset(first, -1, sizeof(first));
	for (int i = 1; i <= N; i++)
		f[i] = i;

	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		vec.push_back(Edge(u, v, w));
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); i++) {
		int p = getfar(vec[i].u);
		int q = getfar(vec[i].v);
		if (p == q)
			continue;
		add_Edge(vec[i].u, vec[i].v, vec[i].w);
		add_Edge(vec[i].v, vec[i].u, vec[i].w);
		f[p] = q;
	}

	dfs(1, 0, 0);
	dfs(1, 1);
	for (int i = 0; i < N - 1; i++) {
		int t = i * 2;
		u = (dep[ed[t].u] < dep[ed[t].v] ? ed[t].v : ed[t].u);
		val[idx[u]] = ed[t].w;
	}
	build(1, 1, N);
}

int solve (int u, int v) {
	int p = top[u], q = top[v], ret = 0;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		ret = max(ret, query(1, idx[p], idx[u]));
		u = far[p];
		p = top[u];
	}
	if (u == v)
		return ret;
	if (dep[u] > dep[v])
		swap(u, v);
	ret = max(ret, query(1, idx[son[u]], idx[v]));
	return ret;
}

int main () {
	int cas = 0;
	while (scanf("%d%d", &N, &M) == 2) {
		if (cas++)
			printf("\n");

		init();

		int u, v;
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d%d", &u, &v);
			printf("%d\n", solve(u, v));
		}
	}
	return 0;
}
