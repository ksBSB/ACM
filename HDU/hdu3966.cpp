#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define lowbit(x) ((x)&(-x))
const int maxn = 50000;

int N, M, Q, val[maxn+5], fenw[maxn+5];
vector<int> g[maxn+5];

inline void add (int x, int v) {
	while (x <= N) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

inline void add (int l, int r, int v) {
	add(l, v);
	add(r+1, -v);
}

inline int query (int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

int id, far[maxn+5], son[maxn+5], dep[maxn+5], cnt[maxn+5], top[maxn+5], idx[maxn+5];

void dfs_fir(int u, int pre, int d) {
	dep[u] = d;
	cnt[u] = 1;
	son[u] = 0;
	far[u] = pre;

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
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

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v == son[u] || v == far[u])
			continue;
		dfs_sec(v, v);
	}
}

void change (int u, int v, int c) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		add(idx[p], idx[u], c);
		u = far[p];
		p = top[u];
	}

	/*
	if (dep[u] > dep[v]) swap(u, v);
	add(idx[u], idx[v], c);
	*/
	if (dep[u] < dep[v]) swap(u, v);
	add(idx[v], idx[u], c);
}

int main () {
	while (scanf("%d%d%d", &N, &M, &Q) == 3) {
		id = 1;
		memset(fenw, 0, sizeof(fenw));
		for (int i = 1; i <= N; i++) {
			scanf("%d", &val[i]);
			g[i].clear();
		}

		int u, v, c;
		for (int i = 0; i < M; i++) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}

		dfs_fir(1, -1, 0);
		dfs_sec(1, 1);

		for (int i = 1; i <= N; i++) add(idx[i], idx[i], val[i]);

		char op[5];
		while (Q--) {
			scanf("%s%d", op, &u);
			if (op[0] == 'Q')
				printf("%d\n", query(idx[u]));
			else {
				scanf("%d%d", &v, &c);
				if (op[0] == 'D') c = -c;
				change(u, v, c);
			}
		}
	}
	return 0;
}
